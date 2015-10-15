#include "GameOverState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "MenuButton.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::GameOverState() : MenuState()
{
	m_bIsValid = true;
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
	std::cout << "\n\n< GameOverState::onEnter() >\n";
	StateParser stateParser;
	stateParser.parseState( "init.xml", s_gameOverID, &m_gameObjects, &m_textureIDList );

	m_callbacks.push_back(s_restartPlay);
	m_callbacks.push_back(s_gameOverToMain);
	setCallbacks(m_callbacks);

	std::cout << "< END GameOverState::onEnter() >\n";
	return true;
}

bool GameOverState::onExit()
{
	std::cout << "< MainMenuState::onExit() >\n";
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		std::cout << " cleaning m_gameObjects[" << i << "]\n";
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	// Clear textures
	for( int i = 0; i < m_textureIDList.size(); i++ )
	{
		std::cout << " cleaning texture " << m_textureIDList[i] << "\n";
		TextureManager::Instance()->clearFromTextureMap( m_textureIDList[i] );
	}

	InputHandler::Instance()->reset();

	Game::Instance()->getStateMachine()->getBack()->onEnter();
	std::cout << "< END GameOverState::onExit() >\n";
	return true;
}

void GameOverState::setCallbacks( const std::vector<Callback>& callbacks )
{
	std::cout << "< GameOverState::setCallbacks( callbacks ) >\n";
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		if( dynamic_cast<MenuButton*>(m_gameObjects[i]) )
		{
			MenuButton *pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback( callbacks[pButton->getCallbackID()] );
		}
	}
	std::cout << "< END GameOverState::setCallbacks( callbacks ) >\n";
}

void GameOverState::s_gameOverToMain()
{
	std::cout << "! GameOverState::s_gameOverToMain() !\n";
	Game::Instance()->getStateMachine()->changeState( new MainMenuState() );
}

void GameOverState::s_restartPlay()
{
	std::cout << "! GameOverState::s_restartPlay() !\n";
	Game::Instance()->getStateMachine()->changeState( new PlayState() );
}

