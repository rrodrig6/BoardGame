#include "TileLayer.h"
#include <iostream>
#include <stdexcept>
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "Vector2D.h"

TileLayer::TileLayer( int tileSize, const std::vector<Tileset> &tilesets )
	: m_tileSize(tileSize),
		m_tilesets(tilesets),
		m_position(0,0),
		m_velocity(0,0)
{
	m_numColumns = Game::Instance()->getGameWidth() / m_tileSize;
	m_numRows = Game::Instance()->getGameHeight() / m_tileSize;
}

void TileLayer::update()
{
	m_velocity = Vector2D( 0, 0 );
	if(InputHandler::Instance()->isKeyDown( SDL_SCANCODE_W ))
	{
		m_velocity += Vector2D( 0, -2 );
	}
	if(InputHandler::Instance()->isKeyDown( SDL_SCANCODE_S ))
	{
		m_velocity += Vector2D( 0, 2 );
	}
	if(InputHandler::Instance()->isKeyDown( SDL_SCANCODE_A ))
	{
		m_velocity += Vector2D( -2, 0 );
	}
	if(InputHandler::Instance()->isKeyDown( SDL_SCANCODE_D ))
	{
		m_velocity += Vector2D( 2, 0 );
	}

	m_position += m_velocity;
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;
	
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;

	x2 = int( m_position.getX() ) % m_tileSize;
	y2 = int( m_position.getY() ) % m_tileSize;

	for( int i = 0; i <= m_numRows; i++ )
	{
		for( int j = 0; j <= m_numColumns; j++ )
		{
			int id = 0;
			try
			{
				id = m_tileIDs.at(i+y).at(j+x);
			}
			catch (const std::out_of_range& oor)
			{
				id == 0;
			}

			if( id == 0 )
			{
				continue;
			}
		
			Tileset tileset = getTilesetByID(id);

			id--;

			TextureManager::Instance()->drawTile(tileset.name, 0, 0, (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, Game::Instance()->getRenderer() );
		}
	}
}

Tileset TileLayer::getTilesetByID( int tileID )
{
	for( int i = 0; i < m_tilesets.size(); i++ )
	{
		if( i + 1 <= m_tilesets.size() - 1 )
		{
			if( tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID )
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;
}
