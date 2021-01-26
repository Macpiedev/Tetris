

#ifndef GAME_FUNCS
#define GAME_FUNCS

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdbool.h>


#define FPS 60
#define SCREEN_WIDTH 820
#define SCREEN_HEIGHT 720
#define PLAY_WIDTH 300
#define PLAY_HEIGHT 600
#define TOP_LEFT_X (SCREEN_WIDTH - 20 - PLAY_WIDTH) /2
#define TOP_LEFT_Y (SCREEN_HEIGHT - 20 - PLAY_HEIGHT) 
#define ROWS 20
#define COLUMNS 10
#define BLOCK_SIZE 30

void initWindow();
int startGame();
void exitGame();
SDL_Window* window;
SDL_Renderer* renderer;

bool isRunning;

int grid[20][10];
typedef struct Text
{
	SDL_Texture *textTexture;
	SDL_Rect position;
}Text;
#endif
