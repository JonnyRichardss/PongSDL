#ifndef USE_ENGINE
#define USE_ENGINE
#include "SDL.h"
#include "GameClock.h"
#include "RenderEngine.h"
#include "GameObject.h"
#include <vector>
#include "Global_Flags.h"
class PongBall;
class GameEngine
{
public:
	static GameEngine* GetInstance();
	void StartLoop();
	void RegisterObject(GameObject* g);
private:
	GameEngine();
	~GameEngine();
	bool ENGINE_QUIT_FLAG = false;
	PongBall* ball;
	RenderEngine* rendering;
	GameClock* clock;
	std::vector<GameObject*> UpdateQueue;
	void ProcessEvents();
	void Update();
	void MoveStatics();
	void GameLoop();
	void DrawBBs();
	void PongInput();
};
#endif // !USE_ENGINE
