#pragma once
#include <XEngine.h>

namespace FinalProject
{
	class Bullet
	{
	public:
		void Load(const std::string& name);
		void Unload();
		void Update(float deltaTime);
		void Render();

		void Fire(const X::Math::Vector2& pos, const X::Math::Vector2& vel);
	private:
		X::TextureId mTextureId;
		X::Math::Vector2 mPosition;
		X::Math::Vector2 mVelocity;
	};

}