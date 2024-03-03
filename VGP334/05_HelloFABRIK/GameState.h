#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState final: public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

	void DrawCounterFramesUI(bool active);

private:
	Omega::CameraService mCameraService;
	std::vector<Omega::Math::Vector3> mPoints;
	std::vector<float> mVecFrames; // ImGui
	Omega::Math::Vector3 mTarget;
	const size_t MAX_FRAME = 100u;
};