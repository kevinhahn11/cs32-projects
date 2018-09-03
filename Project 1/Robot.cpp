#include "Robot.h" 
#include "Arena.h" // we used the Arena::rows and cols functions
#include "globals.h" // we used global constants
#include <iostream> // we wrote to cout
#include <cstdlib> // because we used exit()
using namespace std;

Robot::Robot(Arena* ap, int r, int c)
{
	if (ap == nullptr)
	{
		std::cout << "***** A robot must be in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		std::cout << "***** Robot created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}
	m_arena = ap;
	m_row = r;
	m_col = c;
	m_health = INITIAL_ROBOT_HEALTH;
}

int Robot::row() const
{
	return m_row;
}

int Robot::col() const
{
	return m_col;
}

void Robot::move()
{
	// Attempt to move in a random direction; if we can't move, don't move
	switch (rand() % 4)
	{
	case UP:     if (m_row > 1)               m_row--; break;
	case DOWN:   if (m_row < m_arena->rows()) m_row++; break;
	case LEFT:   if (m_col > 1)               m_col--; break;
	case RIGHT:  if (m_col < m_arena->cols()) m_col++; break;
	}
}

bool Robot::takeDamageAndLive()  // return true if not yet dead
{
	if (m_health > 0)
		m_health--;
	return m_health > 0;
}