#ifndef TEXTURES_FUNCS
#define TEXTURES_FUNCS
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include "Game.h"

SDL_Texture* loadTexture(const char* filename);
void loadBlocksTextures();
Text createText(TTF_Font* GameFont, const char* text, int x, int y);

#endif TEXTURES_FUNCS


