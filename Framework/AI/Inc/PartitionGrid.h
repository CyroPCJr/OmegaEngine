#pragma once

namespace Omega::AI
{
	template <class T>
	class PartitionGrid
	{
	public:
		using Cell = std::vector<T*>;

		void Resize(int columns, int rows)
		{
			mCells.resize(columns * rows);
			mColumns = columns;
			mRows = rows;
			ClearCells();
		}

		void ClearCells()
		{
			for (auto& cell : mCells)
			{
				cell.clear();
			}
		}

		Cell& GetCell(int column, int row) { return mCells[column + (row * mColumns)]; }
		const Cell& GetCell(int column, int row) const { return mCells[column + (row * mColumns)]; }

		int GetColumns() const { return mColumns; }
		int GetRows() const { return mRows; }

	private:
		std::vector<Cell> mCells;
		int mColumns;
		int mRows;
	};

}