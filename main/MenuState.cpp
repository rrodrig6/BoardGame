#include "MenuState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";


MenuState::MenuState()
{
	m_bIsValid = true;
}


void MenuState::update()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->update();
	}

	Game::Instance()->getStateMachine()->dequeueState();
}

void MenuState::render()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	if( !TextureManager::Instance()->load( "sprites/button.png", "playbutton", Game::Instance()->getRenderer() ) )
	{
		return false;
	}
	if( !TextureManager::Instance()->load( "sprites/exit.png", "exitbutton", Game::Instance()->getRenderer() ) )
	{
		return false;
	}

	GameObject* button1 = new MenuButton( new LoaderParams( 32, 32, 32, 32, "playbutton" ), s_menuToPlay );
	GameObject* button2 = new MenuButton( new LoaderParams( 32, 64, 32, 32, "exitbutton" ), s_exitFromMenu );	

	m_gameObjects.push_back( button1 );
	m_gameObjects.push_back( button2 );

	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap( "playbutton" );
	TextureManager::Instance()->clearFromTextureMap( "exitbutton" );
	InputHandler::Instance()->reset();

	std::cout << "exiting MenuState\n";
	Game::Instance()->getStateMachine()->getBack()->onEnter();
	return true;
}

void MenuState::s_menuToPlay()
{
	Game::Instance()->getStateMachine()->changeState( new PlayState() );
}

void MenuState::s_exitFromMenu()
{
	Game::Instance()->quit();
}

