#pragma once

#include "Mesh.h"
#include "MeshBuffer.h"

namespace Omega::Graphics
{

	class Model;

	class ModelLoader
	{
	public :
		static void LoadModel(std::filesystem::path fileName, Model& model);
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
			Mesh mesh;
			uint32_t materialIndex = 0;
			MeshBuffer meshBuffer;
		};

		std::vector<MeshData> meshData;		
	};

}