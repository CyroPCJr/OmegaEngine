#include "Polygons.h"

using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace Omega::Input;

HeartShape::HeartShape()
{
	//mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 0.3f, 0.0f }, Color{Colors::Aqua} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.3f, -0.3f, 0.0f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.3f, -0.3f, 0.0f }, Color{Colors::Red} });

	// upper left triangle
	mVertices.emplace_back(Vertex{ Vector3{ -0.75f,0.3f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.9f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.1f,0.3f,0.0f }, Color{Colors::HotPink} });

	// upper right triangle
	mVertices.emplace_back(Vertex{ Vector3{ 0.75f, 0.3f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, 0.1f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.1f, 0.3f,0.0f }, Color{Colors::HotPink} });

	// botton triangle
	mVertices.emplace_back(Vertex{ Vector3{ 0.75f,0.3f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.0f,-0.75f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.75f,0.3f,0.0f }, Color{Colors::HotPink} });
}

void HeartShape::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::W))
	{
		Omega::MainApp().ChangeState("Triforce");
	}
}

Triforce::Triforce()
{
	mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 1.0f, 0.0f }, Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.3f, -0.3f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, -0.3f, 0.0f }, Color{Colors::Red} });
}

void Triforce::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::S))
	{
		Omega::MainApp().ChangeState("RandomPolygon");
	}
}

RandomPolygon::RandomPolygon()
{
	mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 1.0f, 0.0f }, Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 1.f, 0.0f, 1.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, -0.3f, 0.0f }, Color{Colors::Red} });
}

void RandomPolygon::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::D))
	{
		Omega::MainApp().ChangeState("HeartShape");
	}
}
