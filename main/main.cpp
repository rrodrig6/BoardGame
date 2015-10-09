#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main ( int argc, char* argv[] )
{
	// Used to maintain a fixed frame rate;
	Uint32 frameStart, frameTime;

	// Initialize Game instance and continue if successful
	if( Game::Instance()->init( "StratBoard", 100, 100, 384, 320, false ) )
	{
		// Main game loop
		while( Game::Instance()->running() )
		{
	
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			// Adjust delay to maintain fixed frame rate
			if( frameTime < DELAY_TIME )
			{
				SDL_Delay((int) (DELAY_TIME - frameTime));		
			}
		}
	}
	else
	{
		printf( "Game init failure! SDL Errror: %s\n", SDL_GetError() );
		return -1;
	}
	
	printf( "Game closing...\n" );
	Game::Instance()->clean();

	return 0;
}
