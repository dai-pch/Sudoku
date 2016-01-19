#include "stdafx.h"

std::ostream &operator<<(std::ostream &ostream, const element &ele)
{
	return ostream << "(" << ele.position << ", " << ele.number << ") ";
}

int addrow(const int position, const int num, const int linkrow, std::vector<nonZeroPosition> &vec, std::vector<element> &index)
{
	int row, col, uni;
	nonZeroPosition node;
	element ele;

	row = (position - 1) / 9 + 1;
	col = position - 9 * (row - 1);
	uni = ((row - 1) / 3) * 3 + ((col - 1) / 3) + 1;

	//column 1-81
	node.row = linkrow;
	node.column = position;
	vec.push_back(node);

	//column 82-162
	node.row = linkrow;
	node.column = 72 + row * 9 + num;
	vec.push_back(node);

	//column 163-243
	node.row = linkrow;
	node.column = 153 + col * 9 + num;
	vec.push_back(node);

	//column 244-324
	node.row = linkrow;
	node.column = 234 + uni * 9 + num;
	vec.push_back(node);
	
	ele.position = position;
	ele.number = num;
	index.push_back(ele);

	return 0;
}

int convert(int matric[], std::vector<nonZeroPosition> &exa, std::vector<element> &index)
{
	int linkrow = 0;

/*	if (matric.size() != 81)
	{
		throw std::logic_error("Sudoku matric size does not correct.");
	}*/

	exa.clear();
	index.clear();
/*	res.push_back(0);
	res.push_back(324);*/

	for (int ii = 0; ii < 81; ii++)
	{
		if (matric[ii] != 0)
		{
			addrow(ii + 1, matric[ii], ++linkrow, exa, index);
		}
		else
		{
			for (int jj = 1; jj < 10; jj++)
			{
				addrow(ii + 1, jj, ++linkrow, exa, index);
			}
		}
	}

	return linkrow;
}