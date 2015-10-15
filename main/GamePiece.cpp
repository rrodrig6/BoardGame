#include "GamePiece.h"
#include "InputHandler.h"

GamePiece::GamePiece() : SDLGameObject()
{

}

void GamePiece::load( const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}

void GamePiece::draw()
{
	SDLGameObject::draw();
}

void GamePiece::update()
{
	if( InputHandler::Instance()->getMouseButtonState( LEFT ) )
	{
		m_position = Vector2D( InputHandler::Instance()->getMousePosition()->getX(), InputHandler::Instance()->getMousePosition()->getY() );
		moveToNearestCell();	
	}
	else
	{
		
	}

	m_velocity = Vector2D( 0, 0 );
	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_RIGHT ) )
	{
		m_velocity.setX( 1 );
	}
	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_LEFT ) )
	{
		m_velocity.setX( -1 );
	}
	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_UP ) )
	{
		m_velocity.setY( -1 );
	}
	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_DOWN ) )
	{
		m_velocity.setY( 1 );
	}

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
