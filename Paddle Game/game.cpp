// Beginning Game Programming, Second Edition
// Chapter 10
// Paddle_Game program source code file


#include "game.h"

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

//the wave sound
//CSound *sound_bounce;
//CSound *sound_hit;

//misc
long start = GetTickCount();
HRESULT result;


//initializes the game
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
	ball.x = 400;
	ball.y = 200;
	ball.width = 12;
	ball.height = 12;
	ball.movex = 8;
	ball.movey = -8;

	//load the paddle sprite
	paddle_image = LoadTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (paddle_image == NULL)
		return 0;
	//set paddle properties
	paddle.x = 20;
	paddle.y = SCREEN_HEIGHT / 2;
	paddle.width = 26;
	paddle.height = 90;

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
			ball.x -= ball.width;
			ball.movex *= -1;
			//      PlaySound(sound_bounce);
		}
		else if (ball.x < 0)
		{
			ball.x += ball.width;
			ball.movex *= -1;
			//      PlaySound(sound_bounce);
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
		paddle.x += Mouse_X();
		if (paddle.x > SCREEN_WIDTH - paddle.width)
			paddle.x = SCREEN_WIDTH - paddle.width;
		else if (paddle.x < 0)
			paddle.x = 0;

		//  constraint the paddle to the screen's edges

		if (paddle.y <= 0) {
			paddle.y = 0;
		}
		if (paddle.y + paddle.height >= SCREEN_HEIGHT) {
			paddle.y = SCREEN_HEIGHT - paddle.height;
		}

		//check for left arrow
		if (Key_Down(DIK_UPARROW))
			paddle.y -= 5;

		//check for right arrow
		if (Key_Down(DIK_DOWNARROW))
			paddle.y += 5;


		//see if ball hit the paddle
		if (Collision(paddle, ball))
		{
			ball.y -= ball.movey;
			ball.movey *= -1;
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

	if (back != NULL)
		back->Release();

	if (sprite_handler != NULL)
		sprite_handler->Release();

	//if (sound_bounce != NULL)
	//    delete sound_bounce;

	//if (sound_hit != NULL)
	//    delete sound_hit;


}

