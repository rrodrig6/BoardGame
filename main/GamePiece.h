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

	Vector2D getPosition();

private:

	void moveToNearestCell();
	
};

class GamePieceCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new GamePiece();
	}
};
