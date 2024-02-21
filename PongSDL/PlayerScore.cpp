#include "PlayerScore.h"
#include <iostream>
void PlayerScore::Init()
{

	shown = true;
	is_static = true;
	velocity = Vector2::zero();
	BoundingBox = Vector2(CHAR_WIDTH, CHAR_HEIGHT);


}

void PlayerScore::InitVisuals()
{

	
	
	visuals->UpdateLayer(-1);
	UpdateTexture();
	SDL_Rect scoreLocation = BBtoDestRect();
	visuals->UpdateDestPos(&scoreLocation);
}

void PlayerScore::SetPos(Vector2 newPos)
{
	position = newPos;
	MoveVisuals();
}

void PlayerScore::Update()
{
	//donothing
	//std::cout << "HELLO WORLD";
}


void PlayerScore::UpdateTexture()
{
	if (scoreFont == nullptr) scoreFont = TTF_OpenFont("USN_STENCIL.TTF", CHAR_HEIGHT);
	char buffer[sizeof(int) * 8 + 1];
	itoa(score, buffer, 10);
	SDL_Color white={255,255,255,255};
	SDL_Color black = {0,0,0,255};
	SDL_Surface* Surf = TTF_RenderUTF8_LCD_Wrapped(scoreFont, buffer, white, black, 0);
	if (Surf == nullptr) std::cout << "\n\n\n PLAYERSCORE UPDATETEX  GON\n\n\n\n";
	//std::cout << SDL_GetError()<<"\n";
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderContext, Surf);
	//std::cout << SDL_GetError()<<"\n";
	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(scoreTexture);
	if (score == 0)
		BoundingBox.x = CHAR_WIDTH;
	else
		BoundingBox.x = (CHAR_WIDTH * (log10(score) + 1));
}
