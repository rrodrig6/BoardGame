#include "GameStateMachine.h"
#include "InputHandler.h"
#include <iostream>

void GameStateMachine::pushState( GameState *pState )
{
	std::cout << "< GameStateMachine:pushState( " << (pState->getStateID()) << " ) >\n";
	m_gameStates.push_back( pState );
	std::cout << " " << m_gameStates.back()->getStateID() << "->onEnter()\n";
	m_gameStates.back()->onEnter();
	std::cout << " gameStates.size is " << m_gameStates.size() << "\n";
	std::cout << "< END GameStateMachine::pushState " << pState->getStateID() << " ) >\n";
}

void GameStateMachine::changeState( GameState *pState )
{
	std::cout << "< GameStateMachine::changeState( " << pState->getStateID() << " ) >\n";
	if( !m_gameStates.empty() )
	{
		if( m_gameStates.back()->getStateID() == pState->getStateID() )
		{
			return;
		}
		for( int i = 0; i < m_gameStates.size() ; i++ )
		{
			if( m_gameStates[i]->getIsValid() )
			{
				std::cout << " m_gameStates[" << i <<"] is being invalidated\n";
				m_gameStates[i]->setIsValid( false );
			}
		}
	}
	std::cout << " m_gameStates.push_back( " << pState->getStateID() << " )\n";
	m_gameStates.push_back( pState );
	std::cout << " m_gameStates.size is " << m_gameStates.size() << "\n";
	std::cout << "< END GameStateMachine::changeState( " << pState->getStateID() << " ) >\n";
}

void GameStateMachine::popState()
{
	std::cout << "< GameStateMachine::popState() >\n";
	if( !m_gameStates.empty() )
	{
		
		if( m_gameStates.back()->onExit() )
		{
			std::cout << " deleting " << m_gameStates.back()->getStateID() << "\n";
			delete m_gameStates.back();
			m_gameStates.pop_back();
			std::cout << " gameStates.size is " << m_gameStates.size() << "\n";
		}
	}
	std::cout << "< END GameStateMachine::popState() >\n";
}

void GameStateMachine::dequeueState()
{
	
	if( !m_gameStates.empty() )
	{
//		while( m_gameStates.size() > 1 )
//		{
			if( !m_gameStates.front()->getIsValid() && m_gameStates.front()->onExit() )
			{
				delete m_gameStates[0];
				m_gameStates.erase( m_gameStates.begin() );
				printf("gameStates.size = %d\n", m_gameStates.size());
				InputHandler::Instance()->reset();
			}
//		}
	}
}

void GameStateMachine::update()
{
	if( !m_gameStates.empty() )
	{
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render()
{
	if( !m_gameStates.empty() )
	{
		m_gameStates.back()->render();
	}
}

