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

	//Omega::Graphics::MeshPX mMesh;	
	Omega::Graphics::MeshBuffer mMeshBuffer;
	Omega::Graphics::ConstantBuffer mConstantBuffer;
	Omega::Graphics::VertexShader mVertexShader;
	Omega::Graphics::PixelShader mGouraudShadingPixelShader;

	Omega::Graphics::Texture mTexture;
	Omega::Graphics::Sampler mSamplers;

	float mRotation = 0.0f;
};