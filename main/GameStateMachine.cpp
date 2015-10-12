#include "GameStateMachine.h"
#include "InputHandler.h"

void GameStateMachine::pushState( GameState *pState )
{
	printf("pushState\n");
	m_gameStates.push_back( pState );
	m_gameStates.back()->onEnter();
	printf("gameStates.size = %d\n", m_gameStates.size());
}

void GameStateMachine::changeState( GameState *pState )
{
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
				m_gameStates[i]->setIsValid( false );
			}
		}
	}
	printf("changeState\n");
	m_gameStates.push_back( pState );
//	m_gameStates.back()->onEnter();
	printf("gameStates.size = %d\n", m_gameStates.size());
}

void GameStateMachine::popState()
{
	if( !m_gameStates.empty() )
	{
		if( m_gameStates.back()->onExit() )
		{
			printf("popState\n");
			delete m_gameStates.back();
			m_gameStates.pop_back();
			printf("gameStates.size = %d\n", m_gameStates.size());
		}
	}
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

