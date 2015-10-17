#include "Board.h"

Board::Board() : SDLGameObject()
{
	for( int y = 0; y < 10; y++ )
	{
		for( int x = 0; x < 10; x++ )
		{
			tiles[y][x] = new Tile();
			tiles[y][x]->load( new LoaderParams( x*32, y*32, 32, 32, "tiles", 2, 0, 0 ) );
			if(
			 ( y == 4 || y == 5 ) &&
			 ( x == 2 || x == 3 || x == 6 || x == 7 )
			)
			{
				tiles[y][x]->m_TileID = 1;
			}
		}
	}
}

void Board::load( const LoaderParams *pParams )
{
	SDLGameObject::load(pParams);
}

void Board::draw()
{
	for( int y = 0; y < 10; y++ )
	{
		for( int x = 0; x < 10; x++ )
		{
			tiles[y][x]->draw();
		}
	}
	SDLGameObject::draw();
}

void Board::update()
{
	for( int y = 0; y < 10; y++ )
	{
		for( int x = 0; x < 10; x++ )
		{
			tiles[y][x]->update();
		}
	}
	SDLGameObject::update();
}

void Board::clean()
{
	for( int y = 0; y < 10; y++ )
	{
		for( int x = 0; x < 10; x++ )
		{
			delete tiles[y][x];
			tiles[y][x] = NULL;
		}
	}

	SDLGameObject::clean();
}
