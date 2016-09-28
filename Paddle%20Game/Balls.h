#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "dxgraphics.h"
#include "game.h"
class Balls: public Object
{
public:
	int movex, movey;
	LPDIRECT3DTEXTURE9 Texture;
	void Move();
private:
	
public:
	int Init();
	Balls();
	~Balls();
};

