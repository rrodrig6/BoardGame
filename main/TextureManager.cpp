#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = NULL;

TextureManager* TextureManager::Instance()
{
	if(!s_pInstance)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}

	return s_pInstance;
}

bool TextureManager::load( std::string fileName, std::string id, SDL_Renderer* pRenderer )
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if( pTempSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError() );
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if( pTexture == NULL )
	{
		printf( "Unable to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
		return false;
	}
	
	m_TextureMap[id] = pTexture;
	return true;
}

void TextureManager::draw( std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = dstRect.w = width;
	srcRect.h = dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx( pRenderer, m_TextureMap[id], &srcRect, &dstRect, 0, 0, flip );
}

void TextureManager::drawFrame( std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = dstRect.w = width;
	srcRect.h = dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;
	
	SDL_RenderCopyEx( pRenderer, m_TextureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap( std::string id )
{
	m_TextureMap.erase( id );
}
