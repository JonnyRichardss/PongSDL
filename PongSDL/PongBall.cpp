#include "PongBall.h"
#include <iostream>
#include "GameEngine.h"
void PongBall::Init()
{
	BoundingBox = Vector2(BALL_SIZE);
	shown = true;
	NewBall(true);
	//PLAYER 0 IS ON THE RIGHT
	player0 = new PlayerController();
	player0->SetPlayerNo(false);
	player1 = new PlayerController();
	player1->SetPlayerNo(true);
	engine->RegisterObject(player1);
	engine->RegisterObject(player0);
}

void PongBall::NewBall(bool ServePlayer)
{
	position = ServePlayer ? Vector2(-100, 0) : Vector2(100, 0);
	velocity = ServePlayer ? Vector2(5, 0) : Vector2(-5, 0);
	lifetime = 0;
}

void PongBall::MovePlayer(bool player, bool up)
{
	PlayerController* playerP = player ? player1: player0;
	playerP->Move(up);
}
void PongBall::ResetGame()
{
	player0->score = 0;
	player1->score = 0;
	NewBall(true);
}


void PongBall::Update()
{
	lifetime++;
	velocity += velocity.Normalise() * ((float)lifetime / ACCLERATION_CLAMP_FACTOR);
	position += velocity;
	//collision
	CheckCollision();

}


void PongBall::InitVisuals()
{
	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);

	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

void PongBall::CheckCollision()
{
	//check bat
	if (position.x > PADDLE_X_ABS) {
		//right paddle
		if (!TryCollide(player0) && position.x > PADDLE_X_ABS + (PADDLE_W+BALL_SIZE /2.0f)) {
			player1->score++;
			NewBall(true);
		}
	}
	else if (position.x < -PADDLE_X_ABS) {
		if (!TryCollide(player1) && position.x < -1* (PADDLE_X_ABS + (PADDLE_W + BALL_SIZE / 2.0f))) {
			player0->score++;
			NewBall(false);
		}
	}
	//check topbotedge
	if (position.y >= GAME_MAX_Y) {
		Bounce(Vector2::up());
	}
	else if (position.y <= -GAME_MAX_Y) {
		Bounce(Vector2::up() * -1.0f);
	}
	else if (position.x >= GAME_MAX_X) {
		Bounce(Vector2::right() * -1);
	}
	else if (position.x <= -GAME_MAX_X) {
		Bounce(Vector2::right());
	}
}
bool PongBall::TryCollide(PlayerController* player) {
	float dist = position.y - player->GetPos().y;
	if (abs(dist)  > ((player->GetBB().y + BoundingBox.y) / 2.0f))
		return false;
	Vector2 CollisionNormal = player->GetSurfNormal();
	CollisionNormal.y -= dist / DEFLECTION_REDUCTION_MODIFIER;
	Bounce(CollisionNormal);
	position -= player->GetSurfNormal() * 5.0f; // teleport ball
	return true;

}
void PongBall::BounceBat() {

}
void PongBall::Bounce(Vector2 SurfaceNormal) {
	SurfaceNormal = SurfaceNormal.Normalise();
	velocity -= 2 * SurfaceNormal * Vector2::dot(velocity, SurfaceNormal);
}

