#include "Engine.h"
#include <Gamebuino-Meta.h>

//static variables
float Engine::gravity = 0.5;
float Engine::cameraX = 8;
float Engine::cameraY = 8;
float Engine::cameraTargetX = 8;
float Engine::cameraTargetY = 8;
Object* Engine::objects[ENGINE_NUM_OBJECTS];
TileMap Engine::map;

extern const uint8_t map1[];

void Engine::init() {
  addObject(new Player());
  map.load(map1);
}

void Engine::clear() {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    delete objects[i];
    objects[i] = NULL;
  }
}

void Engine::update() {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) continue;
    if (objects[i]->life == 0) continue;
    if (objects[i]->justCreated) continue;
    objects[i]->update();

    //interact with other objects
    for (int j = 0; j < ENGINE_NUM_OBJECTS; j++) {
      if (objects[j] == 0) continue;
      if (objects[j]->life == 0) continue;
      if (objects[j]->justCreated) continue;
      if (i == j) {
        continue;
      }
      if ((objects[i] != 0) && (objects[j] != 0)) {
        objects[i]->interact(objects[j]);
      }
    }
    //kill objects going out of the map
    if (  (objects[i]->x < 0)
          || (objects[i]->y < 0)
          || (objects[i]->x > (map.widthTiles * map.tileSize))
          || (objects[i]->y > (map.heightTiles * map.tileSize))) {
      objects[i]->life = 0;
    }
  }

  //unallocate dead objects
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) continue;
    if (objects[i]->life <= 0) {
      objects[i]->die();
      delete objects[i];
      objects[i] = NULL;
    }
  }

  draw();

  //mark all newly created objects as no longer new
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) continue;
    if (objects[i]->justCreated) {
      objects[i]->justCreated = false;
    }
  }
}

void Engine::draw() {
  cameraX = (cameraX * 7 + cameraTargetX) / 8;
  cameraY = (cameraY * 7 + cameraTargetY) / 8;
  //draw map
  map.draw();
  //draw all objects
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) continue;
    if (objects[i]->justCreated) continue;
    objects[i]->draw();
  }
  //print info
  gb.display.setColor(WHITE);
  /*gb.display.print(gb.getCpuLoad());
    gb.display.print("% ");
    gb.display.print((100 * gb.getFreeRam()) / 32768);
    gb.display.print("% ");
    int num = 0;
    for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] != 0) num++;
    }
    gb.display.print(num);
    gb.display.print("/");
    gb.display.println(ENGINE_NUM_OBJECTS);*/
  gb.display.print("TREES:");
  gb.display.print(Engine::map.getTreeCount());
}

int Engine::addObject(Object * object) {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) {
      objects[i] = object;
      return i; //object created
    }
  }
  delete object;
  return -1; //no more space
}

int Engine::growTree(int x, int y) {
  if (Engine::map.getTile(x, y) == 0) {
    Engine::map.setTile(x, y, 2);
    Engine::addObject(new Particle(x, y, LIGHTGREEN));
    Engine::addObject(new Particle(x, y, LIGHTGREEN));
    Engine::addObject(new Particle(x, y, YELLOW));
  }
}
