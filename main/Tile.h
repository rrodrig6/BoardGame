#ifndef __Tile__
#define __Tile__
#include <string>
#include <stdio.h>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Tile : public SDLGameObject
{
public:

	Tile();

	void load(const LoaderParams *pParams);
	void draw();
	void update();
	void clean();

private:

};

class TileCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Tile();
	}
};
#endif
