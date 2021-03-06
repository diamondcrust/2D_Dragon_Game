#pragma once
#include <string>

class Map
{
public:
    
    int mapW;
    int mapH;
    static int scaledSize;
    
    Map(std::string tID, int ms, int ts);
    ~Map();
    
    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);
    
private:
    std::string texID;
    int tileSize;
    int mapScale;
};
