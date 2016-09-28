#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "dxgraphics.h"
#include "game.h"
#include "Object.h"
#include "dxinput.h"
class Paddles: public Object
{
public:
	LPDIRECT3DTEXTURE9 Texture;
public:
	void Move(int);
	int Init();
	Paddles(int);
	~Paddles();
};

