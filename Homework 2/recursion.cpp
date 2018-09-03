#include <string>
#include <iostream>
#include <cassert>
using namespace std;
int mult(unsigned int m, unsigned int n);
int countDigit(int num, int digit);
string pairStars(string n);
string subBrackets(string str);
bool comboSum(const int a[], int size, int target); // you can literally do it in three lines
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

int mult(unsigned int m, unsigned int n)
{
	if (n == 0 || m == 0)
		return 0;
	else if (m == 1)
		return n;
	else if (n == 1)
		return m;
	return m + mult(m, n - 1);
}
int countDigit(int num, int digit)
{
	if (num == digit)
		return 1;
	else if (num == 0)
	{
		if (digit == 0)
			return 1;
		else
			return 0;
	}

	if (num % 10 == digit) // 767  and 7
		return 1 + countDigit(num / 10, digit);
	return countDigit(num / 10, digit);
}
string pairStars(string n)
{
	if (n.size() == 0 || n.size() == 1) // base case
		return n;
	if (n[0] == n[1])
		return n.substr(0, 1) + "**" + pairStars(n.substr(1, n.size() - 1));
	return n.substr(0, 1) + pairStars(n.substr(1, n.size() - 1));
}
string subBrackets(string str)
{
	if (str[0] != '[')
	{
		return subBrackets(str.substr(1, str.size() - 1)); // omitting str.size() - 1 is okay too
		/*
		we could have put this before the return line in this if statement, but redundant
		if (str[str.size() - 1] != ']')
			return subBrackets(str.substr(1, str.size() - 1));
		*/
	}
	if (str[str.size() - 1] != ']')
		return subBrackets(str.substr(0, str.size() - 1));
	return str;
}
bool comboSum(const int a[], int size, int target)
{
	// int size is the exit condition
	// Base Cases:
	if (target == 0)
		return true;
	if (!(size != 0 || target == 0)) 
		return false;
	// if (size != 0) == false && (target == 0) == false
	
	// Ignore the last element if its larger than the desired sum
	if (!(a[size - 1] <= target))
		return comboSum(a, size - 1, target);
	
	// otherwise, check if sum can be obtained by including the last element or omitting the last element   
	
	bool cond = comboSum(a, size - 1, target); // including
	bool cond2 = comboSum(a, size - 1, target - a[size - 1]); // excluding
	return (cond || cond2);
}
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)
		return true;

	// mark the location as visited
	maze[sr][sc] = 'V';

	// checking north:
	if (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec) != false)
		return true;
	// check south
	if (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec) != false)
		return true;
	// check east
	if (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec) != false)
		return true;
	// check west
	if (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec) != false)
		return true;

	return false;
}

int main()
{
	unsigned int x = mult(3, 5);
	cout << x << endl;
	int y = countDigit(2772797, 7);
	cout << y << endl;

	cout << pairStars("yyuu") << endl;
	cout << pairStars("goodbye") << endl;
	cout << pairStars("aaaa") << endl;
	cout << subBrackets("aaa[ghj]nnn") << endl;
	cout << subBrackets("[ghj]nnn") << endl;
	cout << subBrackets("[ghj]") << endl;
	cout << subBrackets("aaa[ghj]") << endl;
	cout << subBrackets("[x]7") << endl;
	cout << subBrackets("4agh[y]") << endl;
	int a[] = { 2, 8, 4 };
	if (comboSum(a, 3, 8))
		cout << "True" << endl;
	if (comboSum(a, 3, 14))
		cout << "True" << endl;
	if (!comboSum(a, 3, 11))
		cout << "False" << endl;
	int b[1];
	if (comboSum(b, 0, 0))
		cout << "True" << endl;
	int c[] = {0, 0, 0};
	if (comboSum(c, 0, 0))
		cout << "True" << endl;
	string maze[10] = {
		"XXXXXXXXXX",
		"X.......@X",
		"XX@X@@.XXX",
		"X..X.X...X",
		"X..X...@.X",
		"X....XXX.X",
		"X@X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
