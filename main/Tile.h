#ifndef __Tile__
#define __Tile__
#include <string>
#include <stdio.h>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
#include "GamePiece.h"

class Tile : public SDLGameObject
{
public:

	Tile();

	void load(const LoaderParams *pParams);
	void draw();
	void update();
	void clean();
	
	GamePiece* getGamePiece()  { return m_pGamePiece; }
	void setGamePiece( GamePiece* pGamePiece ) { m_pGamePiece = pGamePiece; }

	int m_TileID;

private:

	GamePiece* m_pGamePiece;
	
	bool m_bGamePieceSelected;
	bool m_bPreviousClickState;

	

};

class TileCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Tile();
	}
};
#endif
