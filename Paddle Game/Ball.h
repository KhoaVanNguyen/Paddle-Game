#pragma once
#include "GameObject.h"
#include "Constants.h"
class Ball: public GameObject
{
public:
	virtual void Move();
public:
	void ResetPosition();
	int IsScore();
	Ball();
	~Ball();
};

