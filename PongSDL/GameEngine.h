#ifndef USE_ENGINE
#define USE_ENGINE
#include "SDL.h"
#include "GameClock.h"
#include "RenderEngine.h"
#include "GameObject.h"
#include <vector>
#include "Global_Flags.h"
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
	
	RenderEngine* rendering;
	GameClock* clock;
	std::vector<GameObject*> UpdateQueue;
	void ProcessEvents();
	void Update();
	void GameLoop();
};
#endif // !USE_ENGINE
