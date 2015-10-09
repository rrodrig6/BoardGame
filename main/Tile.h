#include <string>
#include <stdio.h>
#include "SDLGameObject.h"

class Tile : public SDLGameObject
{
public:

	Tile( const LoaderParams* pParams );

	void draw();
	void update();
	void clean();

private:

};
