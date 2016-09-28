#pragma once
#include "GameObject.h"
class Paddle: public GameObject
{
public:
	LPDIRECT3DTEXTURE9 Texture;
public:
	void Move(int);
	int Init();
	Paddle(int);
	~Paddle();
};

