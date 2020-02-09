#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
private:

	Omega::Graphics::Camera mCamera;

	Omega::Graphics::Mesh mMesh;
	
	Omega::Graphics::MeshBuffer mMeshBuffer;
	Omega::Graphics::MeshBuffer mMeshClouds;
	Omega::Graphics::Sampler mSamplers;
	Omega::Graphics::Texture mDisplacementTexture;
	Omega::Graphics::Texture mDifuseTexture;
	Omega::Graphics::Texture mSpecularTexture;
	Omega::Graphics::Texture mNormalMap;
	Omega::Graphics::Texture mClouds;
	Omega::Graphics::Texture mNightLights;

	struct TransformData
	{
		Omega::Math::Matrix4 world;
		Omega::Math::Matrix4 wvp;
		Omega::Math::Vector3 viewPosition;
		float padding;
	};

	struct SettingsData
	{
		float specularWeight = 1.0f;
		float bumpMapWeight = 1.0f;
		float normalMapWeight = 1.0f;
		float padding;
	};

	using TransformBuffer = Omega::Graphics::TypedConstantBuffer<TransformData>;
	using LightBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Graphics::DirectionalLight>;
	using MaterialBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Graphics::Material>;
	
	using SettingsDataBuffer = Omega::Graphics::TypedConstantBuffer<SettingsData>;

	SettingsDataBuffer mSettingsDataBuffer;
	TransformBuffer mTransformBuffer;
	LightBuffer mLightBuffer;
	MaterialBuffer mMaterialBuffer;

	SettingsData mSettingsData;
	Omega::Graphics::DirectionalLight mDirectionalLight;
	Omega::Graphics::Material mMaterial;

	Omega::Graphics::VertexShader mEarthVertexShader;
	Omega::Graphics::PixelShader mEarthPixelShader;
	
	Omega::Graphics::VertexShader mCloudVertexShader;
	Omega::Graphics::PixelShader mCloudPixelShader;
	

	Omega::Graphics::BlendState mBlendState;	

	Omega::Math::Vector3 mRotation = 0.0f;
	float mCloudRotation = 0.0f;
};