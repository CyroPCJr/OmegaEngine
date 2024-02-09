#pragma once

namespace Omega::AI
{
	template <class T>
	class PartitionGrid
	{
	public:
		using Cell = std::vector<T*>;

		void Resize(const unsigned int columns, const unsigned int rows)
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

		Cell& GetCell(const unsigned  column, const unsigned  row) { return mCells[column + (row * mColumns)]; }
		const Cell& GetCell(const unsigned  column, const unsigned  row) const { return mCells[column + (row * mColumns)]; }

		const unsigned GetColumns() const { return mColumns; }
		const unsigned GetRows() const { return mRows; }
		const unsigned Size() const { return mCells.size(); }

	private:
		std::vector<Cell> mCells;
		unsigned int mColumns;
		unsigned int mRows;
	};

}