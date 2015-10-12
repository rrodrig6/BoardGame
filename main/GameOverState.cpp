#include "GameOverState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::GameOverState()
{
	m_bIsValid = true;
}

void GameOverState::s_gameOverToMain()
{
	Game::Instance()->getStateMachine()->changeState( new MenuState() );
}

void GameOverState::s_restartPlay()
{
	Game::Instance()->getStateMachine()->changeState( new PlayState() );
}

void GameOverState::update()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->update();
	}
	Game::Instance()->getStateMachine()->dequeueState();
}

void GameOverState::render()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	if( !TextureManager::Instance()->load( "sprites/button.png", "startNewButton", Game::Instance()->getRenderer() ) )	
	{
		return false;
	}
	if( !TextureManager::Instance()->load( "sprites/exit.png", "backToMenuButton", Game::Instance()->getRenderer() ) )
	{
		return false;
	}

	GameObject* button1 = new MenuButton( new LoaderParams( 96, 32, 32, 32, "startNewButton" ), s_restartPlay );
	GameObject* button2 = new MenuButton( new LoaderParams( 96, 64, 32, 32, "backToMenuButton" ), s_gameOverToMain );

	m_gameObjects.push_back( button1 );
	m_gameObjects.push_back( button2 );
	InputHandler::Instance()->reset();

	std::cout << "entering GameOver state\n";
	return true;
}

bool GameOverState::onExit()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap( "startNewButton" );
	TextureManager::Instance()->clearFromTextureMap( "backToMenuButton" );
	InputHandler::Instance()->reset();

	std::cout << "exiting GameOverState\n";
	Game::Instance()->getStateMachine()->getBack()->onEnter();
	return true;
}
