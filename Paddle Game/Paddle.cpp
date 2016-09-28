#include "Paddle.h"



Paddle::Paddle() {
	GameObject::GameObject();
}
Paddle::~Paddle()
{
	if (GameObjectTexture != NULL) {
		GameObjectTexture->Release();
	}
}

void Paddle::Move() {
	
}