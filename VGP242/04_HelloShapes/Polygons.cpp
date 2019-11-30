#include "Polygons.h"

using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace Omega::Input;

HeartShape::HeartShape()
{
	mVertices.clear();
	
	// upper left triangle
	mVertices.emplace_back(Vertex{ Vector3{ -0.75f,0.3f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.9f,0.0f }, Color{Colors::HotPink} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.1f,0.3f,0.0f }, Color{Colors::HotPink} });

	//// upper right triangle
	mVertices.emplace_back(Vertex{ Vector3{ 0.75f, 0.3f,0.0f }, Color{Colors::Red} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, 0.2f,0.0f }, Color{Colors::Black} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.1f, 0.3f,0.0f }, Color{Colors::Green} });

	//// botton triangle
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
	mVertices.clear();
	// triforce zelda
	//
	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, 0.1f, 0.0f }, Color{Colors::Gold} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 0.7f, 0.0f  }, Color{Colors::Gold} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.3f, 0.1f, 0.0f}, Color{Colors::Gold} });

	mVertices.emplace_back(Vertex{ Vector3{ -0.6f, -0.5f, 0.0f }, Color{Colors::Gold} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, 0.1f, 0.0f }, Color{Colors::Gold} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.0f, -0.5f, 0.0f }, Color{Colors::Black} });

	mVertices.emplace_back(Vertex{ Vector3{ 0.0f, -0.5f, 0.0f }, Color{Colors::Black} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.3f, 0.1f, 0.0f }, Color{Colors::Gold} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.6f, -0.5f, 0.0f }, Color{Colors::Gold} });

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
	mVertices.clear();

	// first diamond
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f, 0.5f, 0.0f }, Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, 0.3f, 0.0f }, Color{Colors::Red} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.7f, 0.3f, 0.0f }, Color{Colors::Green} });

	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, 0.3f, 0.0f }, Color{Colors::Red} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.3f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.7f, 0.3f, 0.0f }, Color{Colors::Aqua} });

	// second diamond
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, 0.5f, 0.0f }, Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.7f, 0.3f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.3f, 0.3f, 0.0f }, Color{Colors::Red} });

	mVertices.emplace_back(Vertex{ Vector3{ 0.7f, 0.3f, 0.0f }, Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, -0.3f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.3f, 0.3f, 0.0f }, Color{Colors::Red} });

	// third diamond
	mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 0.2f, 0.0f }, Color{Colors::Firebrick} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.7f, -0.5f, 0.0f }, Color{Colors::DarkOliveGreen} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.7f, -0.5f, 0.0f }, Color{Colors::DarkOliveGreen} });
}

void RandomPolygon::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::D))
	{
		Omega::MainApp().ChangeState("HeartShape");
	}
}