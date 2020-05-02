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
	fclose(file);

	for (auto& data: model.meshData)
	{
		data.meshBuffer.Initialize(data.mesh);
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
		data.meshBuffer.Draw();
	}
}