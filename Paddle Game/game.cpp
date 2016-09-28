// Beginning Game Programming, Second Edition
// Chapter 10
// Paddle_Game program source code file
#include <iostream>
#include "game.h"
#include <fstream>
using namespace std;
//background image
LPDIRECT3DSURFACE9 back;

//sprite handler
LPD3DXSPRITE sprite_handler;

//ball sprite
LPDIRECT3DTEXTURE9 ball_image;
SPRITE ball;
//paddle sprite
LPDIRECT3DTEXTURE9 paddle_image;
SPRITE paddle;

//paddle sprite2
LPDIRECT3DTEXTURE9 paddle_image2;
SPRITE paddle2;
//the wave sound
//CSound *sound_bounce;
//CSound *sound_hit;

//misc

// Timer
long start = GetTickCount();
long startTimer = GetTickCount();
long totalSeconds = 0;
HRESULT result;

// Score
int score1 = 0;
int score2 = 0;
bool isIncreaseScore = false;

// SPEED
int keyboradSpeed = 10;

// Font
ID3DXFont *font;
RECT rScore1;
RECT rScore2;
RECT rTimer;
std::string message1;
std::string message2;
std::string timerText;
// keep track the MouseY
ofstream myfile("trace.txt");
//initializes the game
int GenerateNewPostion() {

	//int v3 = rand() % 30 + 1985;// v3 in the range 1985-2014 // b-a-1   + a
	int random = rand() % 2 + 1;
	return (random == 2) ? 1 : -1;
}

void CountTime() {
	if (GetTickCount() - startTimer > 1000) {
		totalSeconds++;
		startTimer = GetTickCount();
	}
}
void UpdateLables() {
	message1 = to_string(score1);
	message2 = to_string(score2);
	timerText = to_string(totalSeconds) + " s";
}
void KeepTrack(int mouseY) {

	if (myfile.is_open())
	{
		//myfile << "Mouse_Y = " << mouseY << "\n";
		//myfile.close();
		if (GetTickCount() - startTimer > 1000) {
			totalSeconds++;
			//myfile << "Time : " << totalSeconds << "\n";
			startTimer = GetTickCount();
		}
	}
	else {
		//MessageBox(hwnd, "Error initializing the mouse", "Error", MB_OK);
	}
}

int Game_Init(HWND hwnd)
{
	//set random number seed
	srand(time(NULL));
	//initialize mouse
	if (!Init_Mouse(hwnd))
	{
		MessageBox(hwnd, "Error initializing the mouse", "Error", MB_OK);
		return 0;
	}

	//initialize keyboard
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}

	//create sprite handler object
	result = D3DXCreateSprite(d3ddev, &sprite_handler);
	if (result != D3D_OK)
		return 0;

	//load the background image
	back = LoadSurface("background.bmp", NULL);
	if (back == NULL)
		return 0;

	//load the ball sprite
	ball_image = LoadTexture("ball.bmp", D3DCOLOR_XRGB(255, 0, 255));
	if (ball_image == NULL)
		return 0;

	//set the ball's properties
	ball.x = SCREEN_WIDTH / 2;
	ball.y = SCREEN_HEIGHT / 2;
	ball.width = 12;
	ball.height = 12;
	ball.movex = 8;
	ball.movey = -8;

	//load the paddle sprite
	paddle_image = LoadTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (paddle_image == NULL)
		return 0;
	//set paddle properties
	paddle.x = 40;
	paddle.y = SCREEN_HEIGHT / 2;
	paddle.width = 26;
	paddle.height = 90;

	paddle_image2 = LoadTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	//set paddle2 properties
	paddle2.x = SCREEN_WIDTH - 66;
	paddle2.y = SCREEN_HEIGHT / 2;
	paddle2.width = 26;
	paddle2.height = 90;

	// Init font
	font = NULL;
	HRESULT fontResult = D3DXCreateFont(d3ddev, 40, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
	if (!SUCCEEDED(fontResult)) {
		return false;
	}

	SetRect(&rScore1, 0, 0, 200, 400);
	SetRect(&rScore2, SCREEN_WIDTH - 200, 0, SCREEN_WIDTH, 400);
	SetRect(&rTimer, (SCREEN_WIDTH / 2) - 50, 0, (SCREEN_WIDTH / 2) + 50, 100);
	UpdateLables();
	//load bounce wave file
	//    sound_bounce = LoadSound("bounce.wav");
	/*  if (sound_bounce == NULL)
	return 0;*/

	//load the hit wave file
	//    sound_hit = LoadSound("hit.wav");
	/* if (sound_hit == NULL)
	return 0;
	*/
	//return okay
	return 1;
}

int Collision(SPRITE sprite1, SPRITE sprite2)
{
	RECT rect1;
	rect1.left = sprite1.x + 1;
	rect1.top = sprite1.y + 1;
	rect1.right = sprite1.x + sprite1.width - 1;
	rect1.bottom = sprite1.y + sprite1.height - 1;

	RECT rect2;
	rect2.left = sprite2.x + 1;
	rect2.top = sprite2.y + 1;
	rect2.right = sprite2.x + sprite2.width - 1;
	rect2.bottom = sprite2.y + sprite2.height - 1;

	RECT dest;
	return IntersectRect(&dest, &rect1, &rect2);
}

//the main game loop
void Game_Run(HWND hwnd)
{
	//ball position vector
	D3DXVECTOR3 position(0, 0, 0);

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;

	//update mouse and keyboard
	Poll_Mouse();
	Poll_Keyboard();
	CountTime();
	//after short delay, ready for next frame?
	//this keeps the game running at a steady frame rate
	if (GetTickCount() - start >= 30)
	{
		//reset timing
		start = GetTickCount();

		//move the ball sprite
		ball.x += ball.movex;
		ball.y += ball.movey;

		//bounce the ball at screen edges
		if (ball.x > SCREEN_WIDTH - ball.width)
		{
			//ball.x -= ball.width;
			//ball.movex *= -1;
			////      PlaySound(sound_bounce);
			// player 2 win
			score1++;
			ball.x = SCREEN_WIDTH / 2;
			ball.y = SCREEN_HEIGHT / 2;
			ball.movex *= GenerateNewPostion();
		}
		else if (ball.x < 0)
		{
			/*ball.x += ball.width;
			ball.movex *= -1;*/
			//      PlaySound(sound_bounce);
			// player 2 win
			score2++;
			ball.x = SCREEN_WIDTH / 2;
			ball.y = SCREEN_HEIGHT / 2;
			ball.movex *= GenerateNewPostion();
		}

		if (ball.y > SCREEN_HEIGHT - ball.height)
		{
			ball.y -= ball.height;
			ball.movey *= -1;
			//    PlaySound(sound_bounce);
		}
		else if (ball.y < 0)
		{
			ball.y += ball.height;
			ball.movey *= -1;
			//    PlaySound(sound_bounce);
		}

		//move the paddle
		/*paddle.x += Mouse_X();
		if (paddle.x > SCREEN_WIDTH - paddle.width)
			paddle.x = SCREEN_WIDTH - paddle.width;
		else if (paddle.x < 0)
			paddle.x = 0;*/

			//check for left arrow
		if (Key_Down(DIK_UPARROW))
			paddle.y -= keyboradSpeed;

		//check for right arrow
		else if (Key_Down(DIK_DOWNARROW))
			paddle.y += keyboradSpeed;

		// For paddle2
		if (Key_Down(DIK_W))
			paddle2.y -= keyboradSpeed;

		//check for right arrow
		else if (Key_Down(DIK_S))
			paddle2.y += keyboradSpeed;
		// !=0 means mouse has moved up or down
		if (Mouse_Y() != 0) {
			int tempValue = abs(Mouse_Y()) / 2;
			if (Mouse_Y() > 0) {
				paddle.y += tempValue;
			}
			else {
				paddle.y -= tempValue;
			}
		}


		//  constraint the paddle to the screen's edges
		if (paddle.y <= 0) {
			paddle.y = 0;
		}
		if (paddle.y + paddle.height >= SCREEN_HEIGHT) {
			paddle.y = SCREEN_HEIGHT - paddle.height;
		}
		if (paddle2.y <= 0) {
			paddle2.y = 0;
		}
		if (paddle2.y + paddle2.height >= SCREEN_HEIGHT) {
			paddle2.y = SCREEN_HEIGHT - paddle2.height;
		}
		//see if ball hit the paddle
		if (Collision(paddle, ball) || Collision(paddle2, ball))
		{
			ball.x -= ball.movey;
			ball.movex *= -1;
			isIncreaseScore = true;
			//   PlaySound(sound_hit);
		}
	}
	//start rendering
	if (d3ddev->BeginScene())
	{
		//erase the entire background
		d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);

		//start sprite handler
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

		//draw the ball
		position.x = (float)ball.x;
		position.y = (float)ball.y;
		sprite_handler->Draw(
			ball_image,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		//draw the paddle
		position.x = (float)paddle.x;
		position.y = (float)paddle.y;
		sprite_handler->Draw(
			paddle_image,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));

		//draw the paddle2
		position.x = (float)paddle2.x;
		position.y = (float)paddle2.y;
		sprite_handler->Draw(
			paddle_image2,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));

		UpdateLables();
		// draw text:
		if (font != NULL) {
			font->DrawTextA(NULL, message1.c_str(), -1, &rScore1, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		}
		if (font != NULL) {
			font->DrawTextA(NULL, message2.c_str(), -1, &rScore2, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));
		}
		if (font != NULL) {
			font->DrawTextA(NULL, timerText.c_str(), -1, &rTimer, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
		}
		//stop drawing
		sprite_handler->End();

		//stop rendering
		d3ddev->EndScene();
	}

	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//check for mouse button (to exit program)
	if (Mouse_Button(0))
		PostMessage(hwnd, WM_DESTROY, 0, 0);

	//check for escape key (to exit program)
	if (Key_Down(DIK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

//frees memory and cleans up before the game ends
void Game_End(HWND hwnd)
{
	if (ball_image != NULL)
		ball_image->Release();

	if (paddle_image != NULL)
		paddle_image->Release();

	if (paddle_image2 != NULL)
		paddle_image2->Release();
	if (back != NULL)
		back->Release();

	if (sprite_handler != NULL)
		sprite_handler->Release();
	if (font != NULL) {
		font->Release();
		font = 0;
	}
	//if (sound_bounce != NULL)
	//    delete sound_bounce;

	//if (sound_hit != NULL)
	//    delete sound_hit;
}
