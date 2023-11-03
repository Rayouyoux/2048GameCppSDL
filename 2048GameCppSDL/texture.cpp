#include "texture.h"

#include <iostream>

Textures::Textures(Window* oWindow) {
	m_oWindow = oWindow;
}

SDL_Texture* Textures::image(const char* cPath) {
	if (m_msdlTextures.count(cPath)) {
		return m_msdlTextures[cPath];
	}
	else {
		SDL_Surface* sdlSurface = SDL_LoadBMP(cPath);
		if (sdlSurface == NULL)
		{
			std::cout << "Error SDL_LoadBMP :" << SDL_GetError();
			m_oWindow->close();
		}
		SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(m_oWindow->m_sdlRenderer, sdlSurface);
		if (sdlTexture == NULL)
		{
			std::cout << "Error SDL_CreateTextureFromSurface :" << SDL_GetError();
			m_oWindow->close();
		}
		SDL_FreeSurface(sdlSurface);
		m_msdlTextures.insert(std::pair<std::string, SDL_Texture*>(cPath, sdlTexture));
		return sdlTexture;
	}
}

SDL_Texture* Textures::text(const char* cPath, const char* cMessage, SDL_Color sdlColor) {
	if (m_msdlTextures.count(cMessage)) {
		return m_msdlTextures[cMessage];
	}
	else {
		TTF_Font* font = TTF_OpenFont(cPath, 512);
		SDL_Surface* sdlSurface = TTF_RenderUTF8_Solid(font, cMessage, sdlColor);
		if (sdlSurface == NULL)
		{
			std::cout << "Error TTF_RenderUTF8_Solid :" << SDL_GetError();
			m_oWindow->close();
		}
		SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(m_oWindow->m_sdlRenderer, sdlSurface);
		if (sdlTexture == NULL)
		{
			std::cout << "Error SDL_CreateTextureFromSurface :" << SDL_GetError();
			m_oWindow->close();
		}
		SDL_FreeSurface(sdlSurface);
		m_msdlTextures.insert(std::pair<std::string, SDL_Texture*>(cMessage, sdlTexture));
		return sdlTexture;
	}
}


Textures::~Textures() {
	for (std::map<std::string, SDL_Texture*>::iterator i = m_msdlTextures.begin(); i != m_msdlTextures.end(); ++i) {
		SDL_DestroyTexture(i->second);
	}
	m_msdlTextures.clear();
}