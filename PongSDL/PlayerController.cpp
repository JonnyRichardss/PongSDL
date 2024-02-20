#include "PlayerController.h"

void PlayerController::Init(bool _playerNo)
{
	position = Vector2::zero();
	velocity = Vector2::zero();
	PlayerNo = _playerNo;
}

void PlayerController::MoveUp()
{
	position.y += 1;
}

void PlayerController::MoveDown()
{
	position.y -= 1;
}

void PlayerController::Update()
{

}

void PlayerController::InitVisuals()
{
	SDL_Surface* Surf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	SDL_FillRect(Surf, NULL, ColourRGBA::White().MapFromColour(Surf->format));

	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
	//rect to construct renderableComponents
	int xpos = PlayerNo ? (windowWidth / 8) : (windowWidth * (7.0f / 8.0f));
	SDL_Rect DefaultRect = { xpos ,windowHeight / 2,5,10};
	visuals->UpdateDestPos(&DefaultRect);
}


