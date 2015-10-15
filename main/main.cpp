#include "Game.h"
#include <iostream>

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main ( int argc, char* argv[] )
{
	// Used to maintain a fixed frame rate;
	Uint32 frameStart, frameTime;

	std::cout << "< main >\n init\n";
	// Initialize Game instance and continue if successful
	if( Game::Instance()->init( "StratBoard", 100, 100, 384, 320, false ) )
	{
		// Main game loop
		std::cout << " entering main loop\n";
		while( Game::Instance()->running() )
		{			
			frameStart = SDL_GetTicks();
			
			Game::Instance()->handleEvents();
			//std::cout << " update\n";
			Game::Instance()->update();
			//std::cout << " render\n";
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			// Adjust delay to maintain fixed frame rate
			if( frameTime < DELAY_TIME )
			{
				//std::cout << " delaying " << (int) (DELAY_TIME - frameTime) << "ms\n";
				SDL_Delay((int) (DELAY_TIME - frameTime));		
			}
		}
	}
	else
	{
		printf( "Game init failure! SDL Errror: %s\n", SDL_GetError() );
		return -1;
	}
	
	printf( " game closing...\n" );
	Game::Instance()->clean();
	std::cout << "< END main >\n";

	return 0;
}
