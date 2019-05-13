#include <iostream>
#include "Game.h"

Game *game = nullptr;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
label:
    game = new Game();
    
    game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    
    while (game->running())
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        if (enemies.size() == 0 || health <= 0)
        {
            Game::isRunning = false;
        }
    }
    game->displayScore();
    
    SDL_Event e;
    do
    {
        if (SDL_WaitEvent(&e) != 1) std::cout << "Error Waiting for Event!" << std::endl;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
    }
    while (e.type != SDL_QUIT); // e.type != SDL_KEYDOWN && 
    
    
    game->clean();
    
    return 0;
}
