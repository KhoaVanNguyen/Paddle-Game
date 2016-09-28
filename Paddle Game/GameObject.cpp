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
	rect1.left = x + 1;
	rect1.top = y + 1;
	rect1.right = x + width - 1;
	rect1.bottom = y + height - 1;

	RECT rect2;
	rect2.left = secondObj.x + 1;
	rect2.top = secondObj.y + 1;
	rect2.right = secondObj.x + secondObj.width - 1;
	rect2.bottom = secondObj.y + secondObj.height - 1;

	RECT dest;
	return IntersectRect(&dest, &rect1, &rect2);
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