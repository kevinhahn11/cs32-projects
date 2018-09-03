#include "Past.h" 
#include "globals.h" // clearScreen function is used
#include <iostream> // we used cout function
using namespace std;
Past::Past(int nRows, int nCols)
{
	// Assume the args will not exceed the MAXROWS and MAXCOLS and will be >= 1
	p_rows = nRows;
	p_cols = nCols;
	for (int r = 0; r < p_rows; r++)
		for (int c = 0; c < p_cols; c++)
			p_grid[r][c] = '.';
}

bool Past::markIt(int r, int c)
{
	if ((r >= 1 && r <= p_rows) && (c >= 1 && c <= p_cols))
	{
		if (p_grid[r - 1][c - 1] == 'Z')
			p_grid[r - 1][c - 1] = 'Z';
		else if (p_grid[r - 1][c - 1] >= 'A' && p_grid[r - 1][c - 1] < 'Z')
			p_grid[r - 1][c - 1] += 1;
		else
			p_grid[r - 1][c - 1] = 'A';

		return true;
	}
	else
	{
		return false;
	}
}

void Past::printThePast() const
{
	clearScreen();
	for (int r = 1; r <= p_rows; r++)
	{
		for (int c = 1; c <= p_cols; c++)
		{
			cout << p_grid[r-1][c-1];
		}
		cout << endl;
	}
	cout << endl;
}