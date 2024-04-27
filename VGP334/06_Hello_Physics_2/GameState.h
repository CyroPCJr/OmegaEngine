#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState final : public Omega::AppState
{
public:

	~GameState() noexcept = default;

	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	Omega::Physics::PhysicsWorld mPhysicsWorld;
	Omega::CameraService mCameraService;
	std::optional<std::reference_wrapper<Omega::Graphics::RendererManager>> mRenderManager;
	std::array<Omega::Graphics::TextureId, 1u> mTexturesIds{ 0u };
};