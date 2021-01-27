

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
int startGame(const int frameDelay);
void exitGame();
int cordinatesToGridX(int x);
int cordinatesToGridY(int y);
int gridXtoCordinates(int x);
int gridYtoCordinates(int y);
bool emptySpace(int x, int y);

SDL_Window* window;
SDL_Renderer* renderer;

bool isRunning;


int grid[20][10];

typedef struct Text
{
	SDL_Texture *textTexture;
	SDL_Rect position;
}Text;

extern char S2[], S1[], I1[], I2[], I3[], Z1[], Z2[], O[], J1[], J2[], J3[], J4[], L1[], L2[], L3[], L4[], T1[], T2[], T3[], T4[];
#endif
