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
	virtual bool isPresent(int x, int y) const;
	virtual void doSomething();
	virtual void annoy();
	virtual bool isAlive() const;
	virtual bool isDistributedObject() const;
	virtual void setToDead();
	virtual bool isAnObstacle() const;
	virtual bool isPickupable() const;
	double getRadius(int x1, int y1, int x2, int y2);
	StudentWorld* getWorld() const;
	//StudentWorld*& getWorldReference();

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
	virtual bool isAnObstacle() const;
	virtual bool isPickupable() const;
	virtual bool isAlive() const;
	virtual void setToDead();
};
class Human : public Actor
{
public:
	Human(StudentWorld* w, int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth);
	virtual ~Human();
	virtual bool isPresent(int x, int y) const;
	virtual void doSomething();
	virtual void annoy();
	virtual void increaseHitPoints(int i);
	virtual void decreaseHitPoints(int i);
	virtual int getHP() const;
private:
	int m_hitPoints;

};

// Tunnelman declaration
class Tunnelman : public Human
{
public:
	Tunnelman(StudentWorld* w);
	virtual ~Tunnelman();
	virtual void annoy();
	virtual void doSomething();
	void nuggetReceived(); // increase by 1
	void dropNugget(); // decrease by 1
	int getSquirts() const;
	void increaseSquirts(int i);
	void decreaseSquirts(int i);
	void increaseSonarCount();
	void decreaseSonarCount();
	int getNuggetCount() const;
	int getSonarCharges() const;
	void dig();
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
	virtual bool isAnObstacle() const;
	virtual void doSomething();
	virtual bool isDistributedObject() const;
	virtual bool isPresent(int x, int y) const;
	virtual bool isPickupable() const;
	virtual void setToDead();
private:
	bool b_stable;
	bool b_waiting;
	bool b_falling;
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
	virtual bool isAnObstacle() const;
	// Squirts can't be annoyed
private:
	int distance;
};
// Barrel of Oil:
class Barrel : public Object
{
public:
	Barrel(StudentWorld* w, int x, int y);
	virtual ~Barrel();
	virtual void doSomething();
	virtual bool isDistributedObject() const;
	virtual bool isPickupable() const;
	virtual bool isAnObstacle() const;
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
	virtual bool isDistributedObject() const;
	virtual bool isPickupable() const;
	virtual bool isAnObstacle() const;
	// Waterpool can't be annoyed
};
// Gold Nugget:
class GoldNugget : public Object
{
public:
	GoldNugget(StudentWorld* w, int x, int y, bool visibilityState, bool curState, bool pickUpable);
	virtual bool isPickupable() const;
	virtual void doSomething();
	virtual bool isDistributedObject() const;
	virtual bool pickupableByTunnelman() const;
	virtual bool isAnObstacle() const;
	virtual void setToDead();
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
	//~SonarKit();
	virtual bool isPickupable() const;
	virtual bool isDistributedObject() const;
	virtual void doSomething();
	virtual bool isAnObstacle() const;
private:
	bool tempState;
};

#endif 

/*
increment the tick count when doSomething() is executed, (something like a private member variable)
same situation when move() is called.
*/