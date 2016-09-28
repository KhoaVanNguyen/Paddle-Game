#pragma once
#include "GameObject.h"
class Ball: public GameObject
{
public:
	int movex, movey;
	LPDIRECT3DTEXTURE9 Texture;
	void Move();
private:
	
public:
	int Init();
	Ball();
	~Ball();
};

