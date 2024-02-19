#include "RenderEngine.h"
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <algorithm>
static RenderEngine* _instance;
RenderEngine* RenderEngine::GetInstance()
{
    if (_instance == nullptr)
        _instance = new RenderEngine();
    return _instance;
}
RenderEngine::RenderEngine()
{
    clock = GameClock::GetInstance();
    
    SDL_GetDesktopDisplayMode(0, &mode);
    window = SDL_CreateWindow("Jonathan Richards -- 26541501", mode.w /4, mode.h / 4, 800, 600, SDL_WINDOW_RESIZABLE);
    renderContext = SDL_CreateRenderer(window, -1, 0);
    TTF_Init();
}

RenderEngine::~RenderEngine()
{
    
}

SDL_Window* RenderEngine::GetWindow()
{
    return window;
}

SDL_Renderer* RenderEngine::GetRenderContext()
{
    return renderContext;
}

void RenderEngine::RenderFrame()
{
    SDL_SetRenderDrawColor(renderContext, 0, 0, 0, 0); //backg colour
    SDL_RenderClear(renderContext);
    // test code
    /*
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle = {50,50,100,100};
    SDL_RenderDrawRect(renderer, &rectangle);
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderDrawLine(renderer, 200, 100, 200, 500);
    */
    std::sort(RenderQueue.begin(),RenderQueue.end(), [](auto a, auto b){return *a < *b;});
    for (RenderableComponent* c : RenderQueue) {
        SDL_RenderCopy(renderContext, c->GetTexture(), c->GetSourcePos(), c->GetDestPos());
    }
    RenderQueue.clear();
    SDL_RenderPresent(renderContext);
}

void RenderEngine::ToggleFullscreen()
{
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) 
        SDL_SetWindowFullscreen(window, 0);
    else 
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void RenderEngine::Enqueue(RenderableComponent* object)
{
    RenderQueue.push_back(object);
}


