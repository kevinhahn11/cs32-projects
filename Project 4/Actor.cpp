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
	
	if (getWorld()->getLives() <= 0 && myWorld != nullptr)
	{
		delete myWorld;
		myWorld = nullptr;
	}
	
}
bool Actor::isDistributedObject() const { return false; }
void Actor::setToDead() { m_alive = false; }
StudentWorld* Actor::getWorld() const { return myWorld; }
bool Actor::isAnObstacle() const { return false; }
bool Actor::isPickupable() const { return false; }
void Actor::doSomething() {}
void Actor::annoy() {}
double Actor::getRadius(int x1, int y1, int x2, int y2) { return sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2))); }

bool Actor::isAlive() const { return m_alive; }
bool Actor::isPresent(int x, int y) const { return (getX() == x && getY() == y); }
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
bool Human::isPresent(int x, int y) const { return true; }
void Human::doSomething() {}
void Human::annoy() {}
void Human::increaseHitPoints(int i) { m_hitPoints += i; }
void Human::decreaseHitPoints(int i) { m_hitPoints -= i; }
int Human::getHP() const { return m_hitPoints; }
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
void Tunnelman::increaseSonarCount() { m_sonar++; }
void Tunnelman::decreaseSonarCount() { m_sonar--; }
void Tunnelman::dropNugget() { m_nuggets--; }
void Tunnelman::nuggetReceived() { m_nuggets++; }
int Tunnelman::getNuggetCount() const { return m_nuggets; }
int Tunnelman::getSonarCharges() const { return m_sonar; }
void Tunnelman::annoy()
{
	decreaseHitPoints(2);
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
					if (getWorld()->isBoulderPresent(getX() + 4, getY()) == true)
						break;
					else
					{
						moveTo(getX() + 1, getY());
						dig();
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
					if (getWorld()->isBoulderPresent(getX() - 4, getY()) == true)
						break;
					else
					{
						moveTo(getX() - 1, getY());
						dig();
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
					if (getWorld()->isBoulderPresent(getX(), getY() - 4) == true)
						break;
					else
					{
						moveTo(getX(), getY() - 1);
						dig();
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
					if (getWorld()->isBoulderPresent(getX(), getY() + 4) == true)
						break;
					else
					{
						moveTo(getX(), getY() + 1);
						dig();
					}
				}
			}
			break;

		case KEY_PRESS_SPACE:
			if (m_squirts <= 0)
				break;
			switch (getDirection()) {
			case right:
				getWorld()->addActor(new Squirt(getWorld(), getX() + 4, getY(), this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			case left:
				getWorld()->addActor(new Squirt(getWorld(), getX() - 4, getY(), this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			case up:
				getWorld()->addActor(new Squirt(getWorld(), getX(), getY() + 4, this));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				m_squirts--;
				break;
			case down:
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
	for (int col = 0; col <= 3; col++)
		for (int row = 0; row <= 3; row++)
			getWorld()->removeEarth((getX() + col), (getY() + row));
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
bool Object::isAlive() const { return Actor::isAlive(); }
bool Object::isAnObstacle() const { return true; }
///////////////////////////////////////////////////////////////////////////////////////
// Boulder implementations
Boulder::Boulder(StudentWorld* w, int x, int y)
	: Object(w, TID_BOULDER, x, y, down, 1.0, 1), b_stable(true), b_waiting(false), b_falling(false)
{
	//setVisible(true); // already done for us by the actor class
	for (int col = 0; col <= 3; col++)
		for (int row = 0; row <= 3; row++)
			getWorld()->removeEarth((x + col), (y + row));
}
bool Boulder::isDistributedObject() const { return true; }
bool Boulder::isPickupable() const { return false; }
bool Boulder::isPresent(int x, int y) const { return true; }
bool Boulder::isAnObstacle() const { return true; }
void Boulder::setToDead()
{
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
		getWorld()->resetTickCount();
	}
	else if (getWorld()->getTicks() > 30 && b_waiting == true)
	{
		b_waiting = false;
		b_falling = true;
		getWorld()->playSound(SOUND_FALLING_ROCK);
	}
	else if (b_falling == true)
	{
		if (getY() == 0)
		{
			setToDead();
			return;
		}
		else if (getWorld()->isThereEarthFBF(getX(), getX() + 3, getY() - 1, getY() - 1))
		{
			setToDead();
			return;
		}
		else if (getWorld()->isBoulderPresent(getX(), getY() - 1))
		{
			setToDead();
			return;
		}
		else
		{
			moveTo(getX(), getY() - 1);
			return;
		}
	}
	else
		return;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Squirt implementation
Squirt::Squirt(StudentWorld* w, int x, int y, Tunnelman* t)
	: Object(w, TID_WATER_SPURT, x, y, t->getDirection(), 1.0, 1),
	distance(4)
{
	setVisible(true);
}
bool Squirt::isAnObstacle() const { return false; }
bool Squirt::isDistributedObject() const { return false; }
bool Squirt::isPickupable() const { return false; }
Squirt::~Squirt() {}
void Squirt::doSomething()
{
	// if squirt is within a radius of 3.0 of one or more protesters:...

	if (distance == 0)
	{
		this->setToDead();
		return;
	}
	switch (getDirection())
	{
	case right:
		if (getX() + 1 <= 64)
		{
			// if target location is occupied by a earth or boulder
			// ...
			// otherwise
			if (getWorld()->isEarthPresent(getX() + 1, getY()))
				setToDead();
			distance--;
			moveTo((getX() + 1), getY());
		}
		break;
	case left:
		if (getX() - 1 >= 0)
		{
			// if target location is occupied by a earth or boulder
			// ... set squirt to dead so it can be remoed from the oil field at the end of the tick
			// otherwise
			distance--;
			moveTo((getX() - 1), getY());
		}
		break;
	case up:
		if (getY() + 1 <= 64)
		{
			// if target location is occupied by a earth or boulder
			// ...
			// otherwise
			distance--;
			moveTo((getX()), getY() + 1);
		}
		break;
	case down:
		if (getY() - 1 >= 0)
		{
			// if target location is occupied by a earth or boulder
			// ...
			// otherwise
			distance--;
			moveTo((getX()), getY() - 1);
		}
		break;
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
bool Barrel::isDistributedObject() const { return true; }
bool Barrel::isPickupable() const { return true; }
bool Barrel::isAnObstacle() const { return false; }
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
	if (visibility == false && g_tunnelmanCanPickItUp == true)
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
	/*
	else if (g_tunnelmanCanPickItUp == false) // && <= 3 units radius from a protestor))
	{
	// lifetime of 100 game ticks.
	setToDead();
	getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
	getWorld()->getTunnelman()->nuggetReceived();
	// tell protestor that it picked up the nugget (be bribed)
	getWorld()->increaseScore(25);
	}
	*/
	else if (g_100Ticks == true)
	{
		if (getWorld()->getTicks() >= 100)
		{
			setVisible(false);
			setToDead();
		}
		return;
		// if tick lifetime has elapsed, then 
		// setToDead(); // no removed by the studentworld class from the game at the end of the current tick
	}
}
void GoldNugget::setToDead() {
	setVisible(false);
	Actor::setToDead();
}
bool GoldNugget::isDistributedObject() const { return true; }
bool GoldNugget::isAnObstacle() const { return false; }
bool GoldNugget::pickupableByTunnelman() const { return g_tunnelmanCanPickItUp; }
bool GoldNugget::isPickupable() const { return true; }

/////////////////////////////////////////////////////////////
// WaterPool implementation
WaterPool::WaterPool(StudentWorld* w, int x, int y)
	: Object(w, TID_WATER_POOL, x, y, right, 1.0, 2)
{
	//setVisible(true); // already by default
	// only pickup-able by Tunnelman
}
bool WaterPool::isDistributedObject() const { return true; }
bool WaterPool::isPickupable() const { return true; }
bool WaterPool::isAnObstacle() const { return false; }
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
	if (getWorld()->getTicks() >= max(100, 300 - (10 * ((int)getWorld()->getLevel()))))
	{
		setToDead(); // removed by StudentWorld class
		return;
	}
	else
	{
		getWorld()->resetTickCount();
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
bool SonarKit::isPickupable() const { return true; }
bool SonarKit::isDistributedObject() const { return true; }
bool SonarKit::isAnObstacle() const { return false; }
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
		getWorld()->getTunnelman()->increaseSonarCount();
	}
	if (getWorld()->getTicks() >= max(100, 300 - 10 * ((int)getWorld()->getLevel())))
		setToDead();
}
