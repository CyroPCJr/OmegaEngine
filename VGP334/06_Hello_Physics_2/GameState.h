#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState final : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	Omega::CameraService mCameraService;
	std::optional<std::reference_wrapper<Omega::Graphics::RendererManager>> mRenderManager;
	std::array<Omega::Graphics::TextureId, 1> mTexturesIds{ 0 };
};