#include <SDL.h>
#include "SDL_image.h"
#include <stdio.h>
#include <stdbool.h>
#include "TextureManager.h"
#include "BlocksManager.h"
#include "SDL_ttf.h"
#include <time.h>

SDL_Texture* loadTexture(const char* filename)
{
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(!tex || !tempSurface)
		printf("Unable to load texture!!!");
	SDL_FreeSurface(tempSurface);
	return tex;
}

void loadBlocksTextures()
{
	blockTextures[0].blockTexture = loadTexture("assets/IBlock.bmp");
	blockTextures[1].blockTexture = loadTexture("assets/JBlock.bmp");
	blockTextures[2].blockTexture = loadTexture("assets/LBlock.bmp");
	blockTextures[3].blockTexture = loadTexture("assets/OBlock.bmp");
	blockTextures[4].blockTexture = loadTexture("assets/SBlock.bmp");
	blockTextures[6].blockTexture = loadTexture("assets/TBlock.bmp");
	blockTextures[5].blockTexture = loadTexture("assets/ZBlock.bmp");
}


Text createText(TTF_Font* GameFont, const char* text, int x, int y)
{
	Text textTexture;
	textTexture.position.x = x;
	textTexture.position.y = y;
	SDL_Color color;
	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	SDL_Surface* surf = TTF_RenderText_Blended(GameFont, text, color);
	textTexture.textTexture = SDL_CreateTextureFromSurface(renderer, surf);
	if (!surf || !textTexture.textTexture)
		printf("Unable to load texture!!!");
	SDL_FreeSurface(surf);
	SDL_QueryTexture(textTexture.textTexture, NULL, NULL, &textTexture.position.w, &textTexture.position.h);

	return textTexture;
}