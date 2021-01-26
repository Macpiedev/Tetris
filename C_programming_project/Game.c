
#include "Game.h"
#include "BlocksManager.h"

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
			else
				isRunning = false;
		}
	}
}

bool FreeSpace(int x, int y)
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





SDL_Texture* LoadTexture(const char* filename)
{
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}


void init_grid()
{
	for (int i = 0; i < ROWS; i++)
	{
		for(int j=0;j<COLUMNS;j++)
		{
			grid[i][j] = -1;
		}
	}
}


void draw_grid()
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


int CordinatesToGridX(int x)
{
	return (x - TOP_LEFT_X) / BLOCK_SIZE;
}
int CordinatesToGridY(int y)
{
	return (y - TOP_LEFT_Y) / BLOCK_SIZE;
}

int GridXtoCordinates(int x)
{
	return TOP_LEFT_X + BLOCK_SIZE * x;
}
int GridYtoCordinates(int y)
{
	return TOP_LEFT_Y + BLOCK_SIZE * y;
}




bool check_lost()
{
	for (int i = 0; i < COLUMNS; i++)
	{
		if (grid[0][i] != -1)
			return false;
	}
	return true;
}


bool FreeSpaceWhich(int number, Block *block, int m, int t)
{


	switch (number)
	{
	case 3:
			if (FreeSpace(CordinatesToGridX(block->cordinates[2].x) + m, (CordinatesToGridY(block->cordinates[2].y) + t)))
				return 1;
			else
				return 0;
			break;
	case 4:
		if (FreeSpace(CordinatesToGridX(block->cordinates[3].x) + m, (CordinatesToGridY(block->cordinates[3].y) + t)))
			return 1;
		else
			return 0;
		break;
	case 1:
		if (FreeSpace(CordinatesToGridX(block->cordinates[0].x) + m, (CordinatesToGridY(block->cordinates[0].y) + t)))
			return 1;
		else
			return 0;
		break;
	case 2:
		if (FreeSpace(CordinatesToGridX(block->cordinates[1].x) + m, (CordinatesToGridY(block->cordinates[1].y) + t)))
			return 1;
		else
			return 0;
		break;
	}
}

int createShape(Block* block, char shape[], bool isRotate)
{
	int newCordinatesX[3];
	int newCordinatesY[3];
	bool isPossible = true;
	int startx = CordinatesToGridX(block->cordinates[0].x - (2 * BLOCK_SIZE));
	int starty = CordinatesToGridY(block->cordinates[0].y - (2 * BLOCK_SIZE));
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
				if (!FreeSpace(j, i))
				{
					if (isRotate) {
						isPossible = false;
						break;
					}
				}
				newCordinatesX[m] = GridXtoCordinates(j);
				newCordinatesY[m] = GridYtoCordinates(i);
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

void rotateBlock(Block* block)
{
	switch (block->whichTexture)
	{
	case 0:
		if ((block->state == 0))
		{
			if(createShape(block, I2, true))
				block->state = 1;

		}
		else if (block->state == 0)
		{
			if(createShape(block, I3, true))
				block->state = 1;
		}
		else if (block->state == 1)
		{

			if(createShape(block, I1, true))
				block->state = 0;
		}
		break;
	case 1:
		if (block->state == 0)
		{

			if(createShape(block, J2, true))
				block->state = 1;

		}
		else if (block->state == 1)
		{

			if(createShape(block, J3, true))
				block->state = 2;

		}
		else if (block->state == 2 )
		{

			if(createShape(block, J4, true))
				block->state = 3;

		}
		else if (block->state == 3)
		{

			if(createShape(block, J1, true))
				block->state = 0;

		}
		break;
	case 2:
		if (block->state == 0)
		{

			if(createShape(block, L2, true))
				block->state = 1;

		}
		else if (block->state == 1)
		{

			if(createShape(block, L3, true))
				block->state = 2;

		}
		else if (block->state == 2)
		{

			if(createShape(block, L4, true))
				block->state = 3;

		}
		else if (block->state == 3)
		{

			if(createShape(block, L1, true))
				block->state = 0;

		}
		break;
	case 5:
		if (block->state == 0)
		{
			if(createShape(block, S1, true))
				block->state = 1;
		}
		else if (CordinatesToGridX(block->cordinates[0].x) != 0) {
			if(createShape(block, S2, true))
				block->state = 0;
		}
		break;
	case 4:
		if (block->state == 0)
		{
			if(createShape(block, Z2, true))
				block->state = 1;
		}
		else if (block->state == 1 ) {
			if(createShape(block, Z1, true))
				block->state = 0;
		}

		break;
	case 6:
		if (block->state == 0)
		{
			if(createShape(block, T2, true))
				block->state = 1;
		}
		else if (block->state == 1 ) {
			if(createShape(block, T3, true))
				block->state = 2;
		}
		else if (block->state == 2) {
			if(createShape(block, T4, true))
				block->state = 3;
		}
		else if (block->state == 3 ) {
			if(createShape(block, T1, true))
				block->state = 0;
		}
		break;
	}
}





void Events(Block *block, int BlockSpeed, int level)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_LEFT && block->cordinates[0].x > TOP_LEFT_X  && block->cordinates[1].x > TOP_LEFT_X  && block->cordinates[2].x > TOP_LEFT_X && block->cordinates[3].x > TOP_LEFT_X)
			{
	
			if (FreeSpaceWhich(1, block, -1, 0) && FreeSpaceWhich(2, block, -1, 0) && FreeSpaceWhich(3, block, -1, 0) && FreeSpaceWhich(4, block, -1, 0))
					moveAllBlocksLeft(block);
	
			}
			 else if (e.key.keysym.sym == SDLK_RIGHT && block->cordinates[3].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE && block->cordinates[2].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE && block->cordinates[1].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE && block->cordinates[0].x < TOP_LEFT_X + (COLUMNS - 1) * BLOCK_SIZE)
			{
				
				if (FreeSpaceWhich(1, block, 1, 0) && FreeSpaceWhich(2, block, 1, 0) && FreeSpaceWhich(3, block, 1, 0) && FreeSpaceWhich(4, block, 1, 0))
					moveAllBlocksRight(block);

			
			}
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				block->fallSpeed = BlockSpeed - 2;
			}
			 if (e.key.keysym.sym == SDLK_UP)
			{
				rotateBlock(block);
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



void PutBlockIntoGrid(Block* block)
{

for (int m = 0; m < 4; m++) {
	grid[CordinatesToGridY(block->cordinates[m].y)][CordinatesToGridX(block->cordinates[m].x)] = block->whichTexture;
}

}

void LoadBlocksTextures()
{
	blockTextures[0].blockTexture = LoadTexture("assets/IBlock.bmp");
	blockTextures[1].blockTexture = LoadTexture("assets/JBlock.bmp");
	blockTextures[2].blockTexture = LoadTexture("assets/LBlock.bmp");
	blockTextures[3].blockTexture = LoadTexture("assets/OBlock.bmp");
	blockTextures[4].blockTexture = LoadTexture("assets/SBlock.bmp");
	blockTextures[6].blockTexture = LoadTexture("assets/TBlock.bmp");
	blockTextures[5].blockTexture = LoadTexture("assets/ZBlock.bmp");
}

void DestroyBlocksTextures()
{
	for (int i = 0; i < 7; i++)
	{
		SDL_DestroyTexture(blockTextures[i].blockTexture);
	}
}



void choosedShape(Block* block, int Texture)
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
	block->cordinates[0].x = TOP_LEFT_X + BLOCK_SIZE *5;
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

	choosedShape(block, shape);

}



Text createText(TTF_Font* GameFont, char* text, int x, int y)
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
	SDL_FreeSurface(surf);
	SDL_QueryTexture(textTexture.textTexture, NULL, NULL, &textTexture.position.w, &textTexture.position.h);

	return textTexture;
}

void renderer_funcs_game(Block* currentBlock, int nextShape, int score, Text nextShapeText, Text Tetris, Text Author, Text ScoreText, Text ScorePoints, Text LevelText, Text  LevelNumberText)
{

	Block* nextBlockTooltip = malloc(sizeof(Block));
	if (nextBlockTooltip) {
		nextBlockTooltip->blockTexture = blockTextures[nextShape].blockTexture;
		nextBlockTooltip->whichTexture = nextShape;
		setBlockSize(nextBlockTooltip);
		nextBlockTooltip->cordinates[0].x = TOP_LEFT_X + 14 * BLOCK_SIZE;
		nextBlockTooltip->cordinates[0].y = TOP_LEFT_Y + 5 * BLOCK_SIZE;
	}

	choosedShape(nextBlockTooltip, nextShape);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	draw_grid();
	
	for (int i = 0; i < 4; i++) {
		if (currentBlock->cordinates[i].y >= TOP_LEFT_Y)
			SDL_RenderCopy(renderer, currentBlock->blockTexture, NULL, &currentBlock->cordinates[i]);
		if (nextBlockTooltip)
		SDL_RenderCopy(renderer, nextBlockTooltip->blockTexture, NULL, &nextBlockTooltip->cordinates[i]);
	}
	SDL_RenderCopy(renderer, nextShapeText.textTexture, NULL, &nextShapeText.position);
	SDL_RenderCopy(renderer, Tetris.textTexture, NULL, &Tetris.position);
	SDL_RenderCopy(renderer, Author.textTexture, NULL, &Author.position);
	SDL_RenderCopy(renderer, ScoreText.textTexture, NULL, &ScoreText.position);
	SDL_RenderCopy(renderer, ScorePoints.textTexture, NULL, &ScorePoints.position);
	SDL_RenderCopy(renderer, LevelText.textTexture, NULL, &LevelText.position);
	SDL_RenderCopy(renderer, LevelNumberText.textTexture, NULL, &LevelNumberText.position);
	showBlocks();
	SDL_RenderPresent(renderer);
	free(nextBlockTooltip);
}



void ClearAndUpdateGrid(int y)
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
	int min = CordinatesToGridY(block->cordinates[0].y);
	int max = CordinatesToGridY(block->cordinates[0].y);
	bool points = true;
	int quantity = 0;
	int bonusPoints = 0;
	for (int i = 0; i < 4; i++)
	{
		if (CordinatesToGridY(block->cordinates[i].y) < min)
			min = CordinatesToGridY(block->cordinates[i].y);
		if (CordinatesToGridY(block->cordinates[i].y) > max)
			max = CordinatesToGridY(block->cordinates[i].y);
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
			ClearAndUpdateGrid(y);
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

int LevelUp(int score)
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
	DestroyBlocksTextures();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

}
int startGame(const int frameDelay)
{

	int score = 0, newscore = 0;
	isRunning = 1;
	srand(time(NULL));

	int BlockSpeed = FPS/2;
	int Level = 1;
	int whenMove = 0;
	Uint32 frameStart;
	int frameTime;
	init_grid();
	
	bool IscurrentBlock = true;
	int nextShape = rand() % 7;
	Block *currentBlock = malloc(sizeof(Block));
	spawnBlock(currentBlock, nextShape, Level);
	nextShape = rand() % 7;

	TTF_Font* GameFont, * AuthorFont, * GameName;
	GameFont = TTF_OpenFont("fonts/Bangers-Regular.ttf", 35);
	AuthorFont = TTF_OpenFont("fonts/Bangers-Regular.ttf", 14);
	GameName = TTF_OpenFont("fonts/Bangers-Regular.ttf", 50);

	Text nextShapeText, Author, Tetris, ScoreText, ScorePoints, LevelText, LevelNumberText;
	nextShapeText = createText(GameFont, "Next Shape", TOP_LEFT_X + 13 * BLOCK_SIZE - 5, TOP_LEFT_Y + 2 * BLOCK_SIZE + BLOCK_SIZE / 2);
	Author = createText(AuthorFont, "Created by Maciej Pietrewicz", 10, 700);
	Tetris = createText(GameName, "Tetris", TOP_LEFT_X + 3 * BLOCK_SIZE, TOP_LEFT_Y - 2 * BLOCK_SIZE);

	ScoreText = createText(GameFont, "Score", TOP_LEFT_X + 14 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE + BLOCK_SIZE / 2);

	LevelText = createText(GameName, "Level", TOP_LEFT_X - 5 * BLOCK_SIZE, TOP_LEFT_Y + 5 * BLOCK_SIZE);
	ScorePoints = createText(GameFont, "0", TOP_LEFT_X + 15 * BLOCK_SIZE - 5, TOP_LEFT_Y + 12 * BLOCK_SIZE + BLOCK_SIZE / 2 - 10);
	LevelNumberText = createText(GameName, "1", TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 7 * BLOCK_SIZE - 10);
	char StrScore[100], StrLevel[10];
	while (isRunning)
	{
		
		
		frameStart = SDL_GetTicks();
		Events(currentBlock, BlockSpeed, Level);
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

				if (FreeSpaceWhich(1, currentBlock, 0, 1) && FreeSpaceWhich(2, currentBlock, 0, 1) && FreeSpaceWhich(3, currentBlock, 0, 1) && FreeSpaceWhich(4, currentBlock, 0, 1))
				{

					Fall(currentBlock);
					whenMove = 0;
				}
				else
				{
					IscurrentBlock = false;
					PutBlockIntoGrid(currentBlock);
					if (check_lost() == false) {
						isRunning = false;
						continue;
					}
					newscore = getPoints(Level, currentBlock, score);
					if (newscore != score) {
						Level = LevelUp(score);
						score = newscore;
						sprintf_s(StrScore, 100, "%d", score);
						sprintf_s(StrLevel, 10, "%d", Level);
						SDL_DestroyTexture(ScorePoints.textTexture);
						SDL_DestroyTexture(LevelNumberText.textTexture);
						ScorePoints = createText(GameFont, StrScore, TOP_LEFT_X + 15 * BLOCK_SIZE - 5, TOP_LEFT_Y + 12 * BLOCK_SIZE + BLOCK_SIZE / 2 - 10);
						LevelNumberText = createText(GameName, StrLevel, TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 7 * BLOCK_SIZE - 10);
					}
				}
		}
		whenMove++;
		if (currentBlock)
		if (currentBlock->cordinates[0].y == TOP_LEFT_Y+(ROWS-1)*BLOCK_SIZE)
		{
			PutBlockIntoGrid(currentBlock);
			IscurrentBlock = false;
			if (check_lost() == false){
				isRunning = false;
				continue;
				}
			newscore = getPoints(Level, currentBlock, score);
			if (newscore != score) {
				Level = LevelUp(score);
				score = newscore;
				sprintf_s(StrScore, 100, "%d", score);
				sprintf_s(StrLevel, 10, "%d", Level);
				SDL_DestroyTexture(ScorePoints.textTexture);
				SDL_DestroyTexture(LevelNumberText.textTexture);
				ScorePoints = createText(GameFont, StrScore, TOP_LEFT_X + 15 * BLOCK_SIZE - 5, TOP_LEFT_Y + 12 * BLOCK_SIZE + BLOCK_SIZE / 2 - 10);
				LevelNumberText = createText(GameName, StrLevel, TOP_LEFT_X - 4 * BLOCK_SIZE, TOP_LEFT_Y + 7 * BLOCK_SIZE - 10);
			}
		}
		
	
		renderer_funcs_game(currentBlock, nextShape, score, nextShapeText, Tetris, Author,ScoreText,ScorePoints, LevelText, LevelNumberText);
		
		

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
	return score;
}


void startMenu()
{
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	LoadBlocksTextures();
	SDL_Event e;
	int highestScore=0, score;
	bool quitGame=true;
	Text HighestScoreText, HighestScoreNumber, Tetris, howToStart, Author;
	TTF_Font* GameFont, *AuthorFont;
	GameFont = TTF_OpenFont("fonts/Bangers-Regular.ttf", 60);
	AuthorFont = TTF_OpenFont("fonts/Bangers-Regular.ttf", 14);
	Author = createText(AuthorFont, "Created by Maciej Pietrewicz", 10, 700);
	Tetris = createText(GameFont, "Tetris", TOP_LEFT_X + 2 * BLOCK_SIZE, TOP_LEFT_Y + BLOCK_SIZE);
	howToStart = createText(GameFont, "Press S to start", TOP_LEFT_X - 2 * BLOCK_SIZE, TOP_LEFT_Y + 6*BLOCK_SIZE);
	HighestScoreText = createText(GameFont, "Highest score :", TOP_LEFT_X - 3 * BLOCK_SIZE, TOP_LEFT_Y +10 * BLOCK_SIZE);
	
	FILE* fptr;
	fopen_s(&fptr,"highestScore.txt", "r");
	if(fptr)
		fscanf_s(fptr, "%d", &highestScore);
	char strHS[100];
	if(fptr)
		fclose(fptr);
	sprintf_s(strHS, 100, "%d", highestScore);
	HighestScoreNumber = createText(GameFont, strHS, TOP_LEFT_X + 9 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE);
	while (quitGame) {
		frameStart = SDL_GetTicks();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Author.textTexture, NULL, &Author.position);
		SDL_RenderCopy(renderer, Tetris.textTexture, NULL, &Tetris.position);
		SDL_RenderCopy(renderer, howToStart.textTexture, NULL, &howToStart.position);
		SDL_RenderCopy(renderer, HighestScoreText.textTexture, NULL, &HighestScoreText.position);
		SDL_RenderCopy(renderer, HighestScoreNumber.textTexture, NULL, &HighestScoreNumber.position);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN) {
				if ((e.key.keysym.sym == SDLK_s)) {
					score = startGame(frameDelay);
					printf("Last Game Score: %d\n", score);
					if (score > highestScore) {
						highestScore = score;
						fopen_s(&fptr, "highestScore.txt", "w");
						if (fptr) {
							fprintf_s(fptr, "%d", highestScore);
							fclose(fptr);
						}
						SDL_DestroyTexture(HighestScoreNumber.textTexture);
						sprintf_s(strHS, 100, "%d", highestScore);
						HighestScoreNumber = createText(GameFont, strHS, TOP_LEFT_X + 9 * BLOCK_SIZE, TOP_LEFT_Y + 10 * BLOCK_SIZE);
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
