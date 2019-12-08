#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

private:

	Omega::Graphics::Camera mCamera;

	//TODO FOR HOMEWORK:

	/*
	Move theses to Graphics Library
	*/

	struct Vertex
	{
		Omega::Math::Vector3 position;
		Omega::Graphics::Color color;
	};
	// Add a Mesh struct

	std::vector<Vertex> mVertices;
	std::vector<uint32_t> mIndices;


	/*

		Add ConstantBuffer class to wrap this
		Initialize(int size) /Terminate
		Bind
		Set(void* data)
	*/
	// move to other class
	ID3D11Buffer* mConstantBuffer = nullptr;


	/*
	 Add MeshBuffer class for theses pointers
	 Initialize(Vertex* vertices, int vertexCount, uint32_t* indices, int indexCount)
	 Terminate()
	 Draw()


	*/
	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11Buffer* mIndexBuffer = nullptr;

	/*
	Just do theses in HelloCube, add few more please
	*/

	Omega::Graphics::VertexShader mVertexShader;
	Omega::Graphics::PixelShader mPixelShader;
	//ID3D11PixelShader* mPixelShader = nullptr;

	float mRotation = 0.0f;
};