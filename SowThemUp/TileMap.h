#ifndef _TILEMAP_H_
#define  _TILEMAP_H_
#include <Arduino.h>

class TileMap {
  public:
    //the size of the map in number of tiles
    static const int widthTiles = 10;
    static const int heightTiles = 50;
    //the widht/height of the tiles in number of pixels
    static const int tileSize = 8;
    //stores the map's data
    uint8_t data[10 * 50];

    TileMap();
    void load(const uint8_t* d);
    int getTile(int x, int y);
    void setTile(int x, int y, int t);
    void draw();
    int getTreeCount();
    void update();
};

#endif // _TILEMAP_H_
