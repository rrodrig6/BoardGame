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

	Vector2D getPosition();

private:

	void moveToNearestCell();

	bool m_bPreviousClickState;
	bool m_bIsSelected;
	int m_iUnitValue;
	
};

class GamePieceCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new GamePiece();
	}
};
