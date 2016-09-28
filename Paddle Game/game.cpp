// Beginning Game Programming, Second Edition
// Chapter 10
// Paddle_Game program source code file
#include <iostream>
#include "game.h"
#include <fstream>
#include "Ball.h"
#include "Paddle.h"
using namespace std;
//background image
LPDIRECT3DSURFACE9 back;

//sprite handler
LPD3DXSPRITE sprite_handler;

//misc
long start = GetTickCount();
HRESULT result;
// Score
 int score1 = 0;
 int score2 = 0;
 int totalTime = 0;
 bool isIncreaseScore = false;
// Font
ID3DXFont *font;
RECT rScore1;
RECT rScore2;
RECT rTimer;
std::string message1;
std::string message2;
std::string timerText;

Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;
// keep track the MouseY
ofstream myfile("trace.txt");

int GenerateNewPostion() {

	//int v3 = rand() % 30 + 1985;// v3 in the range 1985-2014 // b-a-1   + a
	int random = rand() % 2 + 1;
	return (random == 2) ? 1 : -1;
}

//initializes the game
void UpdateLables() {
	message1 = to_string(score1);
	message2 = to_string(score2);
	timerText = to_string(totalTime) + 's';
}
void KeepTrack(int mouseY) {

	if (myfile.is_open())
	{
		myfile << "Mouse_Y = " << mouseY << "\n";
		//myfile.close();
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

	ball.InitTexture("ball.bmp", D3DCOLOR_XRGB(255, 0, 255));
	if (ball.GetTexture() == NULL) {
		return 0;
	}
	ball.x = SCREEN_WIDTH / 2;
	ball.y = SCREEN_HEIGHT / 2;
	ball.width = 12;
	ball.height = 12;
	ball.movex = 8;
	ball.movey = -8;

	leftPaddle.InitTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (leftPaddle.GetTexture() == NULL) {
		return 0;
	}
	leftPaddle.x = 40;
	leftPaddle.y = SCREEN_HEIGHT / 2;
	leftPaddle.width = 26;
	leftPaddle.height = 90;
	
	rightPaddle.InitTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (rightPaddle.GetTexture() == NULL) {
		return 0;
	}
	rightPaddle.x = SCREEN_WIDTH - 66;
	rightPaddle.y = SCREEN_HEIGHT / 2;
	rightPaddle.width = 26;
	rightPaddle.height = 90;

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
	return 1;
}

//the main game loop
void Game_Run(HWND hwnd)
{
	D3DXVECTOR3 position(0, 0, 0);

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;

	//update mouse and keyboard
	Poll_Mouse();
	Poll_Keyboard();
	//CountTime();
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



		//check for left arrow
		if (Key_Down(DIK_UPARROW))
			leftPaddle.y -= 5;

		//check for right arrow
		else if (Key_Down(DIK_DOWNARROW))
			leftPaddle.y += 5;

		// For paddle2
		if (Key_Down(DIK_W))
			rightPaddle.y -= 5;

		//check for right arrow
		else if (Key_Down(DIK_S))
			rightPaddle.y += 5;


		//  constraint the paddle to the screen's edges
		if (leftPaddle.y <= 0) {
			leftPaddle.y = 0;
		}
		if (leftPaddle.y + leftPaddle.height >= SCREEN_HEIGHT) {
			leftPaddle.y = SCREEN_HEIGHT - leftPaddle.height;
		}
		if (rightPaddle.y <= 0) {
			rightPaddle.y = 0;
		}
		if (rightPaddle.y + rightPaddle.height >= SCREEN_HEIGHT) {
			rightPaddle.y = SCREEN_HEIGHT - rightPaddle.height;
		}
		//see if ball hit the paddle
		if (ball.isCollisonWith(leftPaddle) || ball.isCollisonWith(rightPaddle))
		{
			ball.x -= ball.movey;
			ball.movex *= -1;
			isIncreaseScore = true;
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
		position.x = (float)ball.X();
		position.y = (float)ball.Y();
		sprite_handler->Draw(
			ball.GetTexture(),
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));

		//draw the paddle
		position.x = (float)leftPaddle.X();
		position.y = (float)leftPaddle.Y();
		sprite_handler->Draw(
			leftPaddle.GetTexture(),
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));

		//draw the paddle2
		position.x = (float)rightPaddle.X();
		position.y = (float)rightPaddle.Y();
		sprite_handler->Draw(
			rightPaddle.GetTexture(),
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

	if (ball.GetTexture() != NULL)
		ball.~Ball();

	if (leftPaddle.GetTexture() != NULL)
		leftPaddle.~Paddle();

	if (rightPaddle.GetTexture() != NULL)
		rightPaddle.~Paddle();
	
	if (back != NULL)
		back->Release();

	if (sprite_handler != NULL)
		sprite_handler->Release();

}