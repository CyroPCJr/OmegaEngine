#include "Precompiled.h"
#include "Model.h"

#include "MeshIO.h"

using namespace Omega::Graphics;

void ModelLoader::LoadModel(std::filesystem::path fileName, Model& model)
{
	fileName.replace_extension("model");

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	uint32_t numMeshes = 0;
	fscanf_s(file, "MeshCount: %d", &numMeshes);
	model.meshData.resize(numMeshes);
	for (uint32_t i = 0; i < numMeshes; ++i)
	{
		MeshIO::Read(file, model.meshData[i].mesh);
	}

	// For homework, save out model.materialData as well ...
	// if diffuseMapName is empty  string, write <none>

	fclose(file);

	for (auto& data: model.meshData)
	{
		data.meshBuffer.Initialize(data.mesh);
	}

	for (auto& data : model.materialData)
	{
		if (!data.diffuseMapName.empty())
		{
			//data.diffuseMap = std::make_unique<>..
			//data.diffuseMap->Initialize();
		}
	}
}

void Model::Initialize(const std::filesystem::path& fileName)
{
	ModelLoader::LoadModel(fileName, *this);
}

void Model::Terminate()
{
	for (auto& data: meshData)
	{
		data.meshBuffer.Terminate();
	}
}

void Model::Draw() const
{
	for (size_t i = 0; i < meshData.size(); ++i)
	{
		auto& data = meshData[i];
		/*materialData[data.materialIndex].diffuseMap->BindVS();
		materialData[data.materialIndex].diffuseMap->BindPS();*/
		data.meshBuffer.Draw();
	}
}