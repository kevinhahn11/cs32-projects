// StudentWorld.cpp
#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
GameWorld* createStudentWorld(string assetDir) { return new StudentWorld(assetDir); }

// StudentWorld class
// Private member functions:
void StudentWorld::destroyTheEarth()
{
	for (int col = 0; col < VIEW_WIDTH; col++)
	{
		for (int row = 0; row < 60; row++)
		{
			if (earthPtrs[row][col] != nullptr)
			{
				delete earthPtrs[row][col];
				earthPtrs[row][col] = nullptr; // just in case.
			}
		}
	}
}
void StudentWorld::replenishTheEarth()
{
	for (int col = 0; col < VIEW_WIDTH; col++)
	{
		for (int row = 0; row < 60; row++)
		{
			//earthPtrs[col][row] = new Earth(this, col, row);
			if (row >= 4 && col >= 30 && col <= 33)
				continue;
			if (earthPtrs[col][row] == nullptr)
				earthPtrs[col][row] = new Earth(this, col, row);
		}
	}
}
int StudentWorld::generateRandomNum(int min, int max) const
{
	// generates a random between min and max, inclusive.
	return rand() % (max - min + 1) + min;
}
double StudentWorld::euclideanDist(int x1, int y1, int x2, int y2) const
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void StudentWorld::removeDeadActors()
{
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->isAlive() != true)
		{
			delete (*it);
			it = actors.erase(it);
		}
		else
			it++;
	}
	/*
	while (it != actors.end())
	{
	if ((*it)->isAlive() == false)
	{
	(*it)->~Actor();
	actors.erase(it);
	it = actors.begin();
	}
	if (it == actors.end())
	break;

	it++;
	}
	*/
}
// Public member functions
StudentWorld::StudentWorld(std::string assetDir)
	: GameWorld(assetDir), digger(nullptr), m_tickCount(0),
	m_boulderTicks(0), m_nuggetTicks(0), m_sonarTicks(0), m_waterpoolTicks(0)
{
}
// Initializer:
int StudentWorld::init()
{
	m_tickCount = 0;
	m_boulderTicks = 0;
	m_nuggetTicks = 0;
	m_sonarTicks = 0;
	m_waterpoolTicks = 0;
	m_probOfGoodie = 1.0 / (getLevel() * 25 + 300);
	m_probOfHardcore = min(90, ((int)getLevel()) * 10 + 30);
	/*
	We must
	1. Initialize the data structures used to keep track of our game's virtual world
	2. Construct a new oil field that meets the requirements
	3. Allocate and insert a valid tunnelman object into the game world at the proper location
	*/
	digger = new Tunnelman(this);
	// Draw the oil field:
	replenishTheEarth();

	// Create the boulders first:
	int numberOfBoulders = min(((int)getLevel()) / 2 + 2, 9);

	for (int i = 0; i < numberOfBoulders; i++)
	{
		int x = generateRandomNum(0, 60), y = generateRandomNum(20, 56);
		if (actors.empty())
		{
			while (x >= 27 && x <= 33)
			{
				x = generateRandomNum(0, 60);
				y = generateRandomNum(20, 56);
			}

			actors.push_back(new Boulder(this, x, y));
		}
		else
		{
			vector<Actor*>::iterator it = actors.begin();
			bool needsNewValues = false;
			while (it != actors.end())
			{
				if (needsNewValues == true)
				{
					x = generateRandomNum(0, 60);
					y = generateRandomNum(20, 56);
				}
				if ((*it)->isDistributedObject())
				{
					while (x >= 27 && x <= 33)
					{
						x = generateRandomNum(0, 60);
						y = generateRandomNum(20, 56);
					}
					if (euclideanDist((*it)->getX(), (*it)->getY(), x, y) <= 6)
					{
						it = actors.begin();
						needsNewValues = true;
						continue;
					}
					else
					{
						it++;
						needsNewValues = false;
						continue;
					}
				}
			} // end while
			actors.push_back(new Boulder(this, x, y));
		}
	} // end for
	  /*
	  actors.push_back(new Boulder(this, 26, 30));
	  actors.push_back(new Boulder(this, 26, 40));
	  actors.push_back(new Boulder(this, 34, 10));
	  actors.push_back(new SonarKit(this, 30, 10));
	  actors.push_back(new WaterPool(this, 30, 16));

	  */

	int numberOfGoldNuggets = max(5 - (((int)getLevel()) / 2), 2);
	//actors.push_back(new GoldNugget(this, 30, 40, false, true, true));

	for (int i = 0; i < numberOfGoldNuggets; i++)
	{
		int x = generateRandomNum(0, 60);
		int y = generateRandomNum(0, 56);
		vector<Actor*>::iterator it = actors.begin();
		bool g_needsNewValues = false;
		while (it != actors.end())
		{
			if (g_needsNewValues == true)
			{
				x = generateRandomNum(0, 60), y = generateRandomNum(0, 56);
			}
			if ((*it)->isDistributedObject())
			{
				while (x >= 27 && x <= 33)
				{
					x = generateRandomNum(0, 60);
					y = generateRandomNum(0, 56);
				}
				if (euclideanDist((*it)->getX(), (*it)->getY(), x, y) <= 6)
				{
					it = actors.begin();
					g_needsNewValues = true;
					continue;
				}
				else
				{
					it++;
					g_needsNewValues = false;
					continue;
				}
			}
		} // end while
		actors.push_back(new GoldNugget(this, x, y, false, true, true));
	}

	m_barrelsRemaining = min(2 + (int)getLevel(), 21);
	for (int i = 0; i < m_barrelsRemaining; i++)
	{
		int x = generateRandomNum(0, 60), y = generateRandomNum(0, 56);
		vector<Actor*>::iterator it = actors.begin();
		bool b_needsNewValues = false;
		while (it != actors.end())
		{
			if (b_needsNewValues == true)
			{
				x = generateRandomNum(0, 60);
				y = generateRandomNum(0, 56);
			}
			if ((*it)->isDistributedObject())
			{
				while (x >= 27 && x <= 33)
				{
					x = generateRandomNum(0, 60);
					y = generateRandomNum(0, 56);
				}
				if (euclideanDist((*it)->getX(), (*it)->getY(), x, y) <= 6)
				{
					it = actors.begin();
					b_needsNewValues = true;
					continue;
				}
				else
				{
					it++;
					b_needsNewValues = false;
					continue;
				}
			}
		} // end while
		actors.push_back(new Barrel(this, x, y));
	}
	if (!(rand() % 100 < min(90, (int)getLevel() * 10 + 30)))
		actors.push_back(new RegularProtester(this, TID_PROTESTER));
	else
	{
		actors.push_back(new HardcoreProtester(this, TID_HARD_CORE_PROTESTER));
	}

	return GWSTATUS_CONTINUE_GAME;
}
// Move() function:
int StudentWorld::move()
{
	setGameStatText(getInfo()); // update the score/lives/level text at the top of screen
								// chances of adding a new sonarkit or water pool during each tick

								// check to see if tunnelman is alive

	if (!digger->isAlive())
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	//digger->doSomething();
	vector<Actor*>::iterator i = actors.begin();
	while (i != actors.end())
	{
		if ((*i)->isAlive())
		{
			(*i)->doSomething();
			if (!digger->isAlive())
				return GWSTATUS_PLAYER_DIED;
			if (m_barrelsRemaining == 0)
				return GWSTATUS_FINISHED_LEVEL;
		}
		i++;
	}
	removeDeadActors();

	digger->doSomething();
	if (digger->isAlive() == false)
		return GWSTATUS_PLAYER_DIED;
	if (m_barrelsRemaining == 0)
	{
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}


	m_boulderTicks++;
	m_tickCount++;
	m_sonarTicks++;
	m_waterpoolTicks++;
	if ((rand() % (getLevel() * 25 + 300)) == 1)
	{
		if (rand() % 5 == 1)
		{
			int x = generateRandomNum(0, 60);
			int y = generateRandomNum(0, 60);
			while (canPlaceHere(x, y) == false)
			{
				x = generateRandomNum(0, 60);
				y = generateRandomNum(0, 60);
			}
			actors.push_back(new SonarKit(this, 60, 60));
		}
		else
		{
			int x = generateRandomNum(0, 60);
			int y = generateRandomNum(0, 60);
			while (canPlaceHere(x, y) == false)
			{
				x = generateRandomNum(0, 60);
				y = generateRandomNum(0, 60);
			}
			actors.push_back(new WaterPool(this, x, y));
		}
	}

	//digger->doSomething();
	return GWSTATUS_CONTINUE_GAME;
}
// Cleanup function:
void StudentWorld::cleanUp()
{
	setAllActorsToDead();
	removeDeadActors();
	//destroyTheEarth();
	if (digger != nullptr || digger->isAlive() == false)
	{
		delete digger;
		digger = nullptr;
	}


}
void StudentWorld::setAllActorsToDead()
{
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		(*it)->setToDead();
		it++;
	}
}

// Displaying the scoreline (accessor function):
std::string StudentWorld::getInfo() const {
	ostringstream oss;
	oss << "Scr: " << setfill('0') << setw(6) << getScore() << "  ";
	oss << "Lvl: " << setfill(' ') << setw(2) << getLevel();
	oss << "  " << "Lives: " << setw(1) << getLives();
	oss << "  " << "Hlth: " << setfill(' ') << setw(3) << getTunnelman()->getHP() * 10 << "%";
	oss << "  " << "Wtr: " << setfill(' ') << setw(2) << getTunnelman()->getSquirts();
	oss << "  " << "Gld: " << setfill(' ') << setw(2) << getTunnelman()->getNuggetCount();
	oss << "  " << "Sonar: " << setfill(' ') << setw(2) << getTunnelman()->getSonarCharges();
	oss << "  " << "Oil Left:" << setfill(' ') << setw(2) << getBarrels();
	return oss.str();
}
//////////////////////
// Tick Resetters
void StudentWorld::addActor(Actor* a) { actors.push_back(a); }
void StudentWorld::resetTickCount() { m_tickCount = 0; }
void StudentWorld::resetBoulderTicks() { m_boulderTicks = 0; }
void StudentWorld::resetNuggetTicks() { m_nuggetTicks = 0; }
void StudentWorld::resetSonarTicks() { m_sonarTicks = 0; }
void StudentWorld::resetWaterPoolTicks() { m_waterpoolTicks = 0; }
///////////////////////
// Tick Incrementers:
void StudentWorld::incrementNuggetTicks() { m_nuggetTicks++; }
void StudentWorld::incrementBoulderTicks() { m_boulderTicks++; }
void StudentWorld::incrementSonarTicks() { m_sonarTicks++; }
void StudentWorld::incrementWaterPoolTicks() { m_waterpoolTicks++; }
///////////////////////
// Tick Accessors:
int StudentWorld::getTicks() const { return m_tickCount; }
int StudentWorld::getBoulderTicks() const { return m_boulderTicks; }
int StudentWorld::getNuggetTicks() const { return m_nuggetTicks; }
int StudentWorld::getWaitingTick() const { return m_ticksToWaitBetweenMoves; }
int StudentWorld::getSonarTicks() const { return m_sonarTicks; }
int StudentWorld::getWaterPoolTicks() const { return m_waterpoolTicks; }
///////////////////////////////////
// Destructor and removing earth:
StudentWorld::~StudentWorld() {
	if (digger != nullptr)
		delete digger;
	removeDeadActors();
	destroyTheEarth();
}
void StudentWorld::barrelWasPickedUp() { m_barrelsRemaining--; }
int StudentWorld::getBarrels() const { return m_barrelsRemaining; }
void StudentWorld::illuminate(int x, int y) // reveals all pickupable objects within a radius of 12
{
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->isPickupable() && (*it)->getRadius(x, y, (*it)->getX(), (*it)->getY()) <= 12)
			(*it)->setVisible(true);
		it++;
	}
}
/////////////////
/// new stuff:
Tunnelman* StudentWorld::findNearbyTM(int radius, Actor* a) const
{
	if (euclideanDist(a->getX(), a->getY(), digger->getX(), digger->getY()) <= radius)
		return digger;
	else
		return nullptr;
}
bool StudentWorld::canPlaceHere(int x, int y)
{
	for (int col = x; col < x + 4; col++)
	{
		for (int row = y; row < y + 4; row++)
		{
			if (earthPtrs[col][row] != nullptr)
				return false;
		}
	}
	for (vector<Actor*>::iterator it = actors.begin(); it != actors.end(); it++)
	{
		if ((*it)->isDistributedObject() && euclideanDist(x, y, (*it)->getX(), (*it)->getY()) <= 6)
			return false;
	}
	return true;
}
void StudentWorld::removeEarth(int col, int row) {
	if (col >= 0 && col < 64 && row >= 0 && row < 60) {
		if (this->earthPtrs[col][row] != nullptr) {
			delete earthPtrs[col][row];
			this->earthPtrs[col][row] = nullptr;
		}
	}
	return;
}
bool StudentWorld::isThereOneByFourEarth(int x, int y) const
{
	// Sanity check: x's coordinates are 0 <= x <= 63
	if (x < 0 || x > 63 || y < 0 || y > 63)
		return true;
	// Check the earth grid:
	for (int i = y; i < y + 4; i++)
		if (earthPtrs[x][i] != nullptr)
			return true;
	// Otherwise:
	return false;
	/*
	Checks for 1 x 4 a tower of dirt
	.
	.
	.
	.
	*/

}
bool StudentWorld::isThereFourByOneEarth(int x, int y) const
{
	/*
	Checks if there is a 4 x 1 mat of dirt for the boulder to fall on:
	----
	*/
	// Sanity check: x's coordinates are 0 <= x <= 63
	if (x > 63 || x < 0 || y < 0 || y > 63)
		return false;
	// Check the earth grid:
	for (int i = x; i < x + 4; i++)
		if (earthPtrs[i][y] != nullptr)
			return true;
	// Otherwise:
	return false;
}


// Accessors:

Tunnelman* StudentWorld::getTunnelman() const
{
	if (digger == nullptr)
		return nullptr;
	return digger;
}

bool StudentWorld::isEarthPresent(int col, int row) {
	if (col >= 0 && col < 64 && row >= 0 && row < 60) {
		if (earthPtrs[col][row] != nullptr)
			return true;
	}
	return false;
}
bool StudentWorld::isThereEarthFourByFour(int x, int xFinal, int y, int yFinal) const
{
	// for 4 x 4 square objects
	if (x < 0 || x > 63 || xFinal > 63 || xFinal < 0 || y < 0 || y > 63 || yFinal > 63 || yFinal < 0)
		return false;
	for (int i = x; i <= xFinal; i++)
	{
		for (int j = y; j <= yFinal; j++)
		{
			if (earthPtrs[i][j] != nullptr)
				return true;
		}
	}
	return false;
}
bool StudentWorld::isBoulderPresent(int x, int y) const
{
	vector<Actor*>::const_iterator it = actors.begin();
	GraphObject::Direction d = digger->getDirection();
	while (it != actors.end())
	{
		if ((*it)->isObstacle())
		{
			//if ((*it)->getX() == x && (*it)->getY() == y)
			//return true;
			if (d == GraphObject::right)
			{
				if (euclideanDist((*it)->getX(), (*it)->getY(), x, y) <= 3)
					return true;
			}
			else
			{
				if (euclideanDist((*it)->getX() + 2, (*it)->getY() + 2, x + 2, y + 2) <= 3)
					return true;
			}
		}
		// proceed to next item
		it++;
	}
	return false;
}
bool StudentWorld::isBoulderPresent2(int x, int y) const
{
	vector<Actor*>::const_iterator it = actors.begin();
	GraphObject::Direction d = digger->getDirection();
	while (it != actors.end())
	{
		if ((*it)->isObstacle())
		{
			//if ((*it)->getX() == x && (*it)->getY() == y)
			//return true;
			if (d == GraphObject::right)
			{
				if (euclideanDist((*it)->getX(), (*it)->getY(), x, y) <= 3)
					return true;
			}
			else
			{
				if (euclideanDist((*it)->getX(), (*it)->getY(), x, y) <= 3)
					return true;
			}
		}
		// proceed to next item
		it++;
	}
	return false;
}
bool StudentWorld::amIDiggingIntoBoulder(int x, int y) const
{
	vector<Actor*>::const_iterator it = actors.begin();
	GraphObject::Direction d = digger->getDirection();
	while (it != actors.end())
	{
		if ((*it)->isObstacle())
		{
			if (euclideanDist((*it)->getX() + 2, (*it)->getY() + 2, x + 2, y + 2) <= 3)
				return true;
		}
		// proceed to next item
		it++;
	}
	return false;
}
////////////////////////////////////
Actor* StudentWorld::getNearbyProtester(Actor* a, int radius)
{
	for (vector<Actor*>::iterator it = actors.begin(); it != actors.end(); it++)
		if ((*it)->isProtester() && euclideanDist(a->getX(), a->getY(), (*it)->getX(), (*it)->getY()) <= radius)
			return (*it);
	return nullptr;

}
bool StudentWorld::canMoveTo(int x, int y, GraphObject::Direction dir)
{
	/*
	int m = x; int n = y;
	if (dir == GraphObject::up)
	n++;
	else if (dir == GraphObject::down)
	n--;
	else if (dir == GraphObject::left)
	m--;
	else if (dir == GraphObject::right)
	m++;

	if (!(m >= 0 && m < 60) && !(n >= 0 && n < 60))
	return false;
	*/
	return true;
}
bool StudentWorld::isFacingTunnelman(Actor* a) const
{
	/*
	if (a->getX() == digger->getX() && a->getY() == digger->getY())
	return true;
	else
	{
	GraphObject::Direction dir = a->getDirection();
	if (dir == GraphObject::right)
	{
	if (digger->getX() > a->getX())
	return true;
	else
	return false;
	}
	else if (dir == GraphObject::left)
	{
	if (digger->getX() < a->getX())
	return true;
	else
	return false;
	}
	else if (dir == GraphObject::up)
	{
	if (digger->getY() > a->getY())
	return true;
	else
	return false;
	}
	else if (dir == GraphObject::down)
	{
	if (digger->getY() < a->getY())
	return true;
	else
	return false;
	}
	else
	{
	return false;
	}

	}
	*/
	return true;
}
GraphObject::Direction StudentWorld::getLineOfSightToTunnelman(Actor* protester) const
{
	if (digger->getX() != protester->getX() && digger->getY() != protester->getY())
		return GraphObject::none;
	else if (protester->getX() == digger->getX())
	{
		if (protester->getY() < digger->getY())
			return GraphObject::up;
		else if (protester->getY() > digger->getY())
			return GraphObject::down;
		else
			return GraphObject::none;
	}
	else if (protester->getY() == digger->getY())
	{
		if (protester->getX() < digger->getX())
			return GraphObject::right;
		else if (protester->getX() > digger->getX())
			return GraphObject::left;
		else
			return GraphObject::none;
	}
	else
	{
		return GraphObject::none;
	}
}
GraphObject::Direction StudentWorld::determineMoveToExit(int a, int b)
{
	return GraphObject::none;
}
GraphObject::Direction StudentWorld::determineMoveToTunnelman(int a, int b, int M)
{
	return GraphObject::none;
}
bool StudentWorld::inValidZone(int x, int y, int startX, int endX, int startY, int endY) const
{
	//return (x >= startX && x <= endX && y >= startY && y <= endY);
	return true;
}
void StudentWorld::findPath(int xFinal, int yFinal, GraphObject::Direction map[64][64], int distance)
{
	return;
}
