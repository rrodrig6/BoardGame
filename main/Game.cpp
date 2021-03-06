#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Board.h"


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

	m_gameWidth = width;
	m_gameHeight = height;

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

		// Load object types into the GameObjectFactory
		GameObjectFactory::Instance()->registerType( "MenuButton", new MenuButtonCreator() );
		GameObjectFactory::Instance()->registerType( "Board", new BoardCreator() );
		GameObjectFactory::Instance()->registerType( "Tile" , new TileCreator() );
		GameObjectFactory::Instance()->registerType( "GamePiece" , new GamePieceCreator() );

		//Initialize GameStateMachine and load menu state
		m_pGameStateMachine = new GameStateMachine();
		m_pGameStateMachine->changeState( new MainMenuState() );
		m_pGameStateMachine->getBack()->onEnter();
	}
	m_bRunning = true;

	return success;
}

//--update()---------------------------
void Game::update()
{
	m_pGameStateMachine->update();
}

//--render()------------------------------
void Game::render()
{
	SDL_RenderClear( m_pRenderer );
	m_pGameStateMachine->render();
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

//--handleEvents()----------------------------------
void Game::handleEvents()
{
	InputHandler::Instance()->update();
}

//--getRenderer()-----------------------------------
SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}
