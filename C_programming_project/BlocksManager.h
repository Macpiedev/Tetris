#ifndef BLOCKSMANAGER_FUNCS
#define BLOCKSMANAGER_FUNCS
#include "Game.h"

typedef struct Block
{
	SDL_Texture* blockTexture;
	SDL_Rect cordinates[4];
	int whichTexture;
	int fallSpeed;
	int state;
}Block;

Block blockTextures[7];

void showBlocks();
void moveAllBlocksLeft(Block* block);
void moveAllBlocksRight(Block* block);
#endif BLOCKSMANAGER_FUNCS