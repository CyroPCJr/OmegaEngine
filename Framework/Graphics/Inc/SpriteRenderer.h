#pragma once
#include "TextureTypes.h"

namespace DirectX { class CommonStates; class SpriteBatch; }

namespace Omega::Graphics
{
	class Texture;

	class SpriteRenderer
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static SpriteRenderer* Get();
	public:
		SpriteRenderer() = default;
		~SpriteRenderer();

		SpriteRenderer(const SpriteRenderer&) = delete;
		SpriteRenderer& operator=(const SpriteRenderer&) = delete;

		void Initialize();
		void Terminate();

		inline void SetTransform(const Math::Matrix4& transform) { mTransform = transform; }

		void BeginRender();
		void EndRender();

		void Draw(const Texture& texture, const Math::Vector2& pos, float rotation = 0.0f, Pivot pivot = Pivot::Center, Flip flip = Flip::None);
		void Draw(const Texture& texture, const Math::Rect& sourceRect, const Math::Vector2& pos, float rotation = 0.0f, Pivot pivot = Pivot::Center, Flip flip = Flip::None);

	private:
		std::unique_ptr<DirectX::CommonStates> mCommonStates = nullptr;
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch = nullptr;

		Omega::Math::Matrix4 mTransform = Omega::Math::Matrix4::Identity;
	};

}