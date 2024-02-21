#include <iostream>
#include "GameEngine.h"
#include "PongBall.h"
int main(int argc, char* args[])
{
    std::cout << "Hello World!\n";
    GameEngine* engine = GameEngine::GetInstance();
    
    std::cout << SDL_NumJoysticks();
    engine->StartLoop();
    return 0;
}