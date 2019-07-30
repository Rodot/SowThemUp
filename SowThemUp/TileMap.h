#ifndef _TILEMAP_H_
#define  _TILEMAP_H_
#include <Arduino.h>

class TileMap {
  public:
    //the size of the map in number of tiles
    static const int widthTiles = 12;
    static const int heightTiles = 150;
    //the widht/height of the tiles in number of pixels
    static const int tileSize = 8;
    //stores the map's data
    char data[widthTiles * heightTiles];

    TileMap();
    void load(const char* d);
    int getTile(int x, int y);
    void setTile(int x, int y, int t);
    void draw();
    int getTreeCount();
    void update();
};

#endif // _TILEMAP_H_
