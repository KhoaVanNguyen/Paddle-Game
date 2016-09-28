#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "dxgraphics.h"
#include "game.h"
class GameObject
{
protected:
	int x, y;
	int width, height;
	int movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
	int scalex, scaley;
	int rotation, rotaterate;
public:
	GameObject();
	~GameObject();
};

