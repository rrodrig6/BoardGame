#include "PauseState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";



PauseState::PauseState()
{
	m_bIsValid = true;
}

void PauseState::s_pauseToMain()
{
	Game::Instance()->getStateMachine()->changeState( new MenuState() );
}

void PauseState::s_resumePlay()
{
	Game::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for ( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->update();
	}

	Game::Instance()->getStateMachine()->dequeueState();
}

void PauseState::render()
{
	for ( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if( !TextureManager::Instance()->load( "sprites/button.png", "resumeButton", Game::Instance()->getRenderer() ) )
	{
		return false;
	}
	if( !TextureManager::Instance()->load( "sprites/exit.png", "mainMenuButton", Game::Instance()->getRenderer() ) )
	{
		return false;
	}

	GameObject* button1 = new MenuButton( new LoaderParams( 64, 32, 32, 32, "mainMenuButton" ) , s_pauseToMain );
	GameObject* button2 = new MenuButton( new LoaderParams( 64, 64, 32, 32, "resumeButton" ) , s_resumePlay );

	m_gameObjects.push_back( button1 );
	m_gameObjects.push_back( button2 );

	std::cout << "entering PauseState\n";
	InputHandler::Instance()->reset();	
	return true;
}

bool PauseState::onExit()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap( "resumeButton" );
	TextureManager::Instance()->clearFromTextureMap( "mainMenuButton" );
	InputHandler::Instance()->reset();

	std::cout << "exiting PauseState\n";
	Game::Instance()->getStateMachine()->getBack()->onEnter();
	return true;
}
