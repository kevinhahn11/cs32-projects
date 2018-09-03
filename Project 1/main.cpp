/*
// Test Case 1
#include "Game.h"
#include "Game.h"
#include "Arena.h"
#include "Arena.h"
#include "Past.h"
#include "Past.h"
#include "Player.h"
#include "Player.h"
#include "Robot.h"
#include "Robot.h"
#include "globals.h"
#include "globals.h"

int main()
{}
*/
/////////////////////////////
/*
// Test Case 2
#include "Past.h"
int main()
{
	Past pt(2, 2);
	pt.markIt(1, 1);
	pt.printThePast();
}
*/
/////////////////////
/*
// Test Case 3
#include "Robot.h"
int main()
{
	Robot r(0, 1, 1);
}
*/
///////////////////
/*
// Test Case 4
#include "Player.h"
int main()
{
	Player p(0, 1, 1);
}
*/
///////////////////
/*
// Test Case 5
#include "Arena.h"
int main()
{
	Arena a(10, 18);
	a.addPlayer(2, 2);
}
*/
//////////////////
/*
// Test Case 6
#include "globals.h"
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/
/////////////////
/*
// Test Case 7
#include "Arena.h"
#include "Player.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/
/////////////////
/*
// Test Case 8
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/
////////////////
/* Problem
// Test Case 9: should print 
.B
.A
		// empty line

#include "Arena.h"
#include "Player.h"
#include "Past.h"
#include "globals.h"

int main()
{
	Arena a(2, 2);
	a.addPlayer(1, 1);
	a.player()->move(RIGHT);
	a.player()->stand();
	a.player()->move(DOWN);
	a.thePast().printThePast();
}
*/
//////////////////
/*
// Test Case 10 - should not build successfully
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
	Robot r(&a, 1, 1);
}
*/
//////////////////
/*
// Test Case 11: should not build successfully
#include "globals.h"
#include "Robot.h"
#include "Player.h"
int main()
{
	Arena a(10, 10);
}
*/
//////////////////
/*
// Test Case 12: should not build successfully
#include "Past.h"
int main()
{
	Past pt;
}
*/
//////////////////////////////////////////////////////////////////
// end of test cases
//////////////////////////////////////////////////////////////////

// Original solution below:

// zion_solution.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "globals.h"
#include "Robot.h"
#include "Player.h"
#include "Arena.h"
#include "Past.h"

#include "Game.h"
using namespace std;

int main()
{
	// Initialize the random number generator.  (You don't need to
	// understand how this works.)
	srand(static_cast<unsigned int>(time(0)));

	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 3, 2);
	Game g(15, 18, 1);

	// Play the game
	g.play();
}
