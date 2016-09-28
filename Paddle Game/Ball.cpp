#include "Ball.h"



Ball::Ball()
{
}

void Balls::Move()
{
	x += movex;
	y += movey;
	if (x > SCREEN_WIDTH - width)
	{
		score1++;
		x = SCREEN_WIDTH / 2;
		y = SCREEN_HEIGHT / 2;
		movex *= -1;
	}
	else if (x < 0)
	{
		score2++;
		x += width;
		movex *= -1;
		x = SCREEN_WIDTH / 2;
		y = SCREEN_HEIGHT / 2;
	}

		if (y > SCREEN_HEIGHT - height)
		{
		y -= height;
		movey *= -1;
		//    PlaySound(sound_bounce);
		}
		else if (y < 0)
		{
		y += height;
		movey *= -1;
		//    PlaySound(sound_bounce);
		}
}


Balls::~Balls()
{
	if (Texture != NULL)
		Texture->Release();
}

int Balls::Init()
{
	//load the ball sprite
	Texture = LoadTexture("ball.bmp", D3DCOLOR_XRGB(255, 0, 255));
	if (Texture == NULL)
		return 0;
	//set the ball's properties
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
	width = 12;
	height = 12;
	movex = 8;
	movey = -8;
	return 1;
}