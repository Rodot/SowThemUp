#ifndef _TILEMAP_H_
#define  _TILEMAP_H_
#include <Arduino.h>



class TileMap {
  public:
    uint8_t *data;
    void draw();
    int tileSize; //the widht/height of the tiles in number of pixels
    int widthTiles, heightTiles; //the size of the map in number of tiles
    int getTreeCount();

    TileMap();
    void load(const uint8_t* d);
    int getTile(int x, int y);
    void setTile(int x, int y, int t);
};

#endif // _TILEMAP_H_
