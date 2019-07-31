#include "TileMap.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"

const uint16_t wall_data[] = {
  8,      // frame width
  8,      // frame height
  1,      // number of frames
  0,      // animation speed
  0xf81f, // transparent color
  0,      // RGB565 color mode
  // frame 1/1
  0x0000, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x0000,
  0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268,
  0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268,
  0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268,
  0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268,
  0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268,
  0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268,
  0x0000, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x5268, 0x0000
};

Image wall_image(wall_data);

const uint16_t tree_data[] = {
  8,      // frame width
  8,      // frame height
  1,      // number of frames
  0,      // animation speed
  0xf81f, // transparent color
  0,      // RGB565 color mode
  // frame 1/1
  0x0000, 0x0000, 0x044a, 0x044a, 0x044a, 0x044a, 0x0000, 0x0000,
  0x0000, 0x044a, 0x044a, 0x8668, 0x044a, 0x044a, 0x044a, 0x0000,
  0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a,
  0x044a, 0x8668, 0x044a, 0x044a, 0x8668, 0x044a, 0x044a, 0x044a,
  0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a,
  0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a,
  0x0000, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x044a, 0x0000,
  0x0000, 0x0000, 0x044a, 0x044a, 0x044a, 0x044a, 0x0000, 0x0000
};

Image tree_image(tree_data);

const uint16_t lava_data[] = {
  8,      // frame width
  8,      // frame height
  8,      // number of frames
  2,      // animation speed
  0xf81f, // transparent color
  0,      // RGB565 color mode
  // frame 1/8
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4,
  0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  // frame 2/8
  0x0000, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4,
  0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  // frame 3/8
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4,
  0x0000, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  // frame 4/8
  0x0000, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0x0000,
  // frame 5/8
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0x0000,
  0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  // frame 6/8
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4,
  0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  // frame 7/8
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4,
  0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  // frame 8/8
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4,
  0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0xd8e4, 0xd8e4, 0xd8e4, 0xfd42, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4,
  0x0000, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0xd8e4, 0x0000
};

Image lava_image(lava_data);

TileMap::TileMap() {
}

void TileMap::load(const char* d) {
  memcpy(data, d, widthTiles * heightTiles);
  //Spawn enemies
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      int tile = data[i + (j * widthTiles)];
    }
  }
}

void TileMap::draw() {
  int x = Engine::cameraX;
  int y = Engine::cameraY;
  int w = gb.display.width();
  int h = gb.display.height();

  // go through the tiles on screen
  for (int i = 0; i < widthTiles; i++) {
    for (int j = y / tileSize; j <= ((y + h) / tileSize); j++) {
      // skip out-of-map tiles
      if ((j < 0) || (j >= heightTiles)) {
        continue;
      }
      // get tile number
      int tile = data[i + (j * widthTiles)];

      // draw this tile
      if (tile > 0) {
        //if (tile == 1) gb.display.setColor(BROWN);
        //if (tile == 2) gb.display.setColor(GREEN);
        //if (tile == 3) gb.display.setColor(RED);
        //gb.display.drawRect(i * tileSize - (int)Engine::cameraX, j * tileSize - (int)Engine::cameraY, tileSize, tileSize);
        if (tile == 1) gb.display.drawImage(i * tileSize - x, j * tileSize - y, wall_image);
        if (tile == 2) gb.display.drawImage(i * tileSize - x, j * tileSize - y, tree_image);
        if (tile == 3) gb.display.drawImage(i * tileSize - x, j * tileSize - y, lava_image);
      }
      
      //spawn enemies
      if (tile == 4) {
        //remove the enemy tile
        data[i + (j * widthTiles)] = 0;
        //create the enemy object
        Engine::addObject(new Enemy(i * tileSize, j * tileSize));
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
