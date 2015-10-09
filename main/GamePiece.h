#include "SDLGameObject.h"

class GamePiece : public SDLGameObject
{
public:

	GamePiece( const LoaderParams* pParams );

	void draw();
	void update();
	void clean();

private:

	void moveToNearestCell();
	
};
