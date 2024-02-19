#ifndef USE_GAMECLOCK
#define USE_GAMECLOCK
#include <chrono>
#include "Global_Flags.h"
using namespace std::chrono_literals;
class GameClock
{
public:
	static GameClock* GetInstance();
	void Tick();
	std::chrono::nanoseconds GetFrametime();
	long long GetFrameCount();
	float GetBudgetPercent();
	std::chrono::high_resolution_clock::time_point GetTimePoint();
	int GetFPS();
	void SetFPSLimit(int fps);
private:
	GameClock();
	~GameClock();
	
	const std::chrono::high_resolution_clock::time_point ENGINE_START_TP;
	std::chrono::high_resolution_clock::time_point last_frame_tp;

	std::chrono::nanoseconds frametime_ns;
	std::chrono::nanoseconds unused_ns;
	std::chrono::nanoseconds target_ns;

	long long framecounter;
	std::chrono::nanoseconds GetRemainingBudget();
	void EnforceLimit();
	std::chrono::nanoseconds TimeSinceLastFrame();
	void WaitFor(std::chrono::nanoseconds wait_ns);
};
#endif // !USE_GAMECLOCK

