#pragma once

namespace Omega
{
	class Terrain
	{
	public:
		void Initialize(uint32_t numRows, uint32_t numCols, float cellSize);
		void Terminate();

		void LoadHeightmap(const std::filesystem::path& filePath);

		void SetHeightScale(float scale);
		void SetDirectionalLight(const Graphics::DirectionalLight& light);

		void Render(const Graphics::Camera& camera);
		void DrawEditorUI();

		void SetPosition(const Math::Vector3& newPos);
	private:
		void GenerateIndices();
		void GenerateVertices();

		struct ConstantData
		{
			Math::Matrix4 world;
			Math::Matrix4 wvp;
			Math::Vector3 viewPosition;
			float padding; // to memory alignment
			Graphics::DirectionalLight directionalLight;
		};

		Math::Vector3 mTerrainPosition = Math::Vector3::Zero;

		Graphics::TypedConstantBuffer<ConstantData> mConstantBuffer;
		Graphics::VertexShader mTerrainVertexShader;
		Graphics::PixelShader mTerrainPixelShader;
		Graphics::Sampler mSampler;
		Graphics::Texture mGrassTexture;

		Graphics::Mesh mMesh;
		Graphics::MeshBuffer mMeshBuffer;

		ConstantData mConstantData;

		uint32_t mNumRows = 0;
		uint32_t mNumCols = 0;
		uint32_t mNumCellsInCol = 0;
		uint32_t mNumCellsInRow = 0;
		uint32_t mNumCell = 0;

		float mheightScale = 1.0f;
		float mCellSize = 1.0f;
	};
}