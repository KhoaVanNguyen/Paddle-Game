#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "dxgraphics.h"
#include "game.h"
class GameObject
{
protected:
	
	// functions
	
	// virtual functions
	virtual void Move();
	
public:
	int x, y;
	int width, height;
	int movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
	int scalex, scaley;
	int rotation, rotaterate;

	LPDIRECT3DTEXTURE9 GameObjectTexture;
	char *imageUrl;
	bool isCollisonWith(GameObject);
	void SetPosition(int, int);
	void SetVelocity(int, int);
	void SetSize(int, int);
	//void LoadTexture(char*, D3DCOLOR);
	int InitTexture(char*, D3DCOLOR);

	// getter 
	LPDIRECT3DTEXTURE9 GetTexture();
	int X();
	int Y();
	int VelX();
	int VelY();
	int Width();
	int Height();
	GameObject();
	~GameObject();
};

