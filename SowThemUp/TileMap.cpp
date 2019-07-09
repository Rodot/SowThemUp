#include "TileMap.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"

// 0 == FLOOR
// 1 == WALL
// 2 == TREE
// 3 == FIRE

int myMap[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 2, 0, 0, 0, 1,
  1, 0, 0, 2, 2, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 3, 3, 3, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 2, 2, 0, 0, 1,
  1, 0, 0, 1, 1, 1, 2, 2, 0, 1,
  1, 0, 0, 0, 0, 2, 2, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 2, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 3, 0, 2, 1,
  1, 0, 0, 0, 2, 1, 3, 2, 2, 1,
  1, 0, 0, 0, 1, 0, 3, 1, 2, 1,
  1, 0, 0, 1, 0, 0, 3, 0, 1, 1,
  1, 0, 0, 0, 0, 0, 3, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 3, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 3, 3, 3, 3, 3, 3, 3, 3, 1,
  1, 3, 3, 3, 3, 3, 3, 3, 3, 1,
  1, 3, 3, 3, 3, 3, 3, 3, 3, 1,
  1, 3, 3, 3, 3, 3, 3, 3, 3, 1,
  1, 3, 3, 3, 3, 3, 3, 3, 3, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

TileMap::TileMap() {
  data = myMap;
  widthTiles = 10;
  heightTiles = 50;
  tileWidth = 8;
  tileHeight = 8;
}

void TileMap::draw() {
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      int tile = data[i + (j * widthTiles)];
      if (tile > 0) {
        if(tile == 1) gb.display.setColor(BROWN);
        if(tile == 2) gb.display.setColor(GREEN);
        if(tile == 3) gb.display.setColor(RED);
        gb.display.drawRect(i * tileWidth - (int)Engine::cameraX, j * tileHeight - (int)Engine::cameraY, tileWidth, tileHeight);
      }
    }
  }
}

int TileMap::getTile(int x, int y) {
  int i = x / tileWidth;
  int j = y / tileHeight;
  if ((i < 0) || (i > widthTiles) || (j < 0) || (j > heightTiles)) {
    return -1;
  }
  return data[i + (j * widthTiles)];
}

void TileMap::setTile(int x, int y, int t) {
  int i = x / tileWidth;
  int j = y / tileHeight;
  if ((i < 0) || (i > widthTiles) || (j < 0) || (j > heightTiles)) {
    return;
  }
  data[i + (j * widthTiles)] = t;
}

int TileMap::getTreeCount(){
  int treeCount = 0;
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      int tile = data[i + (j * widthTiles)];
      if(tile == 2) {
        treeCount++;
      }
    }
  }
  return treeCount;
}
