#include "PlayerController.h"
#include "PlayerScore.h"
#include "GameEngine.h"
void PlayerController::Init()
{
	//WARNING SetPlayerNo MUST Be called before INIT (I might change this os the values just update but thats not how it is atm)
	shown = true;
	
	int xpos = PlayerNo ? -PADDLE_X_ABS : PADDLE_X_ABS;
	score.SetPos(PlayerNo ? Vector2(-SCORE_X_ABS, SCORE_Y) : Vector2(SCORE_X_ABS, SCORE_Y));
	position = Vector2(xpos, 0);
	BoundingBox = Vector2(PADDLE_W, PADDLE_H);
	velocity = Vector2::zero();
	score = 0;
	GameEngine::GetInstance()->RegisterObject(&score);
}
void PlayerController::SetPlayerNo(bool _playerNo) {
	PlayerNo = _playerNo;
	
}
void PlayerController::MoveUp()
{
	position.y += PADDLE_MOVESPEED;
}

void PlayerController::MoveDown()
{
	position.y -= PADDLE_MOVESPEED;
}

void PlayerController::Move(bool up)
{
	if (up)
		MoveUp();
	else
		MoveDown();
}

Vector2 PlayerController::GetSurfNormal()
{
	return PlayerNo ? ( -1.0f * Vector2::right()) : Vector2::right();
}

void PlayerController::Update()
{
	//
}

void PlayerController::InitVisuals()
{
	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
	//rect to construct renderableComponents
	//int xpos = PlayerNo ? (windowWidth / 8) : (windowWidth * (7.0f / 8.0f));
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}


