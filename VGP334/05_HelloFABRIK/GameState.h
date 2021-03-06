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

	void DrawCounterFramesUI(bool active);

private:
	
	Omega::Graphics::Camera mCamera;
	Omega::Math::Vector3 mTarget;
	std::vector<Omega::Math::Vector3> mPoints;


	// ImGui
	std::vector<float> mVecFrames;
	const size_t mMaxFrameSize = 100;
};