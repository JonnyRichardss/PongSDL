#include "GameObject.h"
#include "GameEngine.h"
GameObject::GameObject()
{
	shown = true;
	visuals = new RenderableComponent();
	renderer = RenderEngine::GetInstance();
	engine = GameEngine::GetInstance();
	clock = GameClock::GetInstance();
	window = renderer->GetWindow();
	renderContext = renderer->GetRenderContext();
	GetWindowParams();
}

GameObject::~GameObject()
{
	delete visuals;
}
Vector2 GameObject::GameToWindowCoords(Vector2 GameCoords)
{
	//INVERT Y AXIS
	GameCoords.y *= -1;
	//TRANSFORM VECTOR INTO +VE +VE
	GameCoords += Vector2(GAME_MAX_X, GAME_MAX_Y);
	//SCALE VECTOR
	GameCoords = GameToWindowScaling(GameCoords);

	return GameCoords;
}
Vector2 GameObject::GameToWindowScaling(Vector2 vec) {
	float ScaleFacX, ScaleFacY;
	if (GAME_MAX_X > windowWidth)
		ScaleFacX = (float)GAME_MAX_X / (float)windowWidth;
	else
		ScaleFacX = (float)windowWidth / (float)GAME_MAX_X;

	if (GAME_MAX_Y > windowHeight)
		ScaleFacY = (float)GAME_MAX_Y / (float)windowHeight;
	else
		ScaleFacY = (float)windowHeight / (float)GAME_MAX_Y;
	vec.x *= ScaleFacX / 2.0f;
	vec.y *= ScaleFacY / 2.0f;
	return vec;
}
SDL_Rect GameObject::BBtoDestRect()
{
	Vector2 TransformedPos(position.x - (BoundingBox.x / 2.0f), position.y + (BoundingBox.y / 2.0f));
	TransformedPos = GameToWindowCoords(TransformedPos);
	Vector2 TransformedBB = GameToWindowScaling(BoundingBox);
	SDL_Rect dest = { TransformedPos.x,TransformedPos.y,TransformedBB.x,TransformedBB.y };
	return dest;
}
void GameObject::GetWindowParams()
{
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}
bool GameObject::UpdateAndRender(RenderableComponent*& render)
{
	GetWindowParams();
	Update();
	
	if (shown) {
		if (!is_static)
			MoveVisuals();
		render = visuals;
		return true;
	}
	else 
		return false;

}

void GameObject::Hide()
{
	shown = false;
}

void GameObject::Show()
{
	shown = true;
}

void GameObject::ToggleVisibility()
{
	shown = shown ? false : true;
}

void GameObject::DrawBoundingBox()
{
	
	SDL_Rect BBrect = BBtoDestRect();
	Vector2 WindowPos = GameToWindowCoords(position);
	//SDL_Rect PosRect = {WindowPos.x,WindowPos.y,5,5};
	SDL_RenderDrawRect(renderContext, &BBrect);
	//SDL_RenderDrawRect(renderContext, &PosRect);
	SDL_RenderDrawPoint(renderContext, WindowPos.x, WindowPos.y);
}

Vector2 GameObject::GetPos()
{
	return position;
}

Vector2 GameObject::GetBB()
{
	return BoundingBox;
}

void GameObject::MoveVisuals()
{
	SDL_Rect pos = BBtoDestRect();
	
	visuals->UpdateDestPos(&pos);
}

