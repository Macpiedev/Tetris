
#include "Game.h"
#include "BlocksManager.h"
#include "TextureManager.h"

void initWindow()
{
	TTF_Init();

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0);

	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				isRunning = true;
			}
			else {
				isRunning = false;
				printf("Unable to intialize renderer!!!");
			}
		}
		else {
			printf("Unable to intialize window!!!");
		}
	}
}

bool emptySpace(int x, int y)
{
	if (y < 0)
		return true;
	if (y > 19)
		return false;
	if (x < 0)
		return false;
	if (x > 9)
		return false;
	if (grid[y][x] == -1)
		return true;

	return false;
}



void initGrid()
{
	for (int i = 0; i < ROWS; i++)
	{
		for(int j=0;j<COLUMNS;j++)
		{
			grid[i][j] = -1;
		}
	}
}


void drawGrid()
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	for (int i = 0; i <= PLAY_HEIGHT; i+=BLOCK_SIZE)
	{
		SDL_RenderDrawLine(renderer, TOP_LEFT_X, TOP_LEFT_Y + i, PLAY_WIDTH + TOP_LEFT_X, TOP_LEFT_Y + i);
	}
	for (int j = 0; j <= PLAY_WIDTH; j += BLOCK_SIZE)
	{
		SDL_RenderDrawLine(renderer, TOP_LEFT_X + j, TOP_LEFT_Y, TOP_LEFT_X + j, TOP_LEFT_Y + PLAY_HEIGHT);
	}
	SDL_SetRenderDrawColor(renderer, 200,200,200, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, TOP_LEFT_X, TOP_LEFT_Y, TOP_LEFT_X, TOP_LEFT_Y + PLAY_HEIGHT);
	SDL_RenderDrawLine(renderer, TOP_LEFT_X+ PLAY_WIDTH, TOP_LEFT_Y, TOP_LEFT_X + PLAY_WIDTH, TOP_LEFT_Y + PLAY_HEIGHT);
	SDL_RenderDrawLine(renderer, TOP_LEFT_X, TOP_LEFT_Y , PLAY_WIDTH + TOP_LEFT_X, TOP_LEFT_Y );
	SDL_RenderDrawLine(renderer, TOP_LEFT_X, TOP_LEFT_Y + PLAY_HEIGHT, PLAY_WIDTH + TOP_LEFT_X, TOP_LEFT_Y + PLAY_HEIGHT);
}


int cordinatesToGridX(int x)
{
	return (x - TOP_LEFT_X) / BLOCK_SIZE;
}
int cordinatesToGridY(int y)
{
	return (y - TOP_LEFT_Y) / BLOCK_SIZE;
}

int gridXtoCordinates(int x)
{
	return TOP_LEFT_X + BLOCK_SIZE * x;
}
int gridYtoCordinates(int y)
{
	return TOP_LEFT_Y + BLOCK_SIZE * y;
}



bool checkIfLost()
{
	for (int i = 0; i < COLUMNS; i++)
	{
		if (grid[0][i] != -1)
			return false;
	}
	return true;
}



bool checkFreeSpaces(int number, Block *block, int m, int t)
{


	switch (number)
	{
	case 3:
			if (emptySpace(cordinatesToGridX(block->cordinates[2].x) + m, (cordinatesToGridY(block->cordinates[2].y) + t)))
				return 1;
			else
				return 0;
			break;
	case 4:
		if (emptySpace(cordinatesToGridX(block->cordinates[3].x) + m, (cordinatesToGridY(block->cordinates[3].y) + t)))
			return 1;
		else
			return 0;
		break;
	case 1:
		if (emptySpace(cordinatesToGridX(block->cordinates[0].x) + m, (cordinatesToGridY(block->cordinates[0].y) + t)))
			return 1;
		else
			return 0;
		break;
	case 2:
		if (emptySpace(cordinatesToGridX(block->cordinates[1].x) + m, (cordinatesToGridY(block->cordinates[1].y) + t)))
			return 1;
		else
			return 0;
		break;
	}
}



void handleEvents(Block *block, int BlockSpeed, int level, int *rotateDelay)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_LEFT && block->cordinates[0].x > TOP_LEFT_X  && block->cordinates[1].x > TOP_LEFT_X  && block->cordinates[2].x > TOP_LEFT_X && block->cordinates[3].x > TOP_LEFT_X)
			{
	
			if (checkFreeSpaces(1, block, -1, 0) && checkFreeSpaces(2, block, -1, 0) && checkFreeSpaces(3, block, -1, 0) && checkFreeSpaces(4, block, -1, 0))
					moveAllBlocksLeft(block);
	
			}
			 else if (e.key.keysym.sym == SDLK_RIGHT && block->cordinates[3].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE && block->cordinates[2].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE && block->cordinates[1].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE && block->cordinates[0].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE)
			{
				
				if (checkFreeSpaces(1, block, 1, 0) && checkFreeSpaces(2, block, 1, 0) && checkFreeSpaces(3, block, 1, 0) && checkFreeSpaces(4, block, 1, 0))
					moveAllBlocksRight(block);

			
			}
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				block->fallSpeed = BlockSpeed - 2;
			}
			 if (e.key.keysym.sym == SDLK_UP && rotateDelay[0] >8)
			{
				 rotateDelay[0] = 0;
				RotateBlock(block);
			}
		}
		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				block->fallSpeed = (level - 1) * 5;
			}
		}
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			isRunning = false;
	}
}


void rendererFuncs(Block* currentBlock, int nextShape, int score)
{

	Block* nextBlockTooltip = malloc(sizeof(Block));
	if (nextBlockTooltip) {
		nextBlockTooltip->blockTexture = blockTextures[nextShape].blockTexture;
		nextBlockTooltip->whichTexture = nextShape;
		setBlockSize(nextBlockTooltip);
		nextBlockTooltip->cordinates[0].x = TOP_LEFT_X + 14 * BLOCK_SIZE;
		nextBlockTooltip->cordinates[0].y = TOP_LEFT_Y + 5 * BLOCK_SIZE;
	}

	chooseShape(nextBlockTooltip, nextShape);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	drawGrid();
	
	for (int i = 0; i < 4; i++) {
		if (currentBlock->cordinates[i].y >= TOP_LEFT_Y)
			SDL_RenderCopy(renderer, currentBlock->blockTexture, NULL, &currentBlock->cordinates[i]);
		if (nextBlockTooltip)
		SDL_RenderCopy(renderer, nextBlockTooltip->blockTexture, NULL, &nextBlockTooltip->cordinates[i]);
	}

	for (int i = 0; i < 7; i++)
	{
		SDL_RenderCopy(renderer, gameTexts[i].textTexture, NULL, &gameTexts[i].position);
	}

	showBlocks();
	SDL_RenderPresent(renderer);
	free(nextBlockTooltip);
}



void clearAndUpdateGrid(int y)
{
	for (int i = y; i > 0; i--)
	{
		if (i <= y) {
			for (int j = 0; j < COLUMNS; j++)
			{	
				grid[i][j] = grid[i - 1][j];
				
			}
		}
	}
}

int getPoints(int Level, Block *block, int score) {
	int min = cordinatesToGridY(block->cordinates[0].y);
	int max = cordinatesToGridY(block->cordinates[0].y);
	bool points = true;
	int quantity = 0;
	int bonusPoints = 0;
	for (int i = 0; i < 4; i++)
	{
		if (cordinatesToGridY(block->cordinates[i].y) < min)
			min = cordinatesToGridY(block->cordinates[i].y);
		if (cordinatesToGridY(block->cordinates[i].y) > max)
			max = cordinatesToGridY(block->cordinates[i].y);
	}

	for (int y = min; y < min + (max - min + 1); y++)
	{
		for (int x = 0; x < COLUMNS; x++)
		{
			if (grid[y][x] == -1) {
					points = false;
					break;
			}
		}
		if (points == true)
		{
			quantity++;
			clearAndUpdateGrid(y);
		}
		points = true;
	}
	switch(quantity)
	{
		case 2:
			bonusPoints = 5;
			break;
		case 3:
			bonusPoints = 15;
			break;
		case 4:
			bonusPoints = 25;
			break;
		default:
			bonusPoints = 0;
			break;
	}
	score += 10 * Level * quantity + bonusPoints * Level;
	return score;
	
}

int levelUp(int score)
{
	if (score >= 0 && score <=80)
		return 1;
	else if (score > 80 && score <=200)
		return 2;
	else if (score > 200 && score <600)
		return 3;
	else if (score > 600 && score <=1200)
		return 4;
	else if (score > 1200 )
		return 5;
	
}


void exitGame()
{
	TTF_CloseFont(GameFont);
	TTF_CloseFont(AuthorFont);
	TTF_CloseFont(GameFont2);
	TTF_CloseFont(GameName);
	destroyTextsTextures();
	destroyBlocksTextures();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

}
int startGame(const int frameDelay)
{
	srand(time(NULL));

	isRunning = 1;

	int whenMove = 0;
	unsigned int score = 0, newscore = 0, BlockSpeed = FPS / 2, Level = 1; 

	Uint32 frameStart;
	int frameTime;

	initGrid();

	bool IscurrentBlock = true;
	int nextShape = rand() % 7;
	Block *currentBlock = malloc(sizeof(Block));
	unsigned int* rotateDelay = malloc(sizeof(int));
	rotateDelay[0] = 0;
	spawnBlock(currentBlock, nextShape, Level);
	nextShape = rand() % 7;

	char StrScore[100], StrLevel[10];
	while (isRunning)
	{
		frameStart = SDL_GetTicks();
		handleEvents(currentBlock, BlockSpeed, Level, rotateDelay);
		if (IscurrentBlock == false)
		{
			spawnBlock(currentBlock, nextShape, Level);
			IscurrentBlock = true;
			nextShape = rand() % 7;
		}
		if (currentBlock)
			if (whenMove > BlockSpeed - currentBlock->fallSpeed)
				whenMove = BlockSpeed - currentBlock->fallSpeed;
		if (currentBlock)
		if (whenMove == BlockSpeed - currentBlock->fallSpeed)
		{
				if (checkFreeSpaces(1, currentBlock, 0, 1) && checkFreeSpaces(2, currentBlock, 0, 1) && checkFreeSpaces(3, currentBlock, 0, 1) && checkFreeSpaces(4, currentBlock, 0, 1))
				{

					moveBlock(currentBlock);
					whenMove = 0;
				}
				else
				{
					IscurrentBlock = false;
					putBlockIntoGrid(currentBlock);
					if (checkIfLost() == false) {
						isRunning = false;
						continue;
					}
					newscore = getPoints(Level, currentBlock, score);
					if (newscore != score) {
						Level = levelUp(score);
						score = newscore;
						sprintf_s(StrScore, 100, "%d", score);
						sprintf_s(StrLevel, 10, "%d", Level);
						SDL_DestroyTexture(gameTexts[5].textTexture);
						SDL_DestroyTexture(gameTexts[6].textTexture);
						gameTexts[5] = createText(GameFont, StrScore, TOP_LEFT_X + 15 * BLOCK_SIZE - 5, TOP_LEFT_Y + 12 * BLOCK_SIZE + BLOCK_SIZE / 2 - 10);
						gameTexts[6] = createText(GameName, StrLevel, TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 7 * BLOCK_SIZE - 10);
					}
				}
		}
		whenMove++;
		if (currentBlock)
		if (currentBlock->cordinates[0].y == TOP_LEFT_Y+(ROWS-1)*BLOCK_SIZE)
		{
			putBlockIntoGrid(currentBlock);
			IscurrentBlock = false;
			if (checkIfLost() == false){
				isRunning = false;
				continue;
				}
			newscore = getPoints(Level, currentBlock, score);
			if (newscore != score) {
				Level = levelUp(score);
				score = newscore;
				sprintf_s(StrScore, 100, "%d", score);
				sprintf_s(StrLevel, 10, "%d", Level);
				SDL_DestroyTexture(gameTexts[5].textTexture);
				SDL_DestroyTexture(gameTexts[6].textTexture);
				gameTexts[5] = createText(GameFont, StrScore, TOP_LEFT_X + 15 * BLOCK_SIZE - 5, TOP_LEFT_Y + 12 * BLOCK_SIZE + BLOCK_SIZE / 2 - 10);
				gameTexts[6] = createText(GameName, StrLevel, TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 7 * BLOCK_SIZE - 10);
			}
		}
		
	
		rendererFuncs(currentBlock, nextShape, score);
		rotateDelay[0] += 1;
		

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
	free(rotateDelay);
	free(currentBlock);

	return score;
}


void startMenu()
{
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	loadBlocksTextures();
	SDL_Event e;
	unsigned int highestScore=0, score;
	bool quitGame=true;
	loadTextsTextures();
	
	FILE* fptr;
	fopen_s(&fptr,"highestScore.txt", "r");
	if(fptr)
		fscanf_s(fptr, "%d", &highestScore);
	char strHS[100];
	if(fptr)
		fclose(fptr);
	sprintf_s(strHS, 100, "%d", highestScore);
	menuTexts[4] = createText(GameFont2, strHS, TOP_LEFT_X + 10 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE);

	while (quitGame) {
		frameStart = SDL_GetTicks();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		for (int i = 0; i < 5; i++)
		{
			SDL_RenderCopy(renderer, menuTexts[i].textTexture, NULL, &menuTexts[i].position);
		}
			SDL_RenderPresent(renderer);
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN) {
				if ((e.key.keysym.sym == SDLK_s)) {
					score = startGame(frameDelay);
					printf("Previous Game Score: %d\n", score);
					if (score > highestScore) {
						highestScore = score;
						fopen_s(&fptr, "highestScore.txt", "w");
						if (fptr) {
							fprintf_s(fptr, "%d", highestScore);
							fclose(fptr);
						}
						SDL_DestroyTexture(menuTexts[4].textTexture);
						sprintf_s(strHS, 100, "%d", highestScore);
						menuTexts[4] = createText(GameFont2, strHS, TOP_LEFT_X + 10 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE);
					}
				}
			}
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				quitGame = false;
				if(fptr)
					fclose(fptr);		
			}
		}
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

}
