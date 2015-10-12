#include "SDLGameObject.h"

class GamePiece : public SDLGameObject
{
public:

	GamePiece( const LoaderParams* pParams );

	void draw();
	void update();
	void clean();

	Vector2D getPosition();

private:

	void moveToNearestCell();
	
};
