#ifndef __PlayState__
#define __PlayState__
#include "GameState.h"
#include <vector>
#include "Tile.h"
#include "Level.h"
#include "GamePiece.h"

class PlayState : public GameState
{
public:

	PlayState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	
	static const std::string s_playID;

	Level* pLevel;

	std::vector<GameObject*> m_gameObjects;

};
#endif
