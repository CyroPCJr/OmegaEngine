#include "TileMap.h"

using namespace Steering;

void TileMap::Load()
{
	mTextureIds[0] = X::LoadTexture("grass.png");
	mColumns = 25;
	mRows = 20;
	mTiles.resize(static_cast<size_t>(mColumns * mRows), 0);
}

void TileMap::UnLoad()
{
	mTiles.clear();
}

void TileMap::Render()
{
	float tileWidth = static_cast<float>(X::GetSpriteWidth(mTextureIds[0]));
	float tileHeight = static_cast<float>(X::GetSpriteHeight(mTextureIds[0]));

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y);
			X::Math::Vector2 pos = { (x + 0.5f) * tileWidth,
								  (y + 0.5f) * tileHeight
			};
			X::DrawSprite(mTextureIds[mTiles[index]], pos, X::Pivot::Left);
		}
	}
}
