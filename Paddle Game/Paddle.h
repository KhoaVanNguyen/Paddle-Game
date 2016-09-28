#pragma once
#include "GameObject.h"
class Paddle : public GameObject
{
protected:
	virtual void Move();
public:
	Paddle();
	~Paddle();
};

