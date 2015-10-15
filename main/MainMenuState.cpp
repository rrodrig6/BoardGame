#include "MainMenuState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "PlayState.h"
#include "MenuButton.h"

const std::string MainMenuState::s_menuID = "MENU";

MainMenuState::MainMenuState()
{
	m_bIsValid = true;
}

void MainMenuState::update()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->update();
	}

	Game::Instance()->getStateMachine()->dequeueState();
}

void MainMenuState::render()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{
	std::cout << "\n\n< MainMenuState::onEnter() >\n";
	StateParser stateParser;
	stateParser.parseState( "init.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
	setCallbacks( m_callbacks );

	std::cout << "< END MainMenuState::onEnter() >\n";
	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "< MainMenuState::onExit() >\n";
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		std::cout << " cleaning m_gameObjects[" << i << "]\n";
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	
	// clear the texture manager
	for( int i = 0; i < m_textureIDList.size(); i++ )
	{
		std::cout << " cleaning texture " << m_textureIDList[i] << "\n";
		TextureManager::Instance()->clearFromTextureMap( m_textureIDList[i] );
	}

	InputHandler::Instance()->reset();

	Game::Instance()->getStateMachine()->getBack()->onEnter();
	std::cout << "< END MainMenuState::onExit() >\n";
	return true;
}

void MainMenuState::setCallbacks( const std::vector<Callback>& callbacks )
{
	std::cout << "< MainMenuState::setCallbacks( callbacks ) >\n";
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		// if they are of the type MenuButton then assign a callback based on the id passed in from the file
		if( dynamic_cast<MenuButton*>(m_gameObjects[i]) )
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback( callbacks[pButton->getCallbackID()] );
		}
	}
	std::cout << "< END MainMenuState::setCallbacks( callbacks ) >\n";
}

void MainMenuState::s_menuToPlay()
{
	std::cout << "! MainMenuState::s_menuToPlay() !\n";
	Game::Instance()->getStateMachine()->changeState( new PlayState() );
}

void MainMenuState::s_exitFromMenu()
{
	std::cout << "! MainMenuState::s_exitFromMenu() !\n";
	Game::Instance()->quit();
}

