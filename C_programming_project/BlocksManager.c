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





int createShape(Block* block, char shape[], bool isRotate)
{
	int newCordinatesX[3];
	int newCordinatesY[3];
	bool isPossible = true;
	int startx = cordinatesToGridX(block->cordinates[0].x - (2 * BLOCK_SIZE));
	int starty = cordinatesToGridY(block->cordinates[0].y - (2 * BLOCK_SIZE));
	int chooseBlock = 1;
	int pos = 0;
	int m = 0;
	for (int i = starty; i < starty + 5; i++)
	{
		for (int j = startx; j < startx + 5; j++)
		{
			pos = j - startx + 5 * (i - starty);
			if (shape[pos] == '0')
			{
				if (!emptySpace(j, i))
				{
					if (isRotate) {
						isPossible = false;
						break;
					}
				}
				newCordinatesX[m] = gridXtoCordinates(j);
				newCordinatesY[m] = gridYtoCordinates(i);
				m += 1;
			}
		}
		if (isPossible == false)
			break;
	}
	if (isPossible) {
		for (m = 0; m < 3; m++)
		{
			if (newCordinatesX && newCordinatesY) {
				block->cordinates[m + 1].x = newCordinatesX[m];
				block->cordinates[m + 1].y = newCordinatesY[m];
			}
		}
		return 1;
	}
	else
		return 0;

}



void putBlockIntoGrid(Block* block)
{

	for (int m = 0; m < 4; m++) {
		grid[cordinatesToGridY(block->cordinates[m].y)][cordinatesToGridX(block->cordinates[m].x)] = block->whichTexture;
	}

}

void destroyBlocksTextures()
{
	for (int i = 0; i < 7; i++)
	{
		SDL_DestroyTexture(blockTextures[i].blockTexture);
	}
}



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

void RotateBlock(Block* block)
{
	switch (block->whichTexture)
	{
	case 0:
		if ((block->state == 0))
		{
			if (createShape(block, I2, true))
				block->state = 1;

		}
		else if (block->state == 0)
		{
			if (createShape(block, I3, true))
				block->state = 1;
		}
		else if (block->state == 1)
		{

			if (createShape(block, I1, true))
				block->state = 0;
		}
		break;
	case 1:
		if (block->state == 0)
		{

			if (createShape(block, J2, true))
				block->state = 1;

		}
		else if (block->state == 1)
		{

			if (createShape(block, J3, true))
				block->state = 2;

		}
		else if (block->state == 2)
		{

			if (createShape(block, J4, true))
				block->state = 3;

		}
		else if (block->state == 3)
		{

			if (createShape(block, J1, true))
				block->state = 0;

		}
		break;
	case 2:
		if (block->state == 0)
		{

			if (createShape(block, L2, true))
				block->state = 1;

		}
		else if (block->state == 1)
		{

			if (createShape(block, L3, true))
				block->state = 2;

		}
		else if (block->state == 2)
		{

			if (createShape(block, L4, true))
				block->state = 3;

		}
		else if (block->state == 3)
		{

			if (createShape(block, L1, true))
				block->state = 0;

		}
		break;
	case 5:
		if (block->state == 0)
		{
			if (createShape(block, S1, true))
				block->state = 1;
		}
		else if (cordinatesToGridX(block->cordinates[0].x) != 0) {
			if (createShape(block, S2, true))
				block->state = 0;
		}
		break;
	case 4:
		if (block->state == 0)
		{
			if (createShape(block, Z2, true))
				block->state = 1;
		}
		else if (block->state == 1) {
			if (createShape(block, Z1, true))
				block->state = 0;
		}

		break;
	case 6:
		if (block->state == 0)
		{
			if (createShape(block, T2, true))
				block->state = 1;
		}
		else if (block->state == 1) {
			if (createShape(block, T3, true))
				block->state = 2;
		}
		else if (block->state == 2) {
			if (createShape(block, T4, true))
				block->state = 3;
		}
		else if (block->state == 3) {
			if (createShape(block, T1, true))
				block->state = 0;
		}
		break;
	}
}
void chooseShape(Block* block, int Texture)
{
	switch (Texture)
	{
	case 0:
		createShape(block, I1, false);

		break;
	case 1:
		createShape(block, J1, false);
		break;
	case 2:
		createShape(block, L1, false);
		break;
	case 3:
		createShape(block, O, false);
		break;
	case 4:
		createShape(block, Z1, false);

		break;
	case 5:
		createShape(block, S2, false);
		break;
	case 6:
		createShape(block, T1, false);

		break;
	}
}

void setBlockSize(Block* block)
{
	for (int i = 0; i < 4; i++)
	{
		block->cordinates[i].h = BLOCK_SIZE;
		block->cordinates[i].w = BLOCK_SIZE;
	}
}


void spawnBlock(Block* block, int shape, int level)
{

	block->blockTexture = blockTextures[shape].blockTexture;
	block->cordinates[0].x = TOP_LEFT_X + BLOCK_SIZE * 5;
	switch (shape)
	{
	case 0:
		block->cordinates[0].y = TOP_LEFT_Y - 2 * BLOCK_SIZE;
		break;
	case 1:
		block->cordinates[0].y = TOP_LEFT_Y - 2 * BLOCK_SIZE;
		break;
	case 2:
		block->cordinates[0].y = TOP_LEFT_Y - 2 * BLOCK_SIZE;
		break;
	case 3:
		block->cordinates[0].y = TOP_LEFT_Y - 2 * BLOCK_SIZE;
		break;
	default:
		block->cordinates[0].y = TOP_LEFT_Y - BLOCK_SIZE;
		break;
	}

	block->whichTexture = shape;

	block->fallSpeed = (level - 1) * 4;
	block->state = 0;
	setBlockSize(block);

	chooseShape(block, shape);

}
