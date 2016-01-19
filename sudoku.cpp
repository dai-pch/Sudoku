// sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

bool debug = false;

int _tmain(int argc, _TCHAR* argv[])
{
	int su[81] = { 0 };/*{ 3, 0, 2, 0, 0, 0, 9, 0, 0,
		0, 0, 0, 3, 0, 4, 0, 0, 0,
		8, 0, 0, 0, 7, 9, 0, 3, 0,
		0, 0, 5, 0, 0, 0, 0, 2, 4,
		4, 0, 0, 7, 0, 8, 0, 0, 1,
		9, 3, 0, 0, 0, 0, 7, 0, 0,
		0, 9, 0, 6, 4, 0, 0, 0, 5,
		0, 0, 0, 1, 0, 3, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 4, 0, 3, };*/
	std::vector<nonzeroposition> exa;
	std::vector<int> res;
	std::vector<element> index;
	Head *dl = nullptr;
	int solvedsudoku[81];
	int exarownum;
	int ii = 0, jj = 0, temp;

	//Command line parameter handling
	bool printtime = false, aut = false;
	for (ii = 1; ii < argc; ii++)
	{
		if (_tcscmp(argv[ii], _TEXT("-t")) == 0)
			printtime = true;
		if (_tcscmp(argv[ii], _TEXT("-a")) == 0)
			aut = true;
		if (_tcscmp(argv[ii], _TEXT("-d")) == 0)
			debug = true;
	}

	if (!aut)
		std::cout << "Please input the sudoku matrix(9*9)" << std::endl << "Use 0 instead of the unknown number:" << std::endl;

	for (ii = 0; ii < 81; ii++)
	{
		std::cin >> temp;
		if (temp >= 0 && temp <= 9)
		{
			su[ii] = temp;
		}
		else
			ii--;
	}

	if (debug)
	{
		std::cout << "The input matrix is:" << std::endl;
		for (ii = 0; ii < 9; ii++)
		{
			for (jj = 0; jj < 9; jj++)
				std::cout << su[ii * 9 + jj] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	exarownum = convert(su, exa, index);

	if (debug)
	{
		std::cout << "The exactcover problem is:" << std::endl;
		for (ii = 0; ii < exarownum; ii++)
		{
			std::cout << exa.at(ii);
			if (ii % 12 == 11)
				std::cout << std::endl;
		}

		std::cout << std::endl << "The index is:" << std::endl;
		for (ii = 0; ii < exarownum; ii++)
		{
			std::cout << ii + 1 << ":" << index.at(ii);
			if (ii % 10 == 9)
				std::cout << std::endl;
		}
		std::cout << std::endl << std::endl << "Begain to solve exactcover:" << std::endl;
	}

	dl = new Head(exa, exarownum, 324);
	solveexactcover(*dl, res);
	delete dl;

	if (res.at(0) != 0)
	{
		for (ii = 0; ii < 81; ii++)
			solvedsudoku[index.at(res.at(ii) - 1).position - 1] = index.at(res.at(ii) - 1).number;

		if (!aut || debug)
			std::cout << std::endl << "The result is:" << std::endl;
		for (ii = 0; ii < 9; ii++)
		{
			for (int jj = 0; jj < 9; jj++)
				std::cout << solvedsudoku[ii * 9 + jj] << " ";
			std::cout << std::endl;
		}
	}
	else
		std::cout << "There is no solution." << std::endl;

	if (!aut)
		system("Pause");
	return 0;
}

