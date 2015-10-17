#include "GamePiece.h"
#include "InputHandler.h"

GamePiece::GamePiece() : SDLGameObject()
{
	m_bPreviousClickState = false;
	m_bIsSelected = false;
	m_iUnitValue = 1;
}

void GamePiece::load( const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}

void GamePiece::draw()
{
	m_currentFrame = m_iUnitValue;
	SDLGameObject::draw();
}

void GamePiece::update()
{
	if( InputHandler::Instance()->getMouseButtonState( LEFT ) )
	{
		if( 
				!m_bIsSelected && !m_bPreviousClickState
		 &&	InputHandler::Instance()->getMousePosition()->getX() >= m_position.getX() && InputHandler::Instance()->getMousePosition()->getX() < m_position.getX() + 32
		 &&	InputHandler::Instance()->getMousePosition()->getY() >= m_position.getY() && InputHandler::Instance()->getMousePosition()->getY() < m_position.getY() + 32
		)
		{
			m_bIsSelected = true;
		}
	}
	else
	{
		m_bIsSelected = false;
	}

	if( m_bIsSelected )
	{
		m_position = Vector2D( InputHandler::Instance()->getMousePosition()->getX(), InputHandler::Instance()->getMousePosition()->getY() );
		moveToNearestCell();	
	}

	m_bPreviousClickState = InputHandler::Instance()->getMouseButtonState( LEFT );

	SDLGameObject::update();
}

void GamePiece::clean()
{
	SDLGameObject::clean();
}

Vector2D GamePiece::getPosition()
{
	return m_position;
}

void GamePiece::moveToNearestCell()
{
	int xGrid = int( m_position.getX() / 32 );
	int yGrid = int( m_position.getY() / 32 );

	m_position = Vector2D( (xGrid*32)+8, (yGrid*32)+8 );
}
