#include "InputHandler.h"
#include <iostream>
#include "Game.h"

InputHandler* InputHandler::s_pInstance = NULL;

InputHandler* InputHandler::Instance()
{
	if( !s_pInstance )
	{
		s_pInstance = new InputHandler();
	}
	return s_pInstance;

}

InputHandler::InputHandler()
{
	m_keystates = SDL_GetKeyboardState(0);
	m_mousePosition = new Vector2D( 0, 0 );
	for( int i=0; i<3; i++ )
	{
		m_mouseButtonStates.push_back( false );
	}
}

void InputHandler::update()
{
	SDL_Event event;

	while( SDL_PollEvent( &event ))
	{
		switch ( event.type )
		{
		case SDL_QUIT:
			Game::Instance()->quit();
		break;
		
		case SDL_MOUSEMOTION:
			onMouseMove( event );
		break;
	
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown( event );
		break;
		
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp( event );
		break;

		case SDL_KEYDOWN:
			onKeyDown();
		break;

		case SDL_KEYUP:
			onKeyUp();
		break;

		default:
		break;
		}
	}
}

void InputHandler::reset()
{
	printf("! InputHandler::reset() !\n");
	m_mouseButtonStates[LEFT] = false;
	m_mouseButtonStates[MIDDLE] = false;
	m_mouseButtonStates[RIGHT] = false;
	SDL_FlushEvents( SDL_QUIT , SDL_USEREVENT );
}

void InputHandler::onMouseMove( SDL_Event& event )
{
	m_mousePosition->setX( event.motion.x );
	m_mousePosition->setY( event.motion.y );
}

void InputHandler::onMouseButtonDown( SDL_Event& event )
{
	if( event.button.button == SDL_BUTTON_LEFT )
	{
		std::cout << "! LMB Down !\n";
		m_mouseButtonStates[LEFT] = true;
	}
	if( event.button.button == SDL_BUTTON_MIDDLE )
	{
		std::cout << "! MMB Down !\n";
		m_mouseButtonStates[MIDDLE] = true;
	}
	if( event.button.button == SDL_BUTTON_RIGHT )
	{
		std::cout << "! RMB Down !\n";
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp( SDL_Event& event )
{
	if( event.button.button == SDL_BUTTON_LEFT )
	{
		std::cout << "! LMB Up !\n";
		m_mouseButtonStates[LEFT] = false;
	}
	if( event.button.button == SDL_BUTTON_MIDDLE )
	{
		std::cout << "! MMB Up !\n";
		m_mouseButtonStates[MIDDLE] = false;
	}
	if( event.button.button == SDL_BUTTON_RIGHT )
	{
		std::cout << "! RMB Up !\n";
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}

bool InputHandler::isKeyDown( SDL_Scancode key )
{
	if( m_keystates != 0 )
	{
		if( m_keystates[key] )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void InputHandler::clean()
{
	delete m_mousePosition;
}
