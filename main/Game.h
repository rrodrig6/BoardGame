// Game.h
//
//	This class is at the top of the game hierarchy. It initializes the SDL window and renderer,
// the GameStateMachine to handle game states, the TextureHandler to manage texture loading and
// drawing, and the InputHandler to handle events and input.

#ifndef __Game__
#define __Game__
#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __linux
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif
#include <stdio.h>
#include "GameStateMachine.h"


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
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

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

};
#endif
