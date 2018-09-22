// StudentWorld.h
#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include <vector>
#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
const int UNDISCOVERED = 0;
const int BLOCKED = -1;
class GraphObject;
class Actor;
class Earth;
class Tunnelman;
enum Direction;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
/*
We can use these functions from Gameworld:
unsigned int getLives() const
void decLives
void incLives
unsigned int getScore const
unsigned int getLevel const
void increaseScore(unsigned int howMuch)
void setGameStatText(string text)
bool getKey(int& value)
void playSound(int soundID)
*/
class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	virtual ~StudentWorld();
	virtual void cleanUp();
	virtual int init();
	std::string getInfo() const;
	virtual int move();
	void illuminate(int x, int y);
	bool canPlaceHere(int x, int y);
	// Dealing with earth and boulders:
	bool isEarthPresent(int col, int row);
	bool isThereEarthFourByFour(int x, int xFinal, int y, int yFinal) const;
	bool isThereOneByFourEarth(int x, int y) const;
	bool isBoulderPresent(int col, int row) const;
	bool amIDiggingIntoBoulder(int x, int y) const;
	bool isThereFourByOneEarth(int x, int y) const;
	void removeEarth(int i, int j);
	Tunnelman* findNearbyTM(int radius, Actor* a) const;
	// Resetting ticks, adding actors:
	void addActor(Actor* a);
	void barrelWasPickedUp();
	void resetTickCount();
	void resetBoulderTicks();
	void resetNuggetTicks();
	void resetSonarTicks();
	void resetWaterPoolTicks();
	void incrementNuggetTicks();
	void incrementBoulderTicks();
	void incrementSonarTicks();
	void incrementWaterPoolTicks();

	// Accessors:
	Tunnelman* getTunnelman() const;
	int getBarrels() const;
	int getTicks() const;
	int getWaitingTick() const; // for protesters
	int getBoulderTicks() const;
	int getNuggetTicks() const;
	int getSonarTicks() const;
	int getWaterPoolTicks() const;
	//
	bool canMoveTo(int x, int y, GraphObject::Direction dir);
	bool isFacingTunnelman(Actor* a) const;
	GraphObject::Direction getLineOfSightToTunnelman(Actor* protester) const;
	GraphObject::Direction determineMoveToExit(int a, int b);
	bool inValidZone(int x, int y, int startX, int endX, int startY, int endY) const;
	GraphObject::Direction determineMoveToTunnelman(int a, int b, int M);
	Actor* getNearbyProtester(Actor* a, int radius);
	bool isBoulderPresent2(int x, int y) const;
	void findPath(int xFinal, int yFinal, GraphObject::Direction map[64][64], int dist);


private:
	std::vector<Actor*> actors; // keep track of all the objects
	Tunnelman* digger; // separate pointer to tunnel man
	Earth* earthPtrs[VIEW_HEIGHT][VIEW_WIDTH];// store pointers to all earth objects
	int m_tickCount;
	int m_ticksToWaitBetweenMoves;
	int m_barrelsRemaining;
	int m_boulderTicks;
	int m_nuggetTicks;
	int m_sonarTicks;
	int m_waterpoolTicks;
	int m_numOfProtesters;
	int generateRandomNum(int min, int max) const; // random number generator
	double m_probOfGoodie;
	int m_probOfHardcore;
	// Private member functions:
	double euclideanDist(int x1, int y1, int x2, int y2) const; // distance formula calculator
	void removeDeadActors();
	void setAllActorsToDead();
	void replenishTheEarth();
	void destroyTheEarth();
private:
	struct Coordinate {
		Coordinate(int x, int y, int dist) {
			m_x = x;
			m_y = y;
			m_dist = dist;
		}
		int x() const {
			return m_x;
		}
		int y() const {
			return m_y;
		}
		int dist() const {
			return m_dist;
		}// data members:
		int m_x, m_y, m_dist;
	};
	Coordinate* map[64][64];

};

#endif // STUDENTWORLD_H_
