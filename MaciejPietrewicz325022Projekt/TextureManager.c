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

void destroyBlocksTextures()
{
	for (int i = 0; i < 7; i++)
	{
		SDL_DestroyTexture(blockTextures[i].blockTexture);
	}
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





void loadTextsTextures()
{

	GameFont2 = TTF_OpenFont("fonts/Bangers-Regular.ttf", 60);
	AuthorFont = TTF_OpenFont("fonts/Bangers-Regular.ttf", 14);
	GameFont = TTF_OpenFont("fonts/Bangers-Regular.ttf", 35);
	GameName = TTF_OpenFont("fonts/Bangers-Regular.ttf", 50);

	gameTexts[0] = createText(GameFont, "Next Shape", TOP_LEFT_X + 13 * BLOCK_SIZE - 5, TOP_LEFT_Y + 2 * BLOCK_SIZE + BLOCK_SIZE / 2);
	gameTexts[1] = createText(AuthorFont, "Created by Maciej Pietrewicz", 10, 700);
	gameTexts[2] = createText(GameName, "Tetris", TOP_LEFT_X + 3 * BLOCK_SIZE, TOP_LEFT_Y - 2 * BLOCK_SIZE);
	gameTexts[3] = createText(GameFont, "Score", TOP_LEFT_X + 14 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE + BLOCK_SIZE / 2);
	gameTexts[4] = createText(GameName, "Level", TOP_LEFT_X - 5 * BLOCK_SIZE, TOP_LEFT_Y + 5 * BLOCK_SIZE);
	gameTexts[5] = createText(GameFont, "0", TOP_LEFT_X + 15 * BLOCK_SIZE - 5, TOP_LEFT_Y + 12 * BLOCK_SIZE + BLOCK_SIZE / 2 - 10);
	gameTexts[6] = createText(GameName, "1", TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 7 * BLOCK_SIZE - 10);

	menuTexts[0] = createText(AuthorFont, "Created by Maciej Pietrewicz", 10, 700);
	menuTexts[1] = createText(GameFont2, "Tetris", TOP_LEFT_X + 2 * BLOCK_SIZE, TOP_LEFT_Y + 2*BLOCK_SIZE);
	menuTexts[2] = createText(GameFont2, "Press S to start", TOP_LEFT_X - 2 * BLOCK_SIZE, TOP_LEFT_Y + 6 * BLOCK_SIZE);
	menuTexts[3] = createText(GameFont2, "The Highest Score :", TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE);
}

void destroyTextsTextures()
{
	for (int i = 0; i < 7; i++)
	{
		SDL_DestroyTexture(gameTexts[i].textTexture);
	}
	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(menuTexts[i].textTexture);
	}
}

