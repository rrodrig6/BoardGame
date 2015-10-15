#include "StateParser.h"
#include <iostream>
#include <string>
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"

bool StateParser::parseState( const char *stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs )
{
	std::cout << "< StateParser::parseState( " << stateFile << ", " << stateID << ", pObjects, pTextureIDs) >\n";
	// create the XML document
	TiXmlDocument xmlDoc;
	
	// load the state file
	if( !xmlDoc.LoadFile( stateFile ) )
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}
	std::cout << " XML File Loaded\n";

	// get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	std::cout << " Got Document Root\n";

	// pre declare the state's root node
	TiXmlElement* pStateRoot = 0;

	// get this state's root node and assign it to pStateRoot
	for( TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement() )
	{
		if( e->Value() == stateID )
		{
			pStateRoot = e;
		}
	}

	std::cout << " Got State Root\n";

	// pre-declare the texture root
	TiXmlElement* pTextureRoot = 0;

	// get the root of the texture elements
	for( TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL ; e = e->NextSiblingElement() )
	{
		if( e->Value() == std::string("TEXTURES") )
		{
			pTextureRoot = e;
		}
	}

	std::cout << " Got Texture Root\n";

	// now parse the textures
	parseTextures( pTextureRoot, pTextureIDs );

	std::cout << " Parsed textures\n";

	// pre-declare the object root node
	TiXmlElement* pObjectRoot = 0;

	// get the root node and assign it to pObjectRoot
	for( TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement() )
	{
		if( e->Value() == std::string("OBJECTS") )
		{
			pObjectRoot = e;
		}
	}

	std::cout << " Got Object Root\n";

	// now parse the objects
	parseObjects( pObjectRoot, pObjects );

	std::cout << " Parsed objects\n";	
	std::cout << "< END StateParser::parseState( " << stateFile << ", " << stateID << ", pObjects, pTextureIDs) >\n";
	return true;
}

void StateParser::parseTextures( TiXmlElement* pParseRoot, std::vector<std::string> *pTextureIDs )
{
	for( TiXmlElement * e = pParseRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement() )
	{
		std::string filenameAttribute = e->Attribute( "filename" );
		std::string idAttribute = e->Attribute( "ID" );
		pTextureIDs->push_back(idAttribute);	//push id into list

		TextureManager::Instance()->load( filenameAttribute, idAttribute, Game::Instance()->getRenderer() );
	}
}

void StateParser::parseObjects( TiXmlElement* pParseRoot, std::vector<GameObject*> *pObjects )
{
	for( TiXmlElement* e = pParseRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement() )
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");

		GameObject* pGameObject = GameObjectFactory::Instance()->create( e->Attribute("type") );
		pGameObject->load( new LoaderParams( x, y, width, height, textureID, numFrames, callbackID, animSpeed ) );
		pObjects->push_back( pGameObject );
	}
}

