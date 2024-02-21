#include "GameEngine.h"
#include <iostream>
#include "PongBall.h"
#include "PlayerController.h"
#include "PadHandler.h"

static GameEngine* _instance;
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVENTS);
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
void ShowSDLVer(){
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    char buffer[sizeof(int) * 8 + 1];
	itoa(compiled.major, buffer, 10);
    std::cout << "compiled on SDL "<<buffer<<".";
    itoa(compiled.minor, buffer, 10);
    std::cout << "linked on SDL "<<buffer <<"\n";
    itoa(linked.major, buffer, 10);
    std::cout <<buffer<<".";
    itoa(linked.minor, buffer, 10);
    std::cout <<buffer <<"\n";
}
void GameEngine::StartLoop()
{
    ShowSDLVer();
    std::cout << "LOOPSTART\n";
    //SDL_Init(SDL_INIT_JOYSTICK);
    ball = new PongBall();
    
    RegisterObject(ball);
    PadInit();
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
    while (true) {
        //std::cout<<"|\n";
        ProcessEvents();
        //std::cout<<"E\n";
        PongInput();
       // std::cout<<"I\n";
        Update();
        // std::cout<<"U\n";
        rendering->RenderFrame();
        // std::cout<<"R\n";
        if (DEBUG_DRAW_BB)
            DrawBBs();
             //std::cout<<"D\n";
        clock->Tick();
        // std::cout<<"T\n";
          //std::cout<<"\n";
        //std::cout << SDL_NumJoysticks()<<"JOYS\n";
        std::cout << "Frame " << clock->GetFrameCount() << " - " << clock->GetFPS() << " - ";
        std::cout << clock->GetBudgetPercent() <<"%  ";
        std::cout << clock->GetRuntimeMS() << "\n";
        //std::cout<<"|\n";
        
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
    // const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // if (keystate[SDL_SCANCODE_W]) {
    //     ball->MovePlayer(true, true);
    // }
    // if (keystate[SDL_SCANCODE_S]) {
    //     ball->MovePlayer(true, false);
    // }
    // if (keystate[SDL_SCANCODE_UP]) {
    //     ball->MovePlayer(false, true);
    // }
    // if (keystate[SDL_SCANCODE_DOWN]) {
    //     ball->MovePlayer(false, false);
    // }


    AllButtons* pads = PadGetInputs();
    for(int i=0;i<2;i++){
        if (pads[i].up){
            ball->MovePlayer(!i,true);
        }
        if(pads[i].down){
            ball->MovePlayer(!i,false);
        }
        if(pads[i].start){
            ball->ResetGame();
            break;
        }
    }
    delete pads;
}
