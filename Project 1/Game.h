#ifndef GAME_HEADER
#define GAME_HEADER
class Arena; // we use define a pointer of type Arena as a private data member
class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nRobots);
	~Game();

	// Mutators
	void play();

private:
	Arena * m_arena;
};
#endif