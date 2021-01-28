#ifndef TEXTURES_FUNCS
#define TEXTURES_FUNCS
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include "Game.h"


typedef struct Text
{
	SDL_Texture* textTexture;
	SDL_Rect position;
}Text;


SDL_Texture* loadTexture(const char* filename);
void loadBlocksTextures();
void loadTextsTextures();
void destroyTextsTextures();
void destroyBlocksTextures();
Text createText(TTF_Font* GameFont, const char* text, int x, int y);
Text gameTexts[7];
Text menuTexts[5];
TTF_Font *GameFont, *AuthorFont, *GameName, *GameFont2;
#endif TEXTURES_FUNCS


