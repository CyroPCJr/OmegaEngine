#pragma once

#include "Material.h"
#include "Texture.h"
#include "Skeleton.h"
#include "Mesh.h"
#include "MeshBuffer.h"

namespace Omega::Graphics
{

	class Model;

	class ModelLoader
	{
	public :
		static void LoadModel(std::filesystem::path fileName, Model& model);
		static void LoadSkeleton(std::filesystem::path fileName, Skeleton& model);
	};

	class Model
	{
	public:
		void Initialize(const std::filesystem::path& fileName);
		void Terminate();

		void Draw() const;
	public:
		struct MeshData
		{
			SkinnedMesh mesh; // CPU data
			uint32_t materialIndex = 0;
			MeshBuffer meshBuffer; //GPU data
		};
		
		struct MaterialData
		{
			Material material; // CPU data
			std::string diffuseMapName;
			std::unique_ptr<Texture> diffuseMap; // GPU data
		};

		std::vector<MeshData> meshData;
		std::vector<MaterialData> materialData;
		Skeleton skeleton;
	};

}