#ifndef __GameObjectFactory__
#define __GameObjectFactory__
#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
	public:

	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
	static	GameObjectFactory* Instance();

	bool registerType( std::string typeID, BaseCreator* pCreator );
	GameObject* create( std::string typeID );

private:

	GameObjectFactory(){};
	~GameObjectFactory(){};
	GameObjectFactory( GameObjectFactory const &){};
	GameObjectFactory& operator=( GameObjectFactory const &){};

	std::map<std::string, BaseCreator*> m_creators;

	static GameObjectFactory* s_pInstance;

};
#endif
