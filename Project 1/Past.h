#ifndef PAST_HEADER
#define PAST_HEADER
#include "globals.h" // we used MAXROWS and MAXCOLS
class Past
{
public:
	Past(int nRows, int nCols);
	bool markIt(int r, int c);
	void printThePast() const;
private:
	int p_rows;
	int p_cols;
	char p_grid[MAXROWS][MAXCOLS];
};
#endif

