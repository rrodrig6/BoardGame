#ifndef __GamePiece__
#define __GamePiece__
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class GamePiece : public SDLGameObject
{
public:

	GamePiece();

	void load(const LoaderParams *pParams);
	void draw();
	void update();
	void clean();

	void setUnitValue( int value ) { m_iUnitValue = value; }
	int getUnitValue() { return m_iUnitValue; }
	void moveToNearestCell();
	void selectGamePiece();

	Vector2D getPosition();

private:

	bool m_bPreviousClickState;
	bool m_bSelected;
	int m_iUnitValue;
	
};

class GamePieceCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new GamePiece();
	}
};
#endif
