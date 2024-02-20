#pragma once
#include <OmegaEngine/Inc/Omega.h>

class GameState final : public Omega::AppState
{
public:
	GameState() noexcept = default;
	//copy constructor
	GameState(const GameState&) = delete;
	//copy assignment
	GameState& operator=(const GameState&) = delete;
	//move constructor
	GameState(GameState&&) = delete;
	//move assigment
	GameState& operator=(GameState&&) = delete;

	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
private:
	Omega::GameWorld mWorld;
	Omega::CameraService* mCameraService = nullptr;
};