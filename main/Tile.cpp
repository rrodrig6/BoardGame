#include "Tile.h"

Tile::Tile() : SDLGameObject()
{
	m_TileID = 0;
}

void Tile::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}

void Tile::draw()
{
	m_currentFrame = m_TileID;
	SDLGameObject::draw();
}

void Tile::update()
{
	SDLGameObject::update();
}

void Tile::clean()
{
	SDLGameObject::clean();
}
