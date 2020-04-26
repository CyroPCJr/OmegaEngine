#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/EngineMath.h>

#include <assimp/Importer.hpp> //
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cstdio>

using namespace Omega::Graphics;

struct Arguments
{
	const char* inputFileName = nullptr;
	const char* outputFileName = nullptr;
	float scale = 1.0f;
	bool animOnly = false;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[])
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

void PrintUsage()
{
	printf_s("== ModelImporter Help ==\n\n"
		"Usage:\n"
		"	ModelImporter.exe [Options] <InputFile> <OutputFile>\n\n"
		"Options:\n"
		"	-s	Scale applied to the model.\n");
}

void SaveModel(const Arguments& args, const Model& model)
{
	// For homework. This is basically the opposite of LoadModel..
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
		printf_s("Error: %s\n", importer.GetErrorString());
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

	if (scene->HasMeshes())
	{
		printf("Reading mesh data...\n");

		const uint32_t numMeshes = scene->mNumMeshes;
		model.meshData.resize(numMeshes);

		for (uint32_t meshIndex = 0; meshIndex < numMeshes; ++meshIndex)
		{
			const aiMesh* inputMesh = scene->mMeshes[meshIndex];
			const uint32_t numVertices = inputMesh->mNumVertices;
			const uint32_t numFaces = inputMesh->mNumFaces;
			const uint32_t numIndices = numFaces * 3;

			printf("Reading vertices...\n");

			std::vector<Vertex> vertices;
			vertices.reserve(numVertices);

			const aiVector3D* positions = inputMesh->mVertices;
			const aiVector3D* normals = inputMesh->mNormals;
			const aiVector3D* tangents = inputMesh->mTangents;
			const aiVector3D* texCoords = inputMesh->HasTextureCoords(0) ? inputMesh->mTextureCoords[0] : nullptr;

			// // For homework, add data to vertices

			printf("Reading indices...\n");

			std::vector<uint32_t> indices;
			indices.reserve(numIndices);

			const aiFace* faces = inputMesh->mFaces;
			for (uint32_t i = 0; i < numFaces; ++i)
			{
				indices.push_back(faces[i].mIndices[0]);
				indices.push_back(faces[i].mIndices[1]);
				indices.push_back(faces[i].mIndices[2]);
			}

			Mesh mesh;
			mesh.vertices = std::move(vertices);
			mesh.indices = std::move(indices);
			model.meshData[meshIndex].mesh = std::move(mesh);
		}
	}

	SaveModel(args, model);	// ../../Assets/Models/<name>.model

	printf("All done!\n");

	return 0;
}