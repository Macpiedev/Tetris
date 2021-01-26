#include "BlocksManager.h"
#include "Game.h"




void Fall(Block* block)
{
	for (int i = 0; i < 4; i++)
	{
		block->cordinates[i].y += BLOCK_SIZE;
	}
}

void showBlocks()
{
	SDL_Rect cordinates;
	cordinates.h = BLOCK_SIZE;
	cordinates.w = BLOCK_SIZE;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid[i][j] != -1)
			{
				cordinates.x = TOP_LEFT_X + j * BLOCK_SIZE;
				cordinates.y = TOP_LEFT_Y + i * BLOCK_SIZE;
				SDL_RenderCopy(renderer, blockTextures[grid[i][j]].blockTexture, NULL, &cordinates);
			}
		}
	}
}

void moveAllBlocksLeft(Block* block)
{
	for (int i = 0; i < 4; i++)
	{
		block->cordinates[i].x -= BLOCK_SIZE;
	}

}

void moveAllBlocksRight(Block* block)
{
	for (int i = 0; i < 4; i++)
	{
		block->cordinates[i].x += BLOCK_SIZE;
	}

}

