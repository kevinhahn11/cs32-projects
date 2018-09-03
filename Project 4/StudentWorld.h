// StudentWorld.h
#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include <vector>
#include "GameWorld.h"
#include "GameConstants.h"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
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
	bool isEarthPresent(int col, int row);
	bool isThereEarthFBF(int x, int xFinal, int y, int yFinal);
	void removeEarthFBF(int x, int xFinal, int y, int yFinal);
	bool isBoulderPresent(int col, int row);
	void removeEarth(int i, int j);
	void addActor(Actor* a);
	void barrelWasPickedUp();
	void resetTickCount();

	// Accessors:
	Tunnelman* getTunnelman() const;
	int getBarrels() const;
	int getTicks() const;
	int getWaitingTick() const;
private:
	std::vector<Actor*> actors; // keep track of all the objects
	Tunnelman* digger; // separate pointer to tunnel man
	Earth* earthPtrs[VIEW_HEIGHT][VIEW_WIDTH];// store pointers to all earth objects
	int m_tickCount;
	int m_ticksToWaitBetweenMoves;
	int m_barrelsRemaining;
	int generateRandomNum(int min, int max); // random number generator
	double euclideanDist(int x1, int y1, int x2, int y2); // distance formula calculator
	void removeDeadActors();
	void setAllActorsToDead();
};

#endif // STUDENTWORLD_H_