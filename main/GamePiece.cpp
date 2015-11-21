#include "GamePiece.h"
#include "InputHandler.h"

GamePiece::GamePiece() : SDLGameObject()
{
	m_bPreviousClickState = false;
	m_bSelected = false;
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
	if( m_bSelected )
	{
		m_position = Vector2D( InputHandler::Instance()->getMousePosition()->getX(), InputHandler::Instance()->getMousePosition()->getY() );
		moveToNearestCell();
		if(  !InputHandler::Instance()->getMouseButtonState( LEFT ) 
			&& m_bPreviousClickState )
		{
			m_bSelected = false;
		}
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

void GamePiece::selectGamePiece()
{
	m_bSelected = true;
}
