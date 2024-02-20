#include "PongBall.h"

void PongBall::Init()
{
	shown = true;
	NewBall();
}

void PongBall::NewBall()
{
	position = Vector2(windowWidth / 2, windowHeight / 2);
	velocity = Vector2(0, 0); //randomise this
	lifetime = 0;
}

void PongBall::Update()
{
	lifetime++;
	position += velocity;
	//collision
	//
}
void PongBall::MoveVisuals() {
	SDL_Rect pos = *(visuals->GetDestPos());
	pos.x = position.x;
	pos.y = position.y;
	visuals->UpdateDestPos(&pos);
}

void PongBall::InitVisuals()
{
	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);


	SDL_Rect DefaultRect = { windowWidth/2 ,windowHeight/2 ,10,10 };
	visuals->UpdateDestPos(&DefaultRect);
}

void PongBall::CheckCollision()
{
	//check bat

	//check topbotedge
	if (position.y >= windowHeight || position.y <= 0) {
		Bounce();
	}
	//checkScore
}
void PongBall::BounceBat() {

}
void PongBall::Bounce() {

}

