#include "PlayState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			board[y][x]->update();
		}
	}

	for( std::vector<GameObject*>::size_type i = 0 ; i != m_gameObjects.size() ; i++ )
	{
		m_gameObjects[i]->update();
	}
}

void PlayState::render()
{
	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			board[y][x]->draw();
		}
	}

	for( std::vector<GameObject*>::size_type i = 0 ; i != m_gameObjects.size() ; i++ )
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if(!TextureManager::Instance()->load( "sprites/tileGround.png", "tileGround", Game::Instance()->getRenderer() ))	
	{
		return false;
	}
	if(!TextureManager::Instance()->load( "sprites/tileWater.png", "tileWater", Game::Instance()->getRenderer() ))
	{
		return false;
	}
	if(!TextureManager::Instance()->load( "sprites/piece8.png", "piece8", Game::Instance()->getRenderer() ))
	{
		return false;
	}

	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			if( !( (y==4||y==5) && (x==2||x==3||x==6||x==7) ) )
			{
				board[y][x] = new Tile( new LoaderParams( x*32, y*32, 32, 32, "tileGround" ) );
			}
			else
			{
				board[y][x] = new Tile( new LoaderParams( x*32, y*32, 32, 32, "tileWater" ) );
			}
		}
	}

	m_gameObjects.push_back( new GamePiece( new LoaderParams( 8, 8, 16, 16, "piece8" ) ) );

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for( int y=0; y<10; y++ )
	{
		for( int x=0; x<10; x++ )
		{
			board[y][x]->clean();
		}
	}
	m_gameObjects[0]->clean();
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("tileGround");
	TextureManager::Instance()->clearFromTextureMap("tileWater");
	TextureManager::Instance()->clearFromTextureMap("piece8");

	std::cout << "exiting PlayState\n";
	return true;
}
