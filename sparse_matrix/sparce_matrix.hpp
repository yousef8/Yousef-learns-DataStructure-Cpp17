#ifndef SPARCE_MATRIX_21102024_H
#define SPARCE_MATRIX_21102024_H

#include "array_linked_list.hpp"

#include <cassert>

class SparseMatrix
{
  public:
	SparseMatrix(int _rows = 10, int _cols = 10) : rows{_rows}, cols{_cols}, mat{_rows}
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

	void print_nonzero()
	{
		for (auto &row : mat)
		{
			row.value.print_array_nonzero();
		}
	}

	friend std::ostream &operator<<(std::ostream &out, SparseMatrix &ls)
	{
		auto it = ls.mat.begin();
		int row = 0;

		while (row < ls.rows)
		{
			if (it != ls.mat.end() && it->idx == row)
			{
				out << it->value << std::endl;
				++it;
			}
			else
			{
				out << ArrayLinkedList<int>{ls.cols} << std::endl;
			}
			++row;
		}

		return out;
	}

	SparseMatrix &operator+=(const SparseMatrix &other)
	{
		mat.add(other.mat);
		return *this;
	}

	friend SparseMatrix operator+(SparseMatrix lhs, SparseMatrix &rhs)
	{
		return lhs += rhs;
	}

  private:
	int rows;
	int cols;
	ArrayLinkedList<ArrayLinkedList<int>> mat;
};

#endif
