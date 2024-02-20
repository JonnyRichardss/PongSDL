#ifndef USE_GAMEOBJECT
#define USE_GAMEOBJECT
#include "RenderableComponent.h"
#include "RenderEngine.h"
#include "GameMath.h"
#include "GameClock.h"
#include "ColourRGBA.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	
	bool UpdateAndRender(RenderableComponent*& render);
	
	void Hide();
	void Show();
	void ToggleVisibility();
	
	virtual void Init() = 0;
	virtual void InitVisuals() = 0;
protected:
	int windowWidth, windowHeight;
	Vector2 position;
	Vector2 velocity;
	virtual void MoveVisuals() = 0;
	virtual void Update() = 0;
	void GetWindowParams();
	
	bool shown;
	RenderEngine* renderer;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderContext;
	RenderableComponent* visuals;
};
#endif // !USE_GAMEOBJECT

