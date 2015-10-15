#OBJS specifies which files to compile as part of the project
OBJS = main.cpp\
	tinystr.h tinystr.cpp tinyxml.h tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp\
	Game.h Game.cpp\
	TextureManager.h TextureManager.cpp\
	InputHandler.h InputHandler.cpp\
	GameStateMachine.h GameStateMachine.cpp\
	StateParser.h StateParser.cpp\
	GameObjectFactory.h GameObjectFactory.cpp\
	MenuState.h\
	MainMenuState.h MainMenuState.cpp\
	PlayState.h PlayState.cpp\
	PauseState.h PauseState.cpp\
	GameOverState.h GameOverState.cpp\
	GameObject.h\
	SDLGameObject.h SDLGameObject.cpp\
	Vector2D.h\
	MenuButton.h MenuButton.cpp\
	Tile.h Tile.cpp\
	GamePiece.h GamePiece.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# - suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the additional compilation options we're using
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our executable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
db  : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -g $(LINKER_FLAGS) -o $(OBJ_NAME)
