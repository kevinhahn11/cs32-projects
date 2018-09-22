//Actor.h
#ifndef ACTOR_H_
#define ACTOR_H_
#include <vector>
#include <algorithm>
#include <cmath>
#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* w, int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth);
	virtual ~Actor();
	virtual void doSomething();
	virtual void annoy(int i);
	virtual bool isAlive() const;
	virtual bool isDistributedObject() const;
	virtual void setToDead();
	virtual bool isObstacle() const; // is a collision object
	virtual bool isPickupable() const;
	virtual bool isProtester() const;
	virtual void bribe();
	double getRadius(int x1, int y1, int x2, int y2) const;
	StudentWorld* getWorld() const;
private:
	bool m_alive;
	StudentWorld* myWorld;

};
// Earth declaration:
class Earth : public Actor
{
public:
	Earth(StudentWorld* w, int startingX, int startingY);
	virtual ~Earth();
	virtual void doSomething();
private:
};
class Object : public Actor
{
public:
	Object(StudentWorld* w, int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth);
	virtual void doSomething();
	virtual ~Object();
	virtual bool isDistributedObject() const;
	virtual bool isObstacle() const;
	virtual bool isPickupable() const;
	virtual void setToDead();
	//StudentWorld* getWorld() const;
private:
	//StudentWorld * myWorld;
};
class Human : public Actor
{
public:
	Human(StudentWorld* w, int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth);
	virtual ~Human();
	virtual void doSomething();
	virtual void annoy(int i);
	// Health:
	void increaseHitPoints(int i);
	void decreaseHitPoints(int i);
	int getHP() const;
	void setHitPoints(int i);
private:
	int m_hitPoints;
};

// Tunnelman declaration
class Tunnelman : public Human
{
public:
	Tunnelman(StudentWorld* w);
	virtual ~Tunnelman();
	virtual void annoy(int i);
	virtual void doSomething();
	void dig(); // dig
	void nuggetReceived(); // increase nugget count by 1
	void dropNugget(); // decrease nugget count by 1
	int getSquirts() const; // get squirts remaining
	void increaseSquirts(int i); // increase squirt count by 1
	void decreaseSquirts(int i); // decrease squirt count by 1
	void increaseSonarCount(int i); // increase sonar count by 1
	void decreaseSonarCount(); //decrease sonar count by 1
	int getNuggetCount() const;
	int getSonarCharges() const;
private:
	// squirt gun, sonar, gold nuggets, hit-points
	int m_squirts;
	int m_nuggets;
	int m_sonar;
};

// Boulder:
class Boulder : public Object
{
public:
	Boulder(StudentWorld* w, int x, int y);
	virtual ~Boulder();
	virtual bool isObstacle() const;
	virtual void doSomething();
	virtual bool isPickupable() const;
	virtual void setToDead();
private:
	bool b_stable;
	bool b_waiting;
	bool b_falling;
	bool b_ticks;
};
// Squirt declaration
class Squirt : public Object
{
public:
	Squirt(StudentWorld* w, int x, int y, Tunnelman* t);
	virtual ~Squirt();
	virtual void doSomething();
	virtual bool isPickupable() const;
	virtual bool isDistributedObject() const;
	virtual void setToDead();
	// Squirts can't be annoyed
private:
	int distance;
	bool m_killProtester;
	bool m_boulder;
};
// Barrel of Oil:
class Barrel : public Object
{
public:
	Barrel(StudentWorld* w, int x, int y);
	virtual ~Barrel();
	virtual void doSomething();
	// Barrels can't be annoyed, no need to rewrite
private:
	bool visible;
};
// WaterPool:
class WaterPool : public Object
{
public:
	WaterPool(StudentWorld* w, int x, int y);
	virtual void doSomething();
	virtual ~WaterPool();
	// Waterpool can't be annoyed
};
// Gold Nugget:
class GoldNugget : public Object
{
public:
	GoldNugget(StudentWorld* w, int x, int y, bool visibilityState, bool curState, bool pickUpable);
	virtual void doSomething();
	bool pickupableByTunnelman() const;
	virtual void setToDead();
	virtual ~GoldNugget();

private:
	bool g_permanentState; // true means permanent, false means temporary
	bool g_tunnelmanCanPickItUp; // true means tunnelman can pick it up, false means protester can pick it up
	bool visibility;
	bool g_temporaryState;
	bool g_100Ticks;
};
// SonarKit:
class SonarKit : public Object
{
public:
	SonarKit(StudentWorld* w, int x, int y);
	virtual ~SonarKit();
	virtual void doSomething();
private:
	bool tempState;
};
// Protester:
class Protester : public Human
{
public:
	Protester(StudentWorld* w, int imageID);
	virtual ~Protester();
	virtual void doSomething();
	virtual void annoy(int i);
	virtual void computeNumStepsToMove();
	virtual int getNumStepsToMove() const;
	virtual void bribe();
	virtual bool isProtester() const;
	virtual void moveThisManySquares(int n);
	void unstun();
	void stun();

	//
	int getRestTick();
	int getShoutTick();
	int getTurnTick();
	void setRestTick(int num);
	void setShoutTick(int num);
	void setTurnTick(int num);
	virtual bool isHardcore() const;
	bool isLeavingField() const;
	void setToLeaving();
	GraphObject::Direction randomDirection();
	GraphObject::Direction canTurnPerpendicular();
private:
	bool m_leaving;
	bool m_resting;
	int m_numSquaresToMove;
	bool m_stunned;
	int m_restTicks;
	int m_shoutTicks; // the number of ticks since the protester last shouted.
	int m_perpTurnTicks;
};
class RegularProtester : public Protester
{
public:
	RegularProtester(StudentWorld* w, int imageID);
private:
};
class HardcoreProtester : public Protester
{
public:
	HardcoreProtester(StudentWorld* w, int imageID);
	virtual void annoy(int i);
	virtual void bribe();
};
#endif 
