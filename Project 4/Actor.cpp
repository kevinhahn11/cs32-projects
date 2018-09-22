// Actor.cpp
/////////////////////////////////
#include "Actor.h"
#include "StudentWorld.h"
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std;
// Actor.cpp
/*
GraphObject(imageID, startX, startY, startDirection, size, depth)
void setVisible(bool value)
int getX() const
int getY() const
void moveTo(int x, int y)
Direction getDirection() const // up down left right
void setDirection(Direction d) // up down left right
*/
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
/////////////////////////////////////////////////////////////////////////
// Actor implementations (Base superclass)
Actor::Actor(StudentWorld* w, int imageID, int startX, int startY,
	Direction startDirection, double size = 1.0, unsigned int depth = 0)
	: GraphObject(imageID, startX, startY, startDirection, size, depth), myWorld(w), m_alive(true)
{
	setVisible(true);
}
Actor::~Actor()
{
	//if (getWorld()->getLives() <= 0 && myWorld != nullptr)
	/*
	if (getWorld()->getLives() <= 0 && myWorld != nullptr)
	{
	delete myWorld;
	myWorld = nullptr;
	}
	*/
}
void Actor::setToDead() {
	m_alive = false;
	setVisible(false);
} // sets tunnelman to dead
bool Actor::isProtester() const { return false; }
bool Actor::isDistributedObject() const { return false; }
StudentWorld* Actor::getWorld() const { return myWorld; }

bool Actor::isObstacle() const { return false; }
bool Actor::isPickupable() const { return false; }
void Actor::doSomething() {}
void Actor::annoy(int i) {}
double Actor::getRadius(int x1, int y1, int x2, int y2) const { return sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2))); }
void Actor::bribe() {}
bool Actor::isAlive() const { return m_alive; }
/*
StudentWorld*& Actor::getWorldReference() { return myWorld; }
*/
/////////////////////////////////////////////////////
// Earth implementations
Earth::Earth(StudentWorld* w, int startingX, int startingY)
	: Actor(w, TID_EARTH, startingX, startingY, right, 0.25, 3)
{
	setVisible(true);
}
Earth::~Earth() { setVisible(false); }

void Earth::doSomething() {}
/////////////////////////////////////////////////////////////
Human::Human(StudentWorld* w, int imageID, int startX, int startY,
	Direction startDirection, double size, unsigned int depth)
	: Actor(w, imageID, startX, startY, startDirection, size, depth), m_hitPoints(10)
{
	// humans are always visible, actor's constructor takes care of it for us
}
Human::~Human() {}
void Human::doSomething() {}
void Human::annoy(int i) {}
void Human::increaseHitPoints(int i) { m_hitPoints += i; }
void Human::decreaseHitPoints(int i) { m_hitPoints -= i; }
int Human::getHP() const { return m_hitPoints; }
void Human::setHitPoints(int i) { m_hitPoints = i; }
///////////////////////////////////////////////////
// Tunnelman implementations
Tunnelman::Tunnelman(StudentWorld* w)
	: Human(w, TID_PLAYER, 30, 60, right, 1.0, 0), m_squirts(5), m_nuggets(0), m_sonar(1)
{}
Tunnelman::~Tunnelman() {
	// delete dynamically allocated variables held by the Tunnelman
}
int Tunnelman::getSquirts() const { return m_squirts; }
void Tunnelman::increaseSquirts(int i) { m_squirts += i; }
void Tunnelman::decreaseSquirts(int i) { m_squirts -= i; }
void Tunnelman::increaseSonarCount(int i) { m_sonar++; }
void Tunnelman::decreaseSonarCount() { m_sonar--; }
void Tunnelman::dropNugget() { m_nuggets--; }
void Tunnelman::nuggetReceived() { m_nuggets++; }
int Tunnelman::getNuggetCount() const { return m_nuggets; }
int Tunnelman::getSonarCharges() const { return m_sonar; }
void Tunnelman::annoy(int i)
{
	decreaseHitPoints(i);
	if (getHP() <= 0)
	{
		setToDead();
		getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
	}
	return;
}
void Tunnelman::doSomething()
{
	if (isAlive() == false)
		return;
	int c;
	if (this->getWorld()->getKey(c) == true)
	{
		// user hit a key during this tick!
		switch (c)
		{
		case KEY_PRESS_RIGHT:
			if (getDirection() != right)
				setDirection(right);
			else
			{
				if (getX() + 1 > 60)
				{
					moveTo(60, getY());
					dig();
				}
				else
				{
					if (getWorld()->amIDiggingIntoBoulder(getX() + 1, getY()) == true)
					{
						dig();
						break;
					}
					else
					{
						moveTo(getX() + 1, getY());
						dig();
						//getWorld()->playSound(SOUND_DIG);
					}
				}

				// Now check to see if we need to remove earth.
				//int x = getX(); int y = getY();
			}
			break;
		case KEY_PRESS_LEFT:
			if (this->getDirection() != left)
				this->setDirection(left);
			else
			{
				if (getX() - 1 < 0)
				{
					moveTo(0, getY());
					dig();
				}
				else
				{
					if (getWorld()->amIDiggingIntoBoulder(getX() - 1, getY()) == true)
					{
						//dig();
						break;
					}
					else
					{
						moveTo(getX() - 1, getY());
						dig();
						//getWorld()->playSound(SOUND_DIG);
					}
				}
			}
			break;
		case KEY_PRESS_DOWN:
			if (getDirection() != down)
				setDirection(down);
			else
			{
				if (getY() - 1 < 0)
				{
					moveTo(getX(), 0);
					dig();
				}
				else
				{
					if (getWorld()->amIDiggingIntoBoulder(getX(), getY() - 1) == true)
					{
						//dig();
						break;
					}
					else
					{
						moveTo(getX(), getY() - 1);
						dig();
						//getWorld()->playSound(SOUND_DIG);
					}
				}
			}
			break;
		case KEY_PRESS_UP:
			if (getDirection() != up)
				setDirection(up);
			else
			{
				if (getY() + 1 > 60)
				{
					moveTo(getX(), 60);
					dig();
				}
				else
				{
					if (getWorld()->amIDiggingIntoBoulder(getX(), getY() + 1) == true)
					{
						//dig();
						break;
					}
					else
					{
						moveTo(getX(), getY() + 1);
						dig();
						//getWorld()->playSound(SOUND_DIG);
					}
				}
			}
			break;

		case KEY_PRESS_SPACE:
			if (m_squirts <= 0)
				break;
			switch (getDirection()) {
			case right:
				if (getWorld()->amIDiggingIntoBoulder(getX() + 4, getY()) == true)
				{
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					m_squirts--;
					return;
				}
				if (getWorld()->isThereEarthFourByFour(getX() + 4, getX() + 7, getY(), getY() + 3) == false)
					getWorld()->addActor(new Squirt(getWorld(), getX() + 4, getY(), this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			case left:
				if (getWorld()->amIDiggingIntoBoulder(getX() - 4, getY()) == true)
				{
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					m_squirts--;
					return;
				}
				if (getWorld()->isThereEarthFourByFour(getX() - 4, getX(), getY(), getY() + 3) == false)
					getWorld()->addActor(new Squirt(getWorld(), getX() - 4, getY(), this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			case up:
				if (getWorld()->amIDiggingIntoBoulder(getX(), getY() + 4) == true)
				{
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					m_squirts--;
					return;
				}
				if (getWorld()->isThereEarthFourByFour(getX(), getX() + 3, getY(), getY() + 7) == false)
					getWorld()->addActor(new Squirt(getWorld(), getX(), getY() + 4, this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			case down:
				if (getWorld()->amIDiggingIntoBoulder(getX(), getY() - 4) == true)
				{
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					m_squirts--;
					return;
				}
				if (getWorld()->isThereEarthFourByFour(getX(), getX() + 3, getY() - 4, getY()) == false)
					getWorld()->addActor(new Squirt(getWorld(), getX(), getY() - 4, this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			default:
				break;
			}
			break;
		case KEY_PRESS_ESCAPE:
			this->setToDead();
			getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
			getWorld()->decLives();
			break;
		case KEY_PRESS_TAB:
			if (m_nuggets <= 0)
				break;
			getWorld()->addActor(new GoldNugget(getWorld(), getX(), getY(), true, false, false));
			m_nuggets--;
			break;
		case 'Z':
		case 'z':
			if (m_sonar <= 0)
				break;
			m_sonar--;
			getWorld()->playSound(SOUND_SONAR);
			getWorld()->illuminate(getX(), getY());
			break;
		default:
			break;
		}
	}

	return;
}
void Tunnelman::dig()
{
	if (getWorld()->isThereEarthFourByFour(getX(), getX() + 3, getY(), getY() + 3))
		getWorld()->playSound(SOUND_DIG);
	for (int col = 0; col <= 3; col++)
		for (int row = 0; row <= 3; row++)
			getWorld()->removeEarth((getX() + col), (getY() + row));
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Protester
Protester::Protester(StudentWorld* w, int imageID)
	:Human(w, imageID, 60, 60, left, 1.0, 0), m_numSquaresToMove(-1), m_restTicks(0), m_shoutTicks(0), m_perpTurnTicks(0),
	m_leaving(false), m_resting(false), m_stunned(false)
{
	setHitPoints(5);
	setVisible(true);
}
Protester::~Protester() {}
bool Protester::isProtester() const { return true; }
bool Protester::isHardcore() const { return false; }
void Protester::doSomething()
{
	//m_shoutTicks++;
	if (isAlive() == false)
		return;
	//setDirection(randomDirection());
}
/*
if (m_restTicks > max(0, 3 - (int)(getWorld()->getLevel() / 4)))
{
m_resting = false;
setRestTick(0);
}
if (m_resting == true)
{
m_restTicks++;
return;
}
else if (getRadius(getX(), getY(), getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) <= 4 &&
getWorld()->isFacingTunnelman(this) && m_shoutTicks > 15)
{
getWorld()->getTunnelman()->annoy(2);
}
if (getX() == 60 && getY() == 60)
{
if (m_leaving = true)
{
setToDead();
return;
}
else
{
moveTo(getX() - 1, getY());
setRestTick(0);
return;
}
}
if (m_resting = false && getX() == 30 && getY() == 5)
{
m_leaving = true;
setDirection(up);
moveTo(getX(), getY() + 1);
setRestTick(0);
}
if (getX() == 30 && getY() == 60)
{
if (m_leaving == true)
{
setDirection(right);
moveTo(getX() + 1, getY());
setRestTick(0);
}
else
{
setDirection(down);
moveTo(getX(), getY() - 1);
setRestTick(0);
}
}
else
{
switch (getDirection())
{
case up:
moveTo(getX(), getY() + 1);
setRestTick(0);
return;
break;
case down:
moveTo(getX(), getY() - 1);
setRestTick(0);
return;
break;
case left:
moveTo(getX() - 1, getY());
return;
break;
case right:
moveTo(getX() + 1, getY());
return;
break;
default:
return;
break;
}
}
m_shoutTicks++;
/*
if (m_leaving == false)
{
if (getRadius(getX(), getY(), getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) <= 4 &&
getWorld()->isFacingTunnelman(this) && m_shoutTicks > 15)
{
getWorld()->playSound(SOUND_PROTESTER_YELL);
getWorld()->getTunnelman()->annoy(2);
setShoutTick(0);
}
}
*/
//}
/*
void Protester::doSomething() {
if (isAlive() == false)
return;
else if (m_resting == true)
{
m_restTicks++; // increment resting tick count if the protester is resting.
return;
}
else if (m_leaving == true) // if protester is in a leave the oil state
{
return;
}
else if (getRadius(getX(), getY(), getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) <= 4 &&
getWorld()->isFacingTunnelman(this))
{
if (m_shoutTicks > 15)
{
getWorld()->playSound(SOUND_PROTESTER_YELL);
getWorld()->getTunnelman()->annoy(2);
setShoutTick(0); // prevent protester from shouting again for at least 15 non-resting ticks
}
}
else if (getWorld()->getLineOfSightToTunnelman(this) != none
&& getRadius(getX(), getY(), getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) > 4)
{
setDirection(getWorld()->getLineOfSightToTunnelman(this));
}
else
return;

}
*/
void Protester::bribe()
{
	getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
	getWorld()->increaseScore(25);
	setToLeaving();
}
void Protester::stun() { m_stunned = true; m_resting = true; }
void Protester::unstun() { m_stunned = false; }
void Protester::annoy(int i) {
	this->decreaseHitPoints(i);
	if (isLeavingField() == true)
		return; // protester cannot be further annoyed.

	if (getHP() <= 0)
	{
		setToLeaving();
		getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
		setToDead();
		return;
		setRestTick(0);
		if (i == 100)
			getWorld()->increaseScore(500);
		if (i == 2)
		{
			if (isHardcore() == true)
				getWorld()->increaseScore(250);
			else
				getWorld()->increaseScore(100);
		}

	}
	else
	{
		m_stunned = true;
		getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
		m_restTicks = max(50, 100 - ((int)getWorld()->getLevel()) * 10);
		m_stunned = true;
	}
}

void Protester::computeNumStepsToMove()
{
	m_numSquaresToMove = rand() % 61 + 8;
}
int Protester::getNumStepsToMove() const
{
	return m_numSquaresToMove;
}
void Protester::moveThisManySquares(int n)
{

}
GraphObject::Direction Protester::randomDirection()
{
	int direction = rand() % 4;
	switch (direction)
	{
	case 0:
		return left;
		break;
	case 1:
		return right;
		break;
	case 2:
		return up;
		break;
	case 3:
		return down;
		break;
	default:
		return left;
	}
}
GraphObject::Direction Protester::canTurnPerpendicular()
{
	return GraphObject::none;
}
int Protester::getRestTick() {
	return m_restTicks;
}

int Protester::getShoutTick() {
	return m_shoutTicks;
}

int Protester::getTurnTick() {
	return m_perpTurnTicks;
}

void Protester::setRestTick(int num) {
	m_restTicks = num;
}

void Protester::setShoutTick(int num) {
	m_shoutTicks = num;
}

void Protester::setTurnTick(int num) {
	m_perpTurnTicks = num;
}

bool Protester::isLeavingField() const {
	return m_leaving;
}

void Protester::setToLeaving() {
	m_leaving = true;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Regular Protester
RegularProtester::RegularProtester(StudentWorld* w, int imageID)
	:Protester(w, TID_PROTESTER)
{}
/////////////////////////////////////////////////////////////////////////////////////////
// Hardcore Protester
HardcoreProtester::HardcoreProtester(StudentWorld* w, int imageID)
	: Protester(w, TID_HARD_CORE_PROTESTER)
{
	setHitPoints(20); //
}
void HardcoreProtester::annoy(int i)
{
	Protester::annoy(i);
}
void HardcoreProtester::bribe()
{
	getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
	getWorld()->increaseScore(50);
}
/////////////////////////////////////////////////////////////////////////////////////////
// Object implementations: base class for anything that is not a Protester or Tunnelman.

Object::Object(StudentWorld* w, int imageID, int startX, int startY,
	Direction startDirection, double size, unsigned int depth)
	: Actor(w, imageID, startX, startY, startDirection, size, depth) {
}
void Object::doSomething() {}
Object::~Object() {}
bool Object::isDistributedObject() const { return true; }
bool Object::isPickupable() const { return true; }
void Object::setToDead() {
	setVisible(false);
	Actor::setToDead();
}
bool Object::isObstacle() const { return false; }
///////////////////////////////////////////////////////////////////////////////////////
// Boulder implementations
Boulder::Boulder(StudentWorld* w, int x, int y)
	: Object(w, TID_BOULDER, x, y, down, 1.0, 1), b_stable(true), b_waiting(false), b_falling(false), b_ticks(0)
{
	//setVisible(true); // already done for us by the actor class
	for (int col = 0; col <= 3; col++)
		for (int row = 0; row <= 3; row++)
			getWorld()->removeEarth((x + col), (y + row));
}
Boulder::~Boulder() {}
bool Boulder::isPickupable() const { return false; }
bool Boulder::isObstacle() const { return true; }
void Boulder::setToDead()
{
	getWorld()->resetBoulderTicks();
	setVisible(false);
	Actor::setToDead();
}
void Boulder::doSomething()
{
	if (isAlive() == false)
		return;
	if (b_stable == true)
	{
		for (int row = 0; row <= 3; row++)
			if (getWorld()->isEarthPresent(getX() + row, getY() - 1) == true)
				return;
		b_waiting = true;
		b_stable = false;
		getWorld()->resetBoulderTicks();
	}
	else if (getWorld()->getBoulderTicks() > 30 && b_waiting == true)
	{
		b_waiting = false;
		b_falling = true;
		getWorld()->playSound(SOUND_FALLING_ROCK);
	}
	else if (b_falling == true)
	{
		if (getY() <= 0)
		{
			setToDead();
			return;
		}
		else if (getWorld()->isThereFourByOneEarth(getX(), getY() - 1))
		{
			setToDead();
			return;
		}
		else if (getRadius(getX(), getY() - 1, getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) <= 3)
		{
			getWorld()->getTunnelman()->setToDead(); // kill the player
			getWorld()->playSound(SOUND_PLAYER_GIVE_UP); // play the player died sound
			setToDead(); // set this boulder to dead
			return;
		}
		else if (getWorld()->getNearbyProtester(this, 3) != nullptr)
		{
			getWorld()->getNearbyProtester(this, 3)->annoy(100);
		}

		moveTo(getX(), getY() - 1);
		return;
	}
	else
		return;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Squirt implementation
Squirt::Squirt(StudentWorld* w, int x, int y, Tunnelman* t)
	: Object(w, TID_WATER_SPURT, x, y, t->getDirection(), 1.0, 1),
	distance(0), m_killProtester(false), m_boulder(false)
{
	/*
	if (getWorld()->isThereEarthFourByFour(x, x + 3, y, y + 3))
	{
	setVisible(false);
	setToDead();
	}
	*/
}
// setToDead() is inherited from actor, and just sets the squirt's visibility to false
bool Squirt::isDistributedObject() const { return false; }
bool Squirt::isPickupable() const { return false; }
void Squirt::setToDead()
{
	//setVisible(false);
	Actor::setToDead();
}
Squirt::~Squirt() {}

void Squirt::doSomething()
{
	if (isAlive() == false)
		return;
	// TO-DO: if (squirt is within a radius of 3.0 of one or more protesters):
	// ...

	distance++;
	if (distance >= 4 || m_killProtester == true || m_boulder == true)
	{
		this->setToDead();
		m_killProtester = false;
		m_boulder = false;
		return;
	}
	switch (getDirection())
	{
	case right:
		if (getX() + 1 > 63)
		{
			setToDead();
			return;
		}
		else
		{

			if (getWorld()->isThereOneByFourEarth(getX() + 4, getY()))
			{
				setVisible(false);
				setToDead();
				return;
			}

			if (getWorld()->isThereOneByFourEarth(getX() + 1, getY())
				|| getWorld()->isBoulderPresent2(getX() + 1, getY()))
			{
				m_boulder = true;
				//setToDead();
				return;
			}

			//distance--;
			moveTo((getX() + 1), getY());
		}

		break;

	case left:
		if (getX() - 1 >= 0)
		{
			// if target location is occupied by a earth or boulder
			// ... set squirt to dead so it can be remoed from the oil field at the end of the tick
			// otherwise
			if (getWorld()->isEarthPresent(getX(), getY()))
			{
				setToDead();
				return;
			}
			if (getWorld()->isThereOneByFourEarth(getX() - 1, getY())
				|| getWorld()->isBoulderPresent2(getX() - 1, getY()))
			{
				m_boulder = true;
				//setToDead();
				return;
			}
			//distance--;
			moveTo((getX() - 1), getY());
		}
		break;
	case up:
		if (getY() + 1 <= 63)
		{
			// if target location is occupied by a earth or boulder
			// ...
			if (getWorld()->isThereFourByOneEarth(getX(), getY() + 4)
				|| getWorld()->isBoulderPresent(getX(), getY() + 4))
			{
				setToDead();
				return;
			}
			//distance--;
			moveTo((getX()), getY() + 1);
		}
		else
		{
			setToDead();
			return;
		}
		break;
	case down:
		if (getY() - 1 >= 0)
		{
			// if target location is occupied by a earth or boulder
			// ...
			// otherwise

			if (getWorld()->isThereFourByOneEarth(getX(), getY() - 1)
				|| getWorld()->isBoulderPresent2(getX(), getY() - 1))
			{
				m_boulder = true;
				//setToDead();
				return;
			}

			//distance--;
			moveTo((getX()), getY() - 1);
		}
		else
		{
			setToDead();
			return;
		}
		break;
	}
	Actor* p = getWorld()->getNearbyProtester(this, 3);
	if (p != nullptr)
	{
		setVisible(true);
		p->annoy(2);
		m_killProtester = true;
	}
	return;
}

// Squirts can't be annoyed, so leave the virtual void annoyed() as is.

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Barrel implementation
Barrel::Barrel(StudentWorld* w, int x, int y)
	: Object(w, TID_BARREL, x, y, right, 1.0, 2)
{
	setVisible(false);
	visible = false;
}
Barrel::~Barrel() {}
void Barrel::doSomething()
{
	if (isAlive() == false)
		return;
	double radius = getRadius(getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY(),
		getX(), getY());
	if (visible == false && radius <= 4)
	{
		setVisible(true);
		visible = true;
		return;
	}
	else if (radius <= 3)
	{
		setVisible(false);
		setToDead();
		getWorld()->playSound(SOUND_FOUND_OIL);
		getWorld()->increaseScore(1000);
		getWorld()->barrelWasPickedUp();
		// increase the score by 1000 points
		// notify the student world that barrel has been picked up (function?)
	}
}
// No need to edit the annoyed() function
//////////////////////////////////////////////////////////////////////
// GoldNugget implementation
GoldNugget::GoldNugget(StudentWorld* w, int x, int y, bool visibilityState, bool curState, bool pickUpable)
	: Object(w, TID_GOLD, x, y, right, 1.0, 2), visibility(visibilityState), g_permanentState(curState),
	g_temporaryState(!curState), g_tunnelmanCanPickItUp(pickUpable), g_100Ticks(visibilityState)
{
	setVisible(visibility);
	// permanent = they remain in the field until picked up by tunnelman
	// temporary = they remain for a certain number of ticks before vanishing or being picked up by a protestor
	// we have to specify the state here.
}
void GoldNugget::doSomething()
{
	if (isAlive() == false)
		return;
	double r = getRadius(getX(), getY(),
		getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY());
	Actor* a = getWorld()->getNearbyProtester(this, 4);
	if (g_tunnelmanCanPickItUp == false && a != nullptr)
	{
		// lifetime of 100 game ticks.
		setToDead();
		a->bribe();
		// tell protestor that it picked up the nugget (be bribed)

	}
	else if (visibility == false && g_tunnelmanCanPickItUp == true)
	{
		if (r <= 4)
		{
			setVisible(true);
			visibility = true;
		}
		return;
	}
	else if (r <= 3 && g_tunnelmanCanPickItUp && visibility == true)
	{
		setVisible(false);
		setToDead();
		getWorld()->getTunnelman()->nuggetReceived();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->increaseScore(10);
		// TO DO: tell tunnelman object that it just received a new nugget so it can update its inventory
		return;
	}
	else if (g_100Ticks == true)
	{
		if (getWorld()->getNuggetTicks() >= 100)
		{
			setVisible(false);
			setToDead();
		}
		getWorld()->incrementNuggetTicks();
		return;
		// if tick lifetime has elapsed, then 
		// setToDead(); // no removed by the studentworld class from the game at the end of the current tick
	}
}
void GoldNugget::setToDead() {
	setVisible(false);
	Actor::setToDead();
	getWorld()->resetNuggetTicks();
}
GoldNugget::~GoldNugget() {}
bool GoldNugget::pickupableByTunnelman() const { return g_tunnelmanCanPickItUp; }

/////////////////////////////////////////////////////////////
// WaterPool implementation
WaterPool::WaterPool(StudentWorld* w, int x, int y)
	: Object(w, TID_WATER_POOL, x, y, right, 1.0, 2)
{
	//setVisible(true); // already by default
	// only pickup-able by Tunnelman
}
WaterPool::~WaterPool() {}
void WaterPool::doSomething()
{
	if (isAlive() == false)
		return;
	if (getRadius(getX(), getY(),
		getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) <= 3)
	{
		setToDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		// tell tunnelman that it just received 5 squirts of water so it updates its inventory
		getWorld()->getTunnelman()->increaseSquirts(5);
		getWorld()->increaseScore(100);
		return;
	}
	if (getWorld()->getWaterPoolTicks() >= max(100, 300 - (10 * ((int)getWorld()->getLevel()))))
	{
		setToDead(); // removed by StudentWorld class
		getWorld()->resetWaterPoolTicks();
		return;
	}
}

///////////////////////////////////////////////////////////////
// SonarKit implementation
SonarKit::SonarKit(StudentWorld* w, int x, int y)
	: Object(w, TID_SONAR, x, y, right, 1.0, 2)
{
	// setVisible(true); // Actor constructor already sets it to true
	tempState = true; // always temporary
					  // int numOfTicks = max(100, 300 - 10 * ((int)getWorld()->getLevel()));
}
SonarKit::~SonarKit() {}
void SonarKit::doSomething()
{
	if (isAlive() == false)
		return;
	if (getRadius(getX(), getY(), getWorld()->getTunnelman()->getX(), getWorld()->getTunnelman()->getY()) <= 3)
	{
		setToDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		// notify the tunnelman
		getWorld()->increaseScore(75);
		getWorld()->getTunnelman()->increaseSonarCount(1);
		getWorld()->resetSonarTicks();
	}
	if (getWorld()->getSonarTicks() >= max(100, 300 - 10 * ((int)getWorld()->getLevel())))
	{
		setToDead();
		getWorld()->resetSonarTicks();
	}
}
