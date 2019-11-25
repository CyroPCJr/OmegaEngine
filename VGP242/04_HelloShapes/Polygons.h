#pragma once

#include "Shapes.h"
#include <OmegaEngine/Inc/Omega.h>

class HeartShape : public Shapes
{
public:
	HeartShape();

	void Update(float deltaTime) override;
};

class Triforce : public Shapes
{
public:
	Triforce();
	void Update(float deltaTime) override;
};

class RandomPolygon : public Shapes
{
public :
	RandomPolygon();

	void Update(float deltaTime) override;
};