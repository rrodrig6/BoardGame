#ifndef __Board__
#define __Board__
#include <string>
#include <stdio.h>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
#include "Tile.h"

class Board : public SDLGameObject
{
public:

	Board();

	void load(const LoaderParams *pParams);
	void draw();
	void update();
	void clean();

private:
	
	Tile* tiles [10][10];

};

class BoardCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Board();
	}
};
#endif
