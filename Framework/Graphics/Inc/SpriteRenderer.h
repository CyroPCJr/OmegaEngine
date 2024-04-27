#pragma once
#include "TextureManager.h"
#include "TextureTypes.h"
#include <DirectXTK/Inc/CommonStates.h>
#include <DirectXTK/Inc/SpriteBatch.h>

namespace DirectX { class CommonStates; class SpriteBatch; }

namespace Omega::Graphics
{
	class Texture;

	class SpriteRenderer
	{
	public:

		struct SpriteCommand
		{
			SpriteCommand(TextureId t_textureId, const Math::Vector2& t_posiiton, float t_rotation) noexcept
				: sourceRect({ 0.0f, 0.0f, 0.0f, 0.0f }), position(t_posiiton), textureId(t_textureId), rotation(t_rotation)
			{}

			SpriteCommand(TextureId t_textureId, const Math::Vector2& t_posiiton, float t_rotation, Pivot t_pivot, Flip t_flip) noexcept
				: SpriteCommand(t_textureId, t_posiiton, t_rotation)
			{
				pivot = t_pivot;
				flip = t_flip;
			}

			SpriteCommand(TextureId t_textureId, const Math::Vector2& t_posiiton, float t_rotation, const Math::Rect& t_sourceRect) noexcept
				: SpriteCommand(t_textureId, t_posiiton, t_rotation)
			{
				sourceRect = t_sourceRect;
			}

			Math::Rect sourceRect{};
			Math::Vector2 position = Math::Vector2::Zero;
			TextureId textureId{ 0u };
			Pivot pivot = Pivot::Center;
			Flip flip = Flip::None;
			float rotation{ 0.0f };
		};

		explicit SpriteRenderer() noexcept(false);
		~SpriteRenderer() noexcept;

		SpriteRenderer(const SpriteRenderer&) = delete;
		SpriteRenderer& operator=(const SpriteRenderer&) = delete;

		SpriteRenderer(SpriteRenderer&&) = delete;
		SpriteRenderer& operator=(SpriteRenderer&&) = delete;

		void BeginRender();
		void Render();
		void EndRender();

		void DrawSprite(SpriteCommand&& spriteCommandsArgs);

		TextureId LoadTexture(const std::filesystem::path& fileName);
		void ClearAllTextures() noexcept;

	private:
		void Draw(const Texture& texture, SpriteCommand&& spriteCommandsArgs);

		DirectX::XMFLOAT2 GetOrigin(uint32_t width, uint32_t height, Pivot pivot);
		constexpr DirectX::SpriteEffects GetSpriteEffects(Flip flip) noexcept;
		constexpr DirectX::XMFLOAT2 ToXMFLOAT2(const Omega::Math::Vector2& v);

		std::vector<SpriteCommand> mSpriteCommands;
		std::unique_ptr<TextureManager> mTextureManager;
		std::unique_ptr<DirectX::CommonStates> mCommonStates;
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	};

}