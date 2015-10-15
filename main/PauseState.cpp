#include "PauseState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "MainMenuState.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

PauseState::PauseState() : MenuState()
{
	m_bIsValid = true;
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
	std::cout << "\n\n< PauseState::onEnter() >\n";
	StateParser stateParser;
	stateParser.parseState( "init.xml", s_pauseID, &m_gameObjects, &m_textureIDList );

	m_callbacks.push_back(s_resumePlay);
	m_callbacks.push_back(s_pauseToMain);
	setCallbacks(m_callbacks);

	std::cout << "< END PauseState::onEnter() >\n";
	return true;
}

bool PauseState::onExit()
{
	std::cout << "< PauseState::onExit() >\n";
	for( int i = 0; i < m_textureIDList.size(); i++ )
	{	
		std::cout << " cleaning texture " << m_textureIDList[i] << "\n";
		TextureManager::Instance()->clearFromTextureMap( m_textureIDList[i] );
	}

	InputHandler::Instance()->reset();


	Game::Instance()->getStateMachine()->getBack()->onEnter();
	std::cout << "< END PauseState::onExit() >\n";
	return true;
}

void PauseState::setCallbacks( const std::vector<Callback>& callbacks )
{
	std::cout << "< PauseState::setCallbacks( callbacks ) >\n";
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		if( dynamic_cast<MenuButton*>(m_gameObjects[i]) )
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback( callbacks[pButton->getCallbackID()] );
		}
	}
	std::cout << "< END PauseState::setCallbacks( callbacks ) >\n";
}

void PauseState::s_pauseToMain()
{
	std::cout << "! PauseState::s_pauseToMain() ! >\n";

	Game::Instance()->getStateMachine()->changeState( new MainMenuState() );
}

void PauseState::s_resumePlay()
{
	std::cout << "! PauseState::s_resumePlay() ! >\n";
	Game::Instance()->getStateMachine()->popState();
}
