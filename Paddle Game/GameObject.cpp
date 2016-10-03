#include "GameObject.h"

void GameObject::SetPosition(int newX, int newY) {
	x = newX;
	y = newY;
}
void GameObject::SetVelocity(int newX, int newY) {
	movex = newX;
	movey = newY;
}
void GameObject::SetSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
}
int GameObject::InitTexture(char *imageUrl, D3DCOLOR color)
{
	this->imageUrl = imageUrl;
	GameObjectTexture = LoadTexture(this->imageUrl, color);
	if (GameObjectTexture == NULL) {
		return 0;
	}
	return 1;
}

bool GameObject::isCollisonWith(GameObject secondObj) {
	RECT rect1;
	rect1.left = x ;
	rect1.top = y ;
	rect1.right = x + width ;
	rect1.bottom = y + height ;

	RECT rect2;
	rect2.left = secondObj.x ;
	rect2.top = secondObj.y ;
	rect2.right = secondObj.x + secondObj.width ;
	rect2.bottom = secondObj.y + secondObj.height ;


	return  rect1.right >= rect2.left &&
		rect1.left <= rect2.right &&
		rect1.top <= rect2.bottom &&
		rect1.bottom >= rect2.top;
}
GameObject::GameObject()
{
	
}


GameObject::~GameObject()
{
	
}
void GameObject::Move() {

}

// Getter - Setter
LPDIRECT3DTEXTURE9 GameObject::GetTexture(){
	return GameObjectTexture;
}

int GameObject::X() {
	return x;
}
int GameObject::Y() {
	return y;
}
int GameObject::VelX() {
	return movex;
}
int GameObject::VelY() {
	return movey;
}
int GameObject::Width() {
	return width;
}
int GameObject::Height() {
	return height;
}