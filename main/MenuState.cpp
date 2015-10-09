#include "MenuState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->update();
	}
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

	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
}

void MenuState::s_exitFromMenu()
{
	Game::Instance()->quit();
}

