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
	Omega::Physics::PhysicsWorld mPhysicsWorld;
	float mClothSize = 0.0f;
};