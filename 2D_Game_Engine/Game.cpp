#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

auto &player(manager.addEntity());
auto &wall(manager.addEntity());
//
//auto &tile0(manager.addEntity());
//auto &tile1(manager.addEntity());
//auto &tile2(manager.addEntity());


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized..." << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if (window)
        {
            std::cout << "window created!" << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, flags);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    }
    map = new Map();
    
    //ecs system
//
//    tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
//    tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
//    tile1.addComponent<ColliderComponent>("dirt");
//    tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
//    tile2.addComponent<ColliderComponent>("grass");

    
    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("/Users/yuqiliu/Documents/Dev/2D_Game_Engine/2D_Game_Engine/assets/dragon.png");
    
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    
    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("/Users/yuqiliu/Documents/Dev/2D_Game_Engine/2D_Game_Engine/assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{
    
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    manager.refresh();
    manager.update();
    
    for (auto cc : colliders) {
//        if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
//        {
////            player.getComponent<TransformComponent>().scale = 1;
//            player.getComponent<TransformComponent>().velocity * -1;
//            std::cout << "Wall Hit!" << std::endl;
//        }
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    }
    
    
//    std::cout << player.getComponent<TransformComponent>().position << std::endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);
//    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

void Game::AddTile(int ID, int x, int y)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, ID);
}