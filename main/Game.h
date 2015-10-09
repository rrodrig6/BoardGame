// Game.h
//
//	This class is at the top of the game hierarchy. It initializes the SDL window and renderer,
// the GameStateMachine to handle game states, the TextureHandler to manage texture loading and
// drawing, and the InputHandler to handle events and input.

#ifndef __Game__
#define __Game__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>
#include "GameStateMachine.h"
#include "GameObject.h"
#include "Tile.h"
#include "GamePiece.h"


class Game
{
public:

	// Singleton instance of Game
	static Game* Instance();
	
	bool init( const char* title, int xpos, int ypos, int width, int height, bool fullscreen );
	bool loadMedia();
	void loadGameObjects();
	
	void render();
	void update();
	void handleEvents();
	
	bool running();
	void quit();
	void clean();
	
	SDL_Renderer* getRenderer();	

private:

	Game() {};
	Game(Game const&) {};
	Game& operator=(Game const&) {};
	static Game* s_pInstance;
	typedef Game TheGame;
	
	GameStateMachine* m_pGameStateMachine;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;

	Tile* board [10][10];

	std::vector<GamePiece*> m_gameObjects;
};
#endif
