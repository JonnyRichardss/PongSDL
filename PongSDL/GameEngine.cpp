#include "GameEngine.h"
#include <iostream>
#include "PongBall.h"
static GameEngine* _instance;
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    clock = GameClock::GetInstance();
    rendering = RenderEngine::GetInstance(); 
    clock->SetFPSLimit(GF_FRAME_CAP);
}

GameEngine::~GameEngine()
{
}

GameEngine* GameEngine::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameEngine();
    return _instance;
}

void GameEngine::StartLoop()
{
    PongBall* ball = new PongBall();
    RegisterObject(ball);
    GameLoop();
}

void GameEngine::RegisterObject(GameObject* g)
{
    UpdateQueue.push_back(g);
    g->Init();
    g->InitVisuals();
}

void GameEngine::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_F11:
                rendering->ToggleFullscreen();
                break;
            case SDLK_ESCAPE:
                ENGINE_QUIT_FLAG = true;
                break;
            case SDLK_F10:
                clock->SetFPSLimit(GF_FRAME_CAP);
                break;
            case SDLK_F9:
                clock->SetFPSLimit(0);
                break;
            case SDLK_F8:
                break;
            }
        }
        if (event.type == SDL_QUIT) {
            ENGINE_QUIT_FLAG = true;
        }
    }
}

void GameEngine::Update()
{
    for (GameObject* g : UpdateQueue) {
        RenderableComponent* newComponent = nullptr;
        if (g->UpdateAndRender(newComponent)) {
            rendering->Enqueue(newComponent);
        }
    }
}



void GameEngine::GameLoop() {
    while (!ENGINE_QUIT_FLAG) {
        ProcessEvents();
        Update();
        rendering->RenderFrame();
        clock->Tick();
        std::cout << "Frame " << clock->GetFrameCount() << " - " << clock->GetFPS() << " - ";
        std::cout << clock->GetBudgetPercent() << "%\n";
    }
    SDL_Quit(); //do this after so no null accesses - it still happens oh well
}