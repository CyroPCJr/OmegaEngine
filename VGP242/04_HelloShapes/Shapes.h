#pragma once

#include <OmegaEngine/Inc/Omega.h>

class HearShape : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
private:
	struct Vertex
	{
		Omega::Math::Vector3 position;
		Omega::Graphics::Color color;
	};

	std::vector<Vertex> mVertices;
	ID3D11Buffer* mVertexBuffer = nullptr;

	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;

	ID3D11PixelShader* mPixelShader = nullptr;
};

class Triforce : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
private:
	struct Vertex
	{
		Omega::Math::Vector3 position;
		Omega::Graphics::Color color;
	};

	std::vector<Vertex> mVertices;
	ID3D11Buffer* mVertexBuffer = nullptr;

	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;

	ID3D11PixelShader* mPixelShader = nullptr;
};