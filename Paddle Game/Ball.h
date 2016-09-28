#pragma once
#include "GameObject.h"
class Ball: public GameObject
{
protected:
	virtual void Move();
public:
	Ball();
	~Ball();
};

