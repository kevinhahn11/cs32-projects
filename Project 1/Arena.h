#ifndef ARENA_HEADER

#define ARENA_HEADER

#include "Past.h" // we define a variable of type Past
#include "globals.h" // we used MAXROBOTS
#include <string> // parameter to a function

class Player; // We use a pointer to Player
class Robot; // We use a pointer to an array of Robots

class Arena
{
public:
	// Constructor/destructor
	Arena(int nRows, int nCols);
	~Arena();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     robotCount() const;
	int     nRobotsAt(int r, int c) const;
	void    display(std::string msg) const;
	Past& thePast();

	// Mutators
	bool   addRobot(int r, int c);
	bool   addPlayer(int r, int c);
	void   damageRobotAt(int r, int c);
	bool   moveRobots();

private:
	int     m_rows;
	int     m_cols;
	Player* m_player;
	Robot*  m_robots[MAXROBOTS];
	int     m_nRobots;
	Past m_past;
};

#endif