#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "dxgraphics.h"
#include "Constants.h"
class GameObject
{
protected:
	
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
	void SetPosition(int, int);
	void SetVelocity(int, int);
	void SetSize(int, int);
	int InitTexture(char*, D3DCOLOR);
	
	void Draw(LPD3DXSPRITE);

	// getter - setter
	LPDIRECT3DTEXTURE9 GetTexture();
	int X();
	int Y();
	int VelX();
	int VelY();
	int Width();
	int Height();
	GameObject();
	~GameObject();

	RECT GetRect();

	friend int CheckCollision(GameObject,GameObject);
//	friend DIRS Orientation(GameObject, GameObject);
};

