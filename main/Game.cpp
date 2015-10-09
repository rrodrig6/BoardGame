#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"


Game* Game::s_pInstance = NULL;

SDL_Window* m_pWindow = NULL;
SDL_Renderer* m_pRenderer = NULL;

std::vector<GamePiece*> m_gameObjects;

//--Instance()--------------------------------
Game* Game::Instance()
{
	if( !s_pInstance )
	{
		s_pInstance = new Game();
	}
	return s_pInstance;
}

//--init()------------------------------------
bool Game::init( const char* title, int xpos, int ypos, int width, int height, bool fullscreen )
{
	// Translate fullscreen parameter to SDL_Init flags
	int flags = 0;
	if( fullscreen )
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//Initialization success flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		m_pWindow = SDL_CreateWindow( "StratBoard", xpos, ypos, width, height, flags );
		if( m_pWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, SDL_RENDERER_ACCELERATED);
			if( m_pRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( m_pRenderer, 0x80, 0x70, 0x30, 0xFF );
	
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
		// END Initialize SDL

		//Initialize GameStateMachine and load menu state
		m_pGameStateMachine = new GameStateMachine();
		m_pGameStateMachine->changeState( new MenuState() );
	}

	
	//Load media
	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
		success = false;
	}
	
	//Load object positions, assign textures
	loadGameObjects();

	m_bRunning = true;

	return success;
}

//--loadMedia()---------------
bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	if(!TextureManager::Instance()->load("sprites/tileGround.png", "tileGround", m_pRenderer))	
	{
		success = false;
	}
	if(!TextureManager::Instance()->load("sprites/tileWater.png", "tileWater", m_pRenderer))
	{
		success = false;
	}
	if(!TextureManager::Instance()->load("sprites/piece8.png", "piece8", m_pRenderer))
	{
		success = false;
	}
	return success;

}


//--loadGameObjects()-----------
void Game::loadGameObjects()
{
	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			if( !( (y==4||y==5) && (x==2||x==3||x==6||x==7) ) )
			{
				board[y][x] = new Tile( new LoaderParams( x*32, y*32, 32, 32, "tileGround" ) );
			}
			else
			{
				board[y][x] = new Tile( new LoaderParams( x*32, y*32, 32, 32, "tileWater" ) );
			}
		}
	}

	m_gameObjects.push_back( new GamePiece( new LoaderParams( 8, 8, 16, 16, "piece8" ) ) );
}

//--update()---------------------------
void Game::update()
{

	m_pGameStateMachine->update();

/*
	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			board[y][x]->update();
		}
	}

	for( std::vector<GameObject*>::size_type i = 0 ; i != m_gameObjects.size() ; i++ )
	{
		m_gameObjects[i]->update();
	}
*/
}

//--render()------------------------------
void Game::render()
{
	
	SDL_RenderClear( m_pRenderer );

	m_pGameStateMachine->render();
	
/*
	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			board[y][x]->draw();
		}
	}

	for( std::vector<GameObject*>::size_type i = 0 ; i != m_gameObjects.size() ; i++ )
	{
		m_gameObjects[i]->draw();
	}
*/
	
	SDL_RenderPresent( m_pRenderer );
}

//--running()-------------------------------------
bool Game::running()
{
	return m_bRunning;
}

//--quit()----------------------------------------
void Game::quit()
{
	m_bRunning = false;
}

//--clean()---------------------------------------
void Game::clean()
{	
	InputHandler::Instance()->clean();

	//Destroy Window
	SDL_DestroyRenderer( m_pRenderer );
	SDL_DestroyWindow( m_pWindow );
	m_pWindow = NULL;
	m_pRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//--handleEvents()---------------------------------
void Game::handleEvents()
{
	InputHandler::Instance()->update();

	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_RETURN ) )
	{
		m_pGameStateMachine->changeState( new PlayState() );
	}
}

//--getRenderer()-----------------------------------
SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}
