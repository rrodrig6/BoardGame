#ifndef __PlayState__
#define __PlayState__
#include "GameState.h"
#include <vector>
#include "Tile.h"
#include "GamePiece.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	
	static const std::string s_playID;

	Tile* board [10][10];
	std::vector<GamePiece*> m_gameObjects;

};
#endif
