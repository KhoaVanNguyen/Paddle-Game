#include "Ball.h"



Ball::Ball()
{
	GameObject::GameObject();
}


Ball::~Ball(){
	if (GameObjectTexture != NULL) {
		GameObjectTexture->Release();
	}
}
void Ball::Move() {

}