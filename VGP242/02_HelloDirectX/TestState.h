#pragma once

#include <OmegaEngine/Inc/Omega.h>

class RedState : public Omega::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class BlueState : public Omega::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};