#include "BlocksManager.h"
#include "Game.h"


char S2[] = ".......00..0x...........";
char S1[] = ".......0....x0....0......";

char I1[] = ".......0....x....0....0..";
char I2[] = "..........00x0..........";
char I3[] = "...........0x00.........";

char Z1[] = "...........0x....00......";

char Z2[] = ".......0...0x...0........";

char O[] = "............x0...00......";

char J1[] = ".......0....x...00.......";
char J2[] = "...........0x0....0......";
char J3[] = ".......00...x....0.......";
char J4[] = "......0....0x0...........";

char L1[] = ".......0....x....00......";
char L2[] = "........0..0x0...........";
char L3[] = "......00....x....0.......";
char L4[] = "...........0x0..0........";

char T1[] = "...........0x0...0.......";
char T2[] = ".......0....x0...0.......";
char T3[] = ".......0...0x0...........";
char T4[] = ".......0...0x....0.......";


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

