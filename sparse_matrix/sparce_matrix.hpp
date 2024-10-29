#ifndef SPARCE_MATRIX_21102024_H
#define SPARCE_MATRIX_21102024_H

#include "array_linked_list.hpp"

#include <cassert>

class SparceMatrix
{
  public:
	SparceMatrix(int _rows = 10, int _cols = 10) : rows{_rows}, cols{_cols}, mat{_rows}
	{
	}

	void set_value(int value, int row_idx, int col_idx)
	{
		assert(row_idx >= 0);
		assert(row_idx < rows);
		auto row = mat.get_value(row_idx);
		if (row)
		{
			(*row).set_value(value, col_idx);
			mat.set_value(*row, row_idx);
			return;
		}
		ArrayLinkedList<int> new_row{cols};
		new_row.set_value(value, col_idx);
		mat.set_value(new_row, row_idx);
		return;
	}

	friend std::ostream &operator<<(std::ostream &out, const SparceMatrix &ls)
	{
		out << ls.mat;
		return out;
	}

  private:
	int rows;
	int cols;
	ArrayLinkedList<ArrayLinkedList<int>> mat;
};

#endif
