#include "Ball.h"

Ball::Ball()
{
	GameObject::GameObject();
}
Ball::~Ball(){
	if (GameObjectTexture != NULL) {
		GameObjectTexture->Release();
	}
}
void Ball::Move() {
	//get properties
	int iX = X();
	int iY = Y();
	int iMoveX = VelX();
	int iMoveY = VelY();
	int iWidth = Width();
	int iHeight = Height();
	
	iX += iMoveX;
	iY += iMoveY;

	//if (!IsScore())
	{
		//horinzontal boundary
		if (iY < 0)
		{
			iY = 0;
			iMoveY *= -1;
		}
		else if (iY > SCREEN_HEIGHT - iHeight)
		{
			iY = SCREEN_HEIGHT - iHeight;
			iMoveY *= -1;
		}

		

		//set the properties back
		SetPosition(iX, iY);
		SetVelocity(iMoveX, iMoveY);
	}
	
}


int Ball::IsScore()
{
	
	//vertical boundary
	if (x < 0)
	{
		ResetPosition();
		return 2;
	}
	else if (x > (SCREEN_WIDTH - width))
	{
		ResetPosition();
		return 1;
	}
	return 0;
}


void Ball::ResetPosition()
{
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
	movex *= -1;
}