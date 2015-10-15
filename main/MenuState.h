#ifndef __MenuState__
#define __MenuState__
#include "GameState.h"

class MenuState : public GameState
{
public:

	virtual void update() = 0;
	virtual void render() = 0;
	
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:

	typedef void (*Callback)();
	virtual void setCallbacks( const std::vector<Callback>& callbacks ) = 0;

	std::vector<Callback> m_callbacks;
};
#endif
