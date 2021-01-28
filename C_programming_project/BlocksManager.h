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
void RotateBlock(Block* block);
void spawnBlock(Block* block, int shape, int level);
int createShape(Block* block, char shape[], bool isRotate);
void chooseShape(Block* block, int Texture);
void setBlockSize(Block* block);
void putBlockIntoGrid(Block* block);
void moveBlock(Block* block);
#endif BLOCKSMANAGER_FUNCS