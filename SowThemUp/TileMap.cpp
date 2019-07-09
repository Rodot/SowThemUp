#include "TileMap.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"

TileMap::TileMap() {
}

void TileMap::load(const uint8_t* d) {
  memcpy(data, d, widthTiles * heightTiles);
  //Spawn enemies
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      int tile = data[i + (j * widthTiles)];
      if (tile == 4) {
        //create the enemy
        Engine::addObject(new Enemy(i * tileSize, j * tileSize, 0.2, 0));
        //remove the tile
        data[i + (j * widthTiles)] = 0;
      }
    }
  }
}

void TileMap::draw() {
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      int tile = data[i + (j * widthTiles)];
      if (tile > 0) {
        if (tile == 1) gb.display.setColor(BROWN);
        if (tile == 2) gb.display.setColor(GREEN);
        if (tile == 3) gb.display.setColor(RED);
        gb.display.drawRect(i * tileSize - (int)Engine::cameraX, j * tileSize - (int)Engine::cameraY, tileSize, tileSize);
      }
    }
  }
}

int TileMap::getTile(int x, int y) {
  int i = x / tileSize;
  int j = y / tileSize;
  if ((i < 0) || (i > widthTiles) || (j < 0) || (j > heightTiles)) {
    return -1;
  }
  return data[i + (j * widthTiles)];
}

void TileMap::setTile(int x, int y, int t) {
  int i = x / tileSize;
  int j = y / tileSize;
  if ((i < 0) || (i > widthTiles) || (j < 0) || (j > heightTiles)) {
    return;
  }
  data[i + (j * widthTiles)] = t;
}

int TileMap::getTreeCount() {
  int treeCount = 0;
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      int tile = data[i + (j * widthTiles)];
      if (tile == 2) {
        treeCount++;
      }
    }
  }
  return treeCount;
}
