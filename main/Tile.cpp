#include "Tile.h"
#include <iostream>
#include "InputHandler.h"

Tile::Tile() : SDLGameObject()
{
	m_TileID = 0;
	m_pGamePiece = NULL;
	m_bGamePieceSelected = false;
	m_bPreviousClickState = false;
}

void Tile::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}

void Tile::draw()
{
	m_currentFrame = m_TileID;
	SDLGameObject::draw();
	if(m_pGamePiece)
	{
		std::cout << "drawing piece\n" ;
		m_pGamePiece->draw();
	}
}

void Tile::update()
{
	if( m_pGamePiece )
	{
		m_pGamePiece->update();
	}

	if( 	InputHandler::Instance()->getMousePosition()->getX() >= m_position.getX() && InputHandler::Instance()->getMousePosition()->getX() < m_position.getX() + 32
		&&	InputHandler::Instance()->getMousePosition()->getY() >= m_position.getY() && InputHandler::Instance()->getMousePosition()->getY() < m_position.getY() + 32
	)
	{
		m_currentRow = 1;
		if(  m_pGamePiece
			&& !m_bPreviousClickState
			&& InputHandler::Instance()->getMouseButtonState( LEFT ) )
		{
			m_pGamePiece->selectGamePiece();
		}
	}
	else
	{
		m_currentRow = 0;
	}

	m_bPreviousClickState = InputHandler::Instance()->getMouseButtonState( LEFT );
	
	SDLGameObject::update();
}

void Tile::clean()
{
	if( m_pGamePiece )
	{
		delete m_pGamePiece;
		m_pGamePiece = NULL;
	}
	SDLGameObject::clean();
}
