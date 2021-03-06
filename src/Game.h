#pragma once

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class AssetManager;
class ColliderComponent;
class Entity;

extern Entity &player;

extern int score;
extern int health;
extern std::vector<Entity *> &enemies;

class Game {
    
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void displayScore();
    bool running() { return isRunning; }
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager *assets;
    static std::string path;
    
    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayerProjectiles,
        groupProjectiles,
        groupEnemies,
        groupColliders,
        groupPlayers
        
        
    };
    
    enum PType
    {
        playerT,
        playerFlameT,
        enemyBasicT,
        enemyGeneralT
    };
    
private:
    SDL_Window *window;
    
    template<typename T> bool inView(Entity *t);
};
