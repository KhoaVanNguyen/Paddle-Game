#include "Paddles.h"



Paddles::Paddles(int index)
{
	if (index==1)
	{
		//set paddle properties
		x = 40;
		y = SCREEN_HEIGHT / 2;
		width = 26;
		height = 90;
	}
	if (index == 2)
	{
		x = SCREEN_WIDTH - 40;
		y = SCREEN_HEIGHT / 2;
		width = 26;
		height = 90;
	}
}


Paddles::~Paddles()
{
	if (Texture != NULL)
		Texture->Release();
}
int Paddles::Init()
{
	Texture = LoadTexture("paddle.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (Texture == NULL)
		return 0;
	return 1;
}

void Paddles::Move(int index)
{
	if (index == 1)
	{
		if (Key_Down(DIK_UPARROW))
		{
			y -= 5;
		}
		//check for right arrow
		else if (Key_Down(DIK_DOWNARROW))
			y += 5;
		//check for left arrow
		if (Key_Down(DIK_LEFTARROW))
			x -= 5;

		//check for right arrow
		else if (Key_Down(DIK_RIGHTARROW))
			x += 5;
		//check if paddle out of boundary
		if (x < 0)
			x = 0;
		else if (x >(SCREEN_WIDTH / 2 - width))
			x = SCREEN_WIDTH / 2 - width;
		if (y < 0)
			y = 0;
		else if (y >(SCREEN_HEIGHT - height))
			y = SCREEN_HEIGHT - height;
	}
	else if (index == 2)
	{
		if (Key_Down(DIK_W))
			y -= 5;

		//check for right arrow
		else if (Key_Down(DIK_S))
			y += 5;

		if (Key_Down(DIK_A))
			x -= 5;

		//check for right arrow
		else if (Key_Down(DIK_D))
			x += 5;
		if (x > (SCREEN_WIDTH - width))
			x = SCREEN_WIDTH - width;
		else if (x < (SCREEN_WIDTH / 2 ))
			x = SCREEN_WIDTH / 2;
		if (y < 0)
			y = 0;
		else if (y >(SCREEN_HEIGHT - height))
			y = SCREEN_HEIGHT - height;
	}
	
}