#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance();

	void update();
	void clean();

	void reset();

	bool getMouseButtonState( int buttonNumber )
	{
		return m_mouseButtonStates[buttonNumber];
	};

	Vector2D* getMousePosition()
	{
		return m_mousePosition;
	};

	bool isKeyDown( SDL_Scancode key );


private:

	InputHandler();
	~InputHandler() {};
	InputHandler( InputHandler const& ) {};
	InputHandler& operator=( InputHandler const& ) {};


	//Keyboard
	void onKeyDown();
	void onKeyUp();

	//Mouse
	void onMouseMove( SDL_Event& event );
	void onMouseButtonDown( SDL_Event& event );
	void onMouseButtonUp( SDL_Event& event );

	

	static InputHandler* s_pInstance;

	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

	const Uint8* m_keystates;

};
