#include "PlayState.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "LevelParser.h"

const std::string PlayState::s_playID = "PLAY";

PlayState::PlayState()
{
	m_bIsValid = true;
}

void PlayState::update()
{
	// Check input
	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		Game::Instance()->getStateMachine()->pushState( new PauseState() );
	}
	if( InputHandler::Instance()->isKeyDown( SDL_SCANCODE_RETURN ) )
	{
		Game::Instance()->getStateMachine()->pushState( new GameOverState() );
	}
	// Update GameObjects
	for( std::vector<GameObject*>::size_type i = 0 ; i != m_gameObjects.size() ; i++ )
	{
		m_gameObjects[i]->update();
	}
	// Game Over condition (place piece in lower right corner)
	/*
	std::cout << "This?";
	GamePiece* pPiece = dynamic_cast<GamePiece*>(m_gameObjects[2]);
	std::cout << "Nope.";
	if( pPiece->getPosition().getX() == 296 && pPiece->getPosition().getY() == 296 )
	{
		Game::Instance()->getStateMachine()->pushState( new GameOverState() );
	}
	*/
	pLevel->update();
	// Check to dequeue state
	Game::Instance()->getStateMachine()->dequeueState();
}

void PlayState::render()
{
/*
	for( std::vector<GameObject*>::size_type i = 0 ; i != m_gameObjects.size() ; i++ )
	{
		m_gameObjects[i]->draw();
	}
*/
	pLevel->render();
}

bool PlayState::onEnter()
{
	std::cout << "\n\n< PlayState::onEnter() >\n";
/*	StateParser stateParser;
	stateParser.parseState( "init.xml", s_playID, &m_gameObjects, &m_textureIDList );
*/
	LevelParser levelParser;
	pLevel = levelParser.parseLevel( "board.tmx" );	

	std::cout << "< END PlayState::onEnter() >\n";
	return true;
}

bool PlayState::onExit()
{
	std::cout << "< PlayState::onExit() >\n";
	for( int i = 0; i < m_textureIDList.size(); i++ )
	{	
		std::cout << " clearing texture " << m_textureIDList[i] << "\n";
		TextureManager::Instance()->clearFromTextureMap( m_textureIDList[i] );
	}
	Game::Instance()->getStateMachine()->getBack()->onEnter();	
	std::cout << "< END PlayState::onExit() >\n";
	return true;
}
