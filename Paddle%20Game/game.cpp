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
//LPDIRECT3DTEXTURE9 ball_image;
//SPRITE ball;

//paddle sprite
//LPDIRECT3DTEXTURE9 paddle_image;
//SPRITE paddle;

//paddle sprite2
//LPDIRECT3DTEXTURE9 paddle_image2;
//SPRITE paddle2;
//the wave sound
//CSound *sound_bounce;
//CSound *sound_hit;

//misc
long start = GetTickCount();
HRESULT result;


// Font
ID3DXFont *font;
RECT rScore1;
RECT rScore2;
RECT rTimer;
std::string message1;
std::string message2;
std::string timerText;

Balls ball;
Paddles paddle1(1);
Paddles paddle2(2);
// keep track the MouseY
ofstream myfile("trace.txt");


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

	ball.Init();
	paddle1.Init();
	paddle2.Init();

	//score


	//load the ball sprite
	//ball_image = LoadTexture("ball.bmp", D3DCOLOR_XRGB(255, 0, 255));
	//if (ball_image == NULL)
		//return 0;

	//set the ball's properties
	//ball.x = SCREEN_WIDTH / 2;
	//ball.y = SCREEN_HEIGHT / 2;
	//ball.width = 12;
	//ball.height = 12;
	//ball.movex = 8;
	//ball.movey = -8;

	//load the paddle sprite
	//paddle_image = LoadTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	//if (paddle_image == NULL)
		//return 0;
	//set paddle properties
	//paddle.x = 40;
	//paddle.y = SCREEN_HEIGHT / 2;
	//paddle.width = 26;
	//paddle.height = 90;


	/*paddle_image2 = LoadTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	//set paddle2 properties
	paddle2.x = SCREEN_WIDTH - 66;
	paddle2.y = SCREEN_HEIGHT / 2;
	paddle2.width = 26;
	paddle2.height = 90;*/


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

int Collision(Object obj1, Object obj2)
{
		RECT dest;
		obj1.UpdateRect();
		obj2.UpdateRect();
	return IntersectRect(&dest, &obj1.box, &obj2.box);
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

	//after short delay, ready for next frame?
	//this keeps the game running at a steady frame rate
	if (GetTickCount() - start >= 30)
	{
		//reset timing
		start = GetTickCount();

		//move the ball sprite
		ball.Move();
		paddle1.Move(1);
		paddle2.Move(2);
		/*//bounce the ball at screen edges
		if (ball.x > SCREEN_WIDTH - ball.width)
		{
			//ball.x -= ball.width;
			//ball.movex *= -1;
			////      PlaySound(sound_bounce);
			// player 2 win
			score1++;
			ball.x = SCREEN_WIDTH / 2;
			ball.y = SCREEN_HEIGHT / 2;
			ball.movex *= -1;


		}
		else if (ball.x < 0)
		{
			/*ball.x += ball.width;
			ball.movex *= -1;*/
			//      PlaySound(sound_bounce);
			// player 2 win
			/*score2++;
			ball.x = SCREEN_WIDTH / 2;
			ball.y = SCREEN_HEIGHT / 2;
			ball.movex *= 1;
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
		*/
		//move the paddle
		/*paddle.x += Mouse_X();
		if (paddle.x > SCREEN_WIDTH - paddle.width)
		paddle.x = SCREEN_WIDTH - paddle.width;
		else if (paddle.x < 0)
		paddle.x = 0;*/

		//check for left arrow

		/*if (Key_Down(DIK_UPARROW))
		{
			paddle1.y -= 5;
		}
			

		//check for right arrow
		else if (Key_Down(DIK_DOWNARROW))
			paddle1.y += 5;

		//check for left arrow
		if (Key_Down(DIK_LEFTARROW))
			paddle1.x -= 5;

		//check for right arrow
		else if (Key_Down(DIK_RIGHTARROW))
			paddle1.x += 5;

		// For paddle2
		if (Key_Down(DIK_W))
			paddle2.y -= 5;

		//check for right arrow
		else if (Key_Down(DIK_S))
			paddle2.y += 5;

		if (Key_Down(DIK_A))
			paddle2.x -= 5;

		//check for right arrow
		else if (Key_Down(DIK_D))
			paddle2.x += 5;

		if (paddle1.y <= 0) {
			paddle1.y = 0;
		}
		if (paddle1.y + (paddle1.box.bottom - paddle1.box.top) >= SCREEN_HEIGHT) {
			paddle1.y = SCREEN_HEIGHT - (paddle1.box.bottom - paddle1.box.top);
		}
		if (paddle2.y <= 0) {
			paddle2.y = 0;
		}
		if (paddle2.y + (paddle2.box.bottom - paddle2.box.top) >= SCREEN_HEIGHT) {
			paddle2.y = SCREEN_HEIGHT - (paddle2.box.bottom - paddle2.box.top);
		}

		if (paddle1.x <= 0) {
			paddle1.x = 0;
		}
		if (paddle1.x + (paddle1.box.right - paddle1.box.left) >= SCREEN_WIDTH) {
			paddle1.x = SCREEN_WIDTH - (paddle1.box.right - paddle1.box.left);
		}
		if (paddle2.x <= 0) {
			paddle2.x = 0;
		}
		if (paddle2.x + (paddle2.box.right - paddle2.box.left) >= SCREEN_WIDTH) {
			paddle2.x = SCREEN_WIDTH - (paddle2.box.right - paddle2.box.left);
		}

		paddle1.UpdateRect();
		paddle2.UpdateRect();
		// !=0 means mouse has moved up or down
		/*if (Mouse_Y() != 0) {
			int tempValue = abs(Mouse_Y()) / 2;
			if (Mouse_Y() > 0) {
				paddle.y += tempValue;
			}
			else {
				paddle.y -= tempValue;
			}
		}
		KeepTrack(Mouse_Y());*/


		
		//see if ball hit the paddle
		if (Collision(paddle1, ball) || Collision(paddle2, ball))
		{
			ball.x -= ball.movex;
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
			ball.Texture,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));

		//draw the paddle
		position.x = (float)paddle1.x;
		position.y = (float)paddle1.y;
		sprite_handler->Draw(
			paddle1.Texture,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));

		//draw the paddle2
		position.x = (float)paddle2.x;
		position.y = (float)paddle2.y;
		sprite_handler->Draw(
			paddle2.Texture,
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

	ball.~Balls();
	paddle1.~Paddles();
	paddle2.~Paddles();
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