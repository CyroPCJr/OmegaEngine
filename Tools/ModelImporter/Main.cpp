//Referece:
//https://github.com/assimp/assimp

#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/EngineMath.h>

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>		// Ouput data structure
#include <assimp/postprocess.h> // Post processing flags
#include <iostream>

using namespace Omega::Graphics;
using namespace Omega::Math;

using BoneIndexLookup = std::map<std::string_view, int>; // Used to lookup bone by name

struct Arguments
{
	const char* inputFileName = nullptr;
	const char* outputFileName = nullptr;
	float scale = 1.0f;
	bool animOnly = false;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[]) noexcept
{
	// We need at least 3 arguments.
	if (argc < 3)
	{
		return std::nullopt;
	}

	Arguments args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];

	for (int i = 1; i + 2 < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 's':
				args.scale = static_cast<float>(atof(argv[i + 1]));
				break;
			default:
				break;
			}
		}
	}
	return args;
}

void PrintUsage() noexcept
{
	std::cout << "== ModelImporter Help ==\n\n"
		"Usage:\n"
		"	ModelImporter.exe [Options] <InputFile> <OutputFile>\n\n"
		"Options:\n"
		"	-s	Scale applied to the model.\n";
}

inline Color Convert(const aiColor3D& c) noexcept
{
	return { c.r, c.g, c.b, 1.0f };
}

inline Vector3 Convert(const aiVector3D& v) noexcept
{
	return { v.x, v.y, v.z };
}

inline Quaternion Convert(const aiQuaternion& q) noexcept
{
	return { q.x, q.y, q.z, q.w };
}

inline Matrix4 Convert(const aiMatrix4x4& m) noexcept
{
	Matrix4 mat = *(reinterpret_cast<const Matrix4*>(&m));
	return Transpose(mat);
}

void ExportEmbeddedTexture(const aiTexture& texture, const Arguments& args, std::string_view filePath) noexcept
{
	std::cout << "Extracting embedded texture...\n";

	std::string fullFileName = args.outputFileName;
	fullFileName = fullFileName.substr(0, fullFileName.rfind('/') + 1);
	fullFileName += filePath;

	FILE* file = nullptr;
	fopen_s(&file, fullFileName.c_str(), "wb");
	OMEGAASSERT(file != NULL, "Error to open file! %s", __FUNCTION__);

	size_t written = fwrite(texture.pcData, 1, texture.mWidth, file);
	OMEGAASSERT(written == texture.mWidth, "Error: Failed to extract embedded texture!");
	fclose(file);
}

std::string FindTexture(const aiScene& scene, const aiMaterial& inputMaterial,
	aiTextureType textureType, const Arguments& args, std::string_view suffix) noexcept
{
	std::filesystem::path textureName;

	const uint32_t textureCount = inputMaterial.GetTextureCount(textureType);
	if (textureCount > 0)
	{
		aiString texturePath;
		if (inputMaterial.GetTexture(textureType, 0, &texturePath) == aiReturn_SUCCESS)
		{
			// For FBX files, embedded textures is now accessed using GetEmbeddedTexture
			// https://github.com/assimp/assimp/issues/1830
			if (auto embeddedTexture = scene.GetEmbeddedTexture(texturePath.C_Str()); embeddedTexture)
			{
				std::filesystem::path embeddedFilePath = texturePath.C_Str();
				std::string fileName = args.inputFileName;
				fileName.erase(fileName.length() - 4); // remove ".fbx" extension
				fileName += suffix;
				fileName += embeddedFilePath.extension().u8string();

				ExportEmbeddedTexture(*embeddedTexture, args, fileName);

				std::cout << "Exporting embedded texture to " << fileName.c_str() << '\n';
				textureName = fileName;
			}
			else
			{
				std::filesystem::path filePath = texturePath.C_Str();
				std::string fileName = filePath.filename().u8string();
				std::cout << "Adding texture " << fileName.c_str() << '\n';
				textureName = fileName;
			}
		}
	}
	return textureName.filename().u8string().c_str();
}

// Check if inputBone exists in skeleton, if so just return the index.
// Otherwise, add it to the skeleton. The aiBone must have a name!
int TryAddBone(const aiBone* inputBone, Skeleton& skeleton, BoneIndexLookup& boneIndexLookup) noexcept
{
	std::string_view name = inputBone->mName.C_Str();
	OMEGAASSERT(!name.empty(), "Error: inputBone has no name!");

	if (auto iter = boneIndexLookup.find(name); iter != boneIndexLookup.end())
	{
		return iter->second;
	}

	// Add a new bone in the skeleton for this
	auto& newBone = skeleton.bones.emplace_back(std::make_unique<Bone>());
	newBone->name = std::move(name);
	newBone->index = static_cast<int>(skeleton.bones.size()) - 1;
	newBone->offsetTransform = Convert(inputBone->mOffsetMatrix);

	// Cache the bone index
	boneIndexLookup.emplace(newBone->name, newBone->index);
	return newBone->index;
}

// Recursively walk the aiScene tree and add/link bones to our skeleton as we find them.
Bone* BuildSkeleton(const aiNode& sceneNode, Bone* parent, Skeleton& skeleton, BoneIndexLookup& boneIndexLookup) noexcept
{
	Bone* bone = nullptr;

	std::string_view name = sceneNode.mName.C_Str();
	if (auto iter = boneIndexLookup.find(name); iter != boneIndexLookup.end())
	{
		// Bone already exists
		bone = skeleton.bones[iter->second].get();
	}
	else
	{
		// Add a new bone in the skeleton for this (possible need to generate a name for it)
		bone = skeleton.bones.emplace_back(std::make_unique<Bone>()).get();
		bone->index = static_cast<int>(skeleton.bones.size()) - 1;
		bone->offsetTransform = Matrix4::Identity;
		if (name.empty())
		{
			bone->name = "NoName" + std::to_string(bone->index);
		}
		else
		{
			bone->name = std::move(name);
		}

		// Cache the bone index
		boneIndexLookup.emplace(bone->name, bone->index);
	}

	// Link to your parent
	bone->parent = parent;
	bone->toParentTransform = Convert(sceneNode.mTransformation);

	// Recurse through your children
	bone->children.reserve(sceneNode.mNumChildren);
	for (uint32_t i = 0; i < sceneNode.mNumChildren; ++i)
	{
		Bone* child = BuildSkeleton(*sceneNode.mChildren[i], bone, skeleton, boneIndexLookup);
		child->parentIndex = bone->index; // new line to save Parent Index
		bone->children.push_back(child);
	}
	return bone;
}

void SaveModel(const Arguments& args, Model& model) noexcept
{
	// Reference
	//https://www.programiz.com/c-programming/c-file-input-output
	std::cout << "Saving model: " << args.outputFileName << " ... \n";

	FILE* file = nullptr;
	fopen_s(&file, args.outputFileName, "w");
	OMEGAASSERT(file != NULL, "Error to open file! %s", __FUNCTION__);

	const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
	fprintf_s(file, "MeshCount: %d\n", meshCount);

	for (uint32_t i = 0; i < meshCount; ++i)
	{
		fprintf_s(file, "MaterialIndex: %d\n", model.meshData[i].materialIndex);
		MeshIO::Write(file, model.meshData[i].mesh);
	}
	fclose(file);

	FILE* fileMaterial = nullptr;
	std::filesystem::path fileName = args.outputFileName;
	fileName.replace_extension("materialData");
	std::cout << "Saving material data: " << fileName.u8string().c_str() << " ... \n";
	fopen_s(&fileMaterial, fileName.u8string().c_str(), "w");
	if (fileMaterial == NULL)
	{
		std::cout << __FUNCTION__ " Error to open file!\n";
		exit(1);
	}
	//fopen_s(&fileMaterial, args.outputFileName, "w");

	const uint32_t materialCount = static_cast<uint32_t>(model.materialData.size());
	fprintf_s(fileMaterial, "MaterialCount: %d\n", materialCount);

	for (uint32_t i = 0; i < materialCount; ++i)
	{
		fprintf_s(fileMaterial, "DiffuseMapName %s\n",
			model.materialData[i].diffuseMapName.empty() ?
			"<none>" : model.materialData[i].diffuseMapName.c_str());
		MeshIO::Write(fileMaterial, model.materialData[i].material);
	}
	fclose(fileMaterial);
}

void SaveSkeleton(const Arguments& args, const Skeleton& skeleton) noexcept
{
	std::filesystem::path path = args.outputFileName;
	path.replace_extension("skeleton");

	std::cout << "Saving skeleton: " << path.u8string().c_str() << " ...\n";

	FILE* file = nullptr;
	fopen_s(&file, path.u8string().c_str(), "w");
	OMEGAASSERT(file != NULL, "Error to open file! %s", __FUNCTION__);

	SkeletonIO::Write(file, skeleton);

	fclose(file);
}

void SaveAnimationSet(const Arguments& args, const AnimationSet& animationSet) noexcept
{
	std::filesystem::path path = args.outputFileName;
	path.replace_extension("animset");

	std::cout << "Saving animations: " << path.u8string().c_str() << " ... \n";

	FILE* file = nullptr;
	fopen_s(&file, path.u8string().c_str(), "w");
	OMEGAASSERT(file != NULL, "Error to open file! %s", __FUNCTION__);
	const uint32_t clipCount = static_cast<uint32_t>(animationSet.clips.size());
	fprintf_s(file, "ClipCount: %d\n", clipCount);

	for (const auto& animation : animationSet.clips)
	{
		fprintf_s(file, "Name: %s\n", animation->name.c_str());
		fprintf_s(file, "Duration: %f\n", animation->duration);
		fprintf_s(file, "TickPerSecond: %f\n", animation->tickPerSecond);
		fprintf_s(file, "BoneAnimationCount: %d\n", static_cast<uint32_t>(animation->boneAnimations.size()));
		AnimationIO::Write(file, *animation);
	}

	fclose(file);
}

int main(int argc, char* argv[])
{

	const auto argsOpt = ParseArgs(argc, argv);
	if (!argsOpt.has_value())
	{
		PrintUsage();
		return -1;
	}

	const auto& args = argsOpt.value();

	// Create an instance of the importer class to do the parsing for us.
	Assimp::Importer importer;

	// Try to import the model into a scene.
	const aiScene* scene = importer.ReadFile(args.inputFileName,
		aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded);

	if (!scene)
	{
		std::cout << "Error: " << importer.GetErrorString() << '\n';
		return -1;
	}
	// scene
	// +- mesh[][][][][]
	// +- material[][][][][]
	// +- animation[][][][][_]
	// 
	// +- mRootNode (scene graph)
	//        +- Node
	//            +- Node
	//            +- Node
	//                +- Node ...
	//        +- Node
	//            +- Node ...
	//        +- Node

	Model model;
	BoneIndexLookup boneIndexLookup;

	if (scene->HasMeshes())
	{
		std::cout << "Reading mesh data...\n";

		const uint32_t numMeshes = scene->mNumMeshes;
		model.meshData.resize(numMeshes);

		for (uint32_t meshIndex = 0; meshIndex < numMeshes; ++meshIndex)
		{
			const aiMesh* inputMesh = scene->mMeshes[meshIndex];
			const uint32_t numVertices = inputMesh->mNumVertices;
			const uint32_t numFaces = inputMesh->mNumFaces;
			const uint32_t numIndices = numFaces * 3;

			std::cout << "Reading material index...\n";

			model.meshData[meshIndex].materialIndex = inputMesh->mMaterialIndex;

			std::cout << "Reading vertices...\n";

			std::vector<BoneVertex> vertices;
			vertices.reserve(numVertices);

			const aiVector3D* positions = inputMesh->mVertices;
			const aiVector3D* normals = inputMesh->mNormals;
			const aiVector3D* tangents = inputMesh->mTangents;
			const aiVector3D* texCoords = inputMesh->HasTextureCoords(0) ? inputMesh->mTextureCoords[0] : nullptr;

			for (uint32_t i = 0; i < numVertices; ++i)
			{
				auto& vertex = vertices.emplace_back(BoneVertex{});
				vertex.position = Convert(positions[i]) * args.scale;
				vertex.normal = Convert(normals[i]);
				vertex.tangent = Convert(tangents[i]);
				vertex.texcoord = texCoords ? Vector2(texCoords[i].x, texCoords[i].y) : 0.0f;
			}

			std::cout << "Reading indices...\n";

			std::vector<uint32_t> indices;
			indices.reserve(numIndices);

			const aiFace* faces = inputMesh->mFaces;
			for (uint32_t i = 0; i < numFaces; ++i)
			{
				auto& facess = faces[i];
				indices.push_back(facess.mIndices[0]);
				indices.push_back(facess.mIndices[1]);
				indices.push_back(facess.mIndices[2]);
			}

			if (inputMesh->HasBones())
			{
				std::cout << "Reading bones weights...\n";

				std::vector<int> numWeights(vertices.size(), 0);

				for (uint32_t meshBoneIndex = 0; meshBoneIndex < inputMesh->mNumBones; ++meshBoneIndex)
				{
					aiBone* inputBone = inputMesh->mBones[meshBoneIndex];
					int boneIndex = TryAddBone(inputBone, model.skeleton, boneIndexLookup);

					for (uint32_t weightIndex = 0; weightIndex < inputBone->mNumWeights; ++weightIndex)
					{
						const aiVertexWeight& weight = inputBone->mWeights[weightIndex];
						auto& vertex = vertices[weight.mVertexId];
						auto& count = numWeights[weight.mVertexId];

						// Our vertices can hold at most up to 4 weights
						if (count < 4)
						{
							vertex.boneIndices[count] = boneIndex;
							vertex.boneWeights[count] = weight.mWeight;
							++count;
						}
					}

				}
			}

			SkinnedMesh mesh;
			mesh.vertices = std::move(vertices);
			mesh.indices = std::move(indices);
			model.meshData[meshIndex].mesh = std::move(mesh);

		}
	}

	// Look for material data.
	if (scene->HasMaterials())
	{
		std::cout << "Reading materials...\n";
		const uint32_t numMaterials = scene->mNumMaterials;
		model.materialData.resize(numMaterials);

		for (uint32_t i = 0; i < numMaterials; ++i)
		{
			const aiMaterial* inputMaterial = scene->mMaterials[i];

			aiColor3D ambientColor(0.0f, 0.0f, 0.0f);
			inputMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
			aiColor3D diffuseColor(0.0f, 0.0f, 0.0f);
			inputMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
			aiColor3D specularColor(0.0f, 0.0f, 0.0f);
			inputMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
			ai_real specularPower;
			inputMaterial->Get(AI_MATKEY_SHININESS, specularPower);

			auto& material = model.materialData[i];
			material.material.ambient = Convert(ambientColor);
			material.material.diffuse = Convert(diffuseColor);
			material.material.specular = Convert(specularColor);
			material.material.power = specularPower;
			material.diffuseMapName = FindTexture(*scene, *inputMaterial, aiTextureType_DIFFUSE, args, "_diffuse" + std::to_string(i));
		}
	}

	// Check if we have skeleton information.
	if (!model.skeleton.bones.empty())
	{
		std::cout << "Building skeleton...\n";
		BuildSkeleton(*scene->mRootNode, nullptr, model.skeleton, boneIndexLookup);
	}

	// Look for animation data.
	if (scene->HasAnimations())
	{
		std::cout << "Reading animations...\n";
		for (uint32_t animIndex = 0; animIndex < scene->mNumAnimations; ++animIndex)
		{
			const aiAnimation* inputAnim = scene->mAnimations[animIndex];
			auto animClip = std::make_unique<AnimationClip>();

			if (inputAnim->mName.length > 0)
			{
				animClip->name = inputAnim->mName.C_Str();
			}
			else
			{
				animClip->name = "Anim" + std::to_string(animIndex);
			}
			animClip->duration = static_cast<float>(inputAnim->mDuration);
			animClip->tickPerSecond = static_cast<float>(inputAnim->mTicksPerSecond);

			std::cout << "Reading bone animatons for \n" << animClip->name.c_str() << " ...\n";

			// Make sure we have the same number of slots for animationClip as the bones in the
			// skeleton. This allows us to undex the animationClip using the bone index directly.
			animClip->boneAnimations.resize(model.skeleton.bones.size());

			for (uint32_t boneAnimIndex = 0; boneAnimIndex < inputAnim->mNumChannels; ++boneAnimIndex)
			{
				const aiNodeAnim* inputBoneAnim = inputAnim->mChannels[boneAnimIndex];
				int slotIndex = boneIndexLookup[inputBoneAnim->mNodeName.C_Str()];
				auto& boneAnim = animClip->boneAnimations[slotIndex];
				boneAnim = std::make_unique<Animation>();

				AnimationBuilder builder;
				for (uint32_t keyIndex = 0; keyIndex < inputBoneAnim->mNumPositionKeys; ++keyIndex)
				{
					auto& key = inputBoneAnim->mPositionKeys[keyIndex];
					builder.AddPositionKey(Convert(key.mValue) * args.scale, static_cast<float>(key.mTime));
				}

				for (uint32_t keyIndex = 0; keyIndex < inputBoneAnim->mNumRotationKeys; ++keyIndex)
				{
					auto& key = inputBoneAnim->mRotationKeys[keyIndex];
					builder.AddRotationKey(Convert(key.mValue), static_cast<float>(key.mTime));
				}

				for (uint32_t keyIndex = 0; keyIndex < inputBoneAnim->mNumScalingKeys; ++keyIndex)
				{
					auto& key = inputBoneAnim->mScalingKeys[keyIndex];
					builder.AddScaleKey(Convert(key.mValue), static_cast<float>(key.mTime));
				}

				*boneAnim = builder.GetAnimation();
			}
			// Add the new clip to our animation set
			model.animationSet.clips.emplace_back(std::move(animClip));
		}
	}

	SaveModel(args, model);				// ../../Assets/Models/<name>.model
	SaveSkeleton(args, model.skeleton);	// ../../Assets/Models/<name>.model
	SaveAnimationSet(args, model.animationSet);

	std::cout << "All done!\n";
	return 0;
}