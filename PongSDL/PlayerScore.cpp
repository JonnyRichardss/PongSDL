#include "PlayerScore.h"

void PlayerScore::Init()
{

	shown = true;
	is_static = true;
	velocity = Vector2::zero();
	BoundingBox = Vector2(CHAR_WIDTH, CHAR_HEIGHT);


}

void PlayerScore::InitVisuals()
{

	TTF_Init();
	scoreFont = TTF_OpenFont("USN_STENCIL.TTF", CHAR_HEIGHT);
	visuals->UpdateLayer(100);
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
	char buffer[sizeof(int) * 8 + 1];
	itoa(score, buffer, 10);
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderContext, TTF_RenderUTF8_LCD_Wrapped(scoreFont, buffer, { 255,255,255,255 }, { 0,0,0,0 }, 0));
	visuals->UpdateTexture(scoreTexture);
	if (score == 0)
		BoundingBox.x = CHAR_WIDTH;
	else
		BoundingBox.x = (CHAR_WIDTH * (log10(score) + 1));
}
