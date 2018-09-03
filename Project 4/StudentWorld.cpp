// StudentWorld.cpp
#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
GameWorld* createStudentWorld(string assetDir) { return new StudentWorld(assetDir); }

// StudentWorld class
// Private member functions:
int StudentWorld::generateRandomNum(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
double StudentWorld::euclideanDist(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void StudentWorld::removeDeadActors()
{
	vector<Actor*>::iterator it = actors.begin();
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
}
// Public member functions
StudentWorld::StudentWorld(std::string assetDir)
	: GameWorld(assetDir), digger(nullptr), m_tickCount(0)
{
}
// Initializer:
int StudentWorld::init()
{
	m_tickCount = 0;
	/*
	We must
	1. Initialize the data structures used to keep track of our game's virtual world
	2. Construct a new oil field that meets the requirements
	3. Allocate and insert a valid tunnelman object into the game world at the proper location
	*/
	digger = new Tunnelman(this);
	// Draw the oil field:
	for (int col = 0; col < VIEW_WIDTH; col++)
	{
		for (int row = 0; row < 60; row++)
		{
			//earthPtrs[col][row] = new Earth(this, col, row);
			if (row >= 4 && col >= 30 && col <= 33)
				continue;
			earthPtrs[col][row] = new Earth(this, col, row);
		}
	}
	actors.push_back(new SonarKit(this, 30, 10));
	actors.push_back(new WaterPool(this, 30, 16));
	actors.push_back(new GoldNugget(this, 30, 40, false, true, true));
	int levelNum = getLevel();
	int numberOfBoulders = min(levelNum / 2 + 2, 9);
	/*
	for (int i = 0; i < numberOfBoulders; i++)
	{
		int x = generateRandomNum(0, 60), y = generateRandomNum(20, 56);
		vector<Actor*>::iterator it = actors.begin();
		while (it != actors.end())
		{
			if ((*it)->isDistributedObject())
			{
				if (euclideanDist(x, y, (*it)->getX(), (*it)->getY()) > 6 && !(x >= 27 && x <= 33))
				{
					it++;
					continue;
				}
				x = generateRandomNum(0, 60);
				y = generateRandomNum(20, 56);
				it = actors.begin();
				continue;
			}
			it++;
		}
		actors.push_back(new Boulder(this, x, y));
	}
	*/
	
	actors.push_back(new Boulder(this, 26, 30));
	actors.push_back(new Boulder(this, 26, 40));
	actors.push_back(new Boulder(this, 34, 10));
	
	/*
	int numberOfGoldNuggets = max(5 - levelNum / 2, 2);

	for (int i = 0; i < numberOfGoldNuggets; i++)
	{
	int x = generateRandomNum(0, 60);
	int y = generateRandomNum(0, 56);
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
	if ((*it)->isDistributedObject())
	{
	if (euclideanDist(x, y, (*it)->getX(), (*it)->getY()) > 6 && !(x >= 27 && x <= 33))
	{
	it++;
	continue;
	}
	x = generateRandomNum(0, 60);
	y = generateRandomNum(20, 56);
	it = actors.begin();
	continue;
	}
	it++;
	}
	actors.push_back(new GoldNugget(this, x, y, false, true, true));
	}
	*/
	m_barrelsRemaining = min(2 + levelNum, 21);
	for (int i = 0; i < m_barrelsRemaining; i++)
	{
		int x = generateRandomNum(0, 60), y = generateRandomNum(20, 56);
		vector<Actor*>::iterator it = actors.begin();
		while (it != actors.end())
		{
			if ((*it)->isDistributedObject())
			{
				if (euclideanDist(x, y, (*it)->getX(), (*it)->getY()) > 6 && !(x >= 27 && x <= 33))
				{
					it++;
					continue;
				}
				x = generateRandomNum(0, 60);
				y = generateRandomNum(20, 56);
				it = actors.begin();
				continue;
			}
			it++;
		}
		actors.push_back(new Barrel(this, x, y));
	}

	return GWSTATUS_CONTINUE_GAME;
}
// Move() function:
int StudentWorld::move()
{
	setGameStatText(getInfo()); // update the score/lives/level text at the top of screen
	m_tickCount++;
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level:
	//decLives();
	//return GWSTATUS_PLAYER_DIED;
	digger->doSomething();
	if (!digger->isAlive())
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

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

	if (digger->isAlive() == false)
		return GWSTATUS_PLAYER_DIED;
	if (m_barrelsRemaining == 0)
	{
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}

	return GWSTATUS_CONTINUE_GAME;
}
// Cleanup function:
void StudentWorld::cleanUp()
{
	if (digger != nullptr || digger->isAlive() == false)
	{
		delete digger;
		digger = nullptr;
	}
	//setAllActorsToDead();
	//removeDeadActors();
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		(*it)->~Actor();
		actors.erase(it);
		it = actors.begin();
		
		if (it == actors.end())
			break;

		it++;
	}
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
	oss << "Lvl: " << getLevel() << " Lives: " << getLives();
	oss << " Health: " << getTunnelman()->getHP() * 10 << "% " << "Wtr: " << getTunnelman()->getSquirts() << " Gld: "
		<< getTunnelman()->getNuggetCount();
	oss << " Oil Left: " << getBarrels() << " Sonar: " << getTunnelman()->getSonarCharges()
		<< " Scr: " << getScore();
	return oss.str();
}
// Mutators:
void StudentWorld::addActor(Actor* a) { actors.push_back(a); }
void StudentWorld::resetTickCount() { m_tickCount = 0; }
StudentWorld::~StudentWorld() {
	if (digger != nullptr)
		delete digger;
	removeDeadActors();
	for (int col = 0; col < VIEW_WIDTH; col++) {
		for (int row = 0; row < 60; row++) {
			if (earthPtrs[row][col] != nullptr) {
				delete earthPtrs[row][col];
				earthPtrs[row][col] = nullptr; // just in case.
			}
		}
	}
}
void StudentWorld::barrelWasPickedUp() { m_barrelsRemaining--; }
void StudentWorld::illuminate(int x, int y)
{
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->isPickupable() && (*it)->getRadius(x, y, (*it)->getX(), (*it)->getY()) <= 12)
			(*it)->setVisible(true);
		it++;
	}
}
void StudentWorld::removeEarthFBF(int x, int xFinal, int y, int yFinal)
{
	if (x < 0 || x > 63 || xFinal > 63 || xFinal < 0 || y < 0 || y > 59 || yFinal > 59 || yFinal < 0)
		return;
	for (; x <= xFinal; x++)
		for (; y <= yFinal; y++)
			if (earthPtrs[x][y] != nullptr)
				delete earthPtrs[x][y];
}
void StudentWorld::removeEarth(int col, int row) {
	if (col >= 0 && col < 64 && row >= 0 && row < 60) {
		if (earthPtrs[col][row] != nullptr) {
			delete earthPtrs[col][row];
			earthPtrs[col][row] = nullptr;
		}
	}
	return;
}


// Accessors:

Tunnelman* StudentWorld::getTunnelman() const
{
	if (digger == nullptr)
		return nullptr;
	return digger;
}
int StudentWorld::getTicks() const { return m_tickCount; }
int StudentWorld::getWaitingTick() const { return m_ticksToWaitBetweenMoves; }
bool StudentWorld::isEarthPresent(int col, int row) {
	if (col >= 0 && col < 64 && row >= 0 && row < 60) {
		if (earthPtrs[col][row] != nullptr)
			return true;
	}
	return false;
}
bool StudentWorld::isThereEarthFBF(int x, int xFinal, int y, int yFinal)
{
	// for 4 x 4 square objects
	if (x < 0 || x > 63 || xFinal > 63 || xFinal < 0 || y < 0 || y > 59 || yFinal > 59 || yFinal < 0)
		return false;
	for (; x <= xFinal; x++)
		for (; y <= yFinal; y++)
			if (earthPtrs[x][y] != nullptr)
				return true;
	return false;
}
bool StudentWorld::isBoulderPresent(int x, int y)
{
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->isAnObstacle())
			if ((*it)->getX() == x && (*it)->getY() == y)
				return true;
		// proceed to next item
		it++;
	}
	return false;
}
int StudentWorld::getBarrels() const { return m_barrelsRemaining; }

