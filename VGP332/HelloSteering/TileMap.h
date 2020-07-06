#pragma once

namespace Steering
{

	class TileMap
	{
	public:
		void Load();
		void UnLoad();

		void Render();
	private:

		constexpr int GetIndex(int x, int y) const
		{
			return x + (y * mColumns);
		}

		std::array<X::TextureId, 1> mTextureIds;
		std::vector<int> mTiles;
		int mColumns = 0;
		int mRows = 0;
		int mTileSize = 32;
	};

}