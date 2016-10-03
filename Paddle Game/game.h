// Beginning Game Programming, Second Edition
// Chapter 10
// Paddle_Game program header file


#ifndef _GAME_H
#define _GAME_H 1

//windows/directx headers
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
//framework-specific headers
#include "dxgraphics.h"
//#include "dxaudio.h"
#include "dxinput.h"

//application title
#define APPTITLE "Paddle_Game"

//screen setup
//function prototypes
int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);

//sprite structure
typedef struct {
	int x, y;
	int width, height;
	int movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
	int scalex, scaley;
	int rotation, rotaterate;
} SPRITE;


#endif

