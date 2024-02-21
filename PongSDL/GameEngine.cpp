#include "GameEngine.h"
#include <iostream>
#include "PongBall.h"
#include "PlayerController.h"
static GameEngine* _instance;
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    clock = GameClock::GetInstance();
    rendering = RenderEngine::GetInstance(); 
    clock->SetFPSLimit(FRAME_CAP);
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
    std::cout << "LOOSTART\n";
    //SDL_Init(SDL_INIT_JOYSTICK);
    ball = new PongBall();
    
    RegisterObject(ball);
    SDL_Joystick* joy;
    joy = SDL_JoystickOpen(0);
    std::cout <<SDL_GetError()<<"\n";
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
                MoveStatics();
                break;
            case SDLK_ESCAPE:
                ENGINE_QUIT_FLAG = true;
                break;
            case SDLK_F10:
                clock->SetFPSLimit(FRAME_CAP);
                break;
            case SDLK_F9:
                clock->SetFPSLimit(0);
                break;
            case SDLK_SPACE:
                ball->ResetGame();
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

void GameEngine::MoveStatics(){
    for (GameObject* g : UpdateQueue) {
        if(g->GetStaticStatus())
            g->MoveVisuals();
    }
}

void GameEngine::GameLoop() {
    while (!ENGINE_QUIT_FLAG) {
        ProcessEvents();
        PongInput();
        Update();
        rendering->RenderFrame();
        if (DEBUG_DRAW_BB)
            DrawBBs();
        clock->Tick();
        std::cout << SDL_NumJoysticks()<<"JOYS\n";
        std::cout << "Frame " << clock->GetFrameCount() << " - " << clock->GetFPS() << " - ";
        std::cout << clock->GetBudgetPercent() << "%\n";
        
    }
    SDL_Quit(); //do this after so no null accesses - it still happens oh well
}

void GameEngine::DrawBBs()
{
    SDL_Renderer* renderContext = rendering->GetRenderContext();
    SDL_SetRenderDrawColor(renderContext, 255, 0, 0, 255);
    for (GameObject* g : UpdateQueue) {
        g->DrawBoundingBox();
    }
    SDL_RenderPresent(renderContext);
}

void GameEngine::PongInput()
{
 /*    case SDLK_w:
         ball->MovePlayer(true, true);
         break;
     case SDLK_s:
         ball->MovePlayer(true, false);
         break;
     case SDLK_UP:
         ball->MovePlayer(false, true);
         break;
     case SDLK_DOWN:
         ball->MovePlayer(false, false);
         break;*/
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W]) {
        ball->MovePlayer(true, true);
    }
    if (keystate[SDL_SCANCODE_S]) {
        ball->MovePlayer(true, false);
    }
    if (keystate[SDL_SCANCODE_UP]) {
        ball->MovePlayer(false, true);
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        ball->MovePlayer(false, false);
    }
}
