#include "Engine.h"
#include <Gamebuino-Meta.h>

//static variables
float Engine::gravity = 0.5;
float Engine::cameraX = 8;
float Engine::cameraY = 8;
float Engine::cameraTargetX = 8;
float Engine::cameraTargetY = 8;
boolean Engine::won = false;
boolean Engine::gameOver = false;
Object* Engine::objects[ENGINE_NUM_OBJECTS];
TileMap Engine::map;
extern const char map1[];

void Engine::init() {
  addObject(new Player());
  map.load(map1);
  won = false;
  gameOver = false;
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

  gb.display.setColor(WHITE);
  gb.display.print("TREES:");
  gb.display.print(Engine::map.getTreeCount());

  if (gameOver == true) {
    drawGameOver();
  }

  if (won == true) {
    drawWon();
  }

  //print info
  gb.display.setCursor(0,59);
  gb.display.print(gb.getCpuLoad());
  gb.display.print("%CPU ");
  gb.display.print((100 * gb.getFreeRam()) / 32768);
  gb.display.print("%MEM ");
  int num = 0;
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] != 0) num++;
  }
  gb.display.print(num);
  gb.display.print("/");
  gb.display.println(ENGINE_NUM_OBJECTS);
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

void Engine::drawGameOver() {
  int numberOfTrees = Engine::map.getTreeCount();

  //draw the background rectangle
  gb.display.setColor(BLACK);
  gb.display.fillRect(0, 24, 80, 40);
  gb.display.setColor(RED);
  gb.display.drawRect(0, 24, 80, 40);

  //print the big title
  gb.display.setCursor(2, 26);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.print("OH NO!\n");

  //print the text
  gb.display.setFontSize(1);
  gb.display.setColor(WHITE);
  gb.display.print(" YOU SAVED ");
  gb.display.print(numberOfTrees);
  gb.display.print(" TREES\n BEFORE YOU PERISHED\n TRY AGAIN!");
}

void Engine::drawWon() {
  int numberOfTrees = Engine::map.getTreeCount();

  //draw the background rectangle
  gb.display.setColor(BLACK);
  gb.display.fillRect(0, 24, 80, 40);
  gb.display.setColor(LIGHTGREEN);
  gb.display.drawRect(0, 24, 80, 40);

  //print the big title
  gb.display.setCursor(2, 26);
  gb.display.setFontSize(2);
  gb.display.setColor(LIGHTGREEN);
  gb.display.print("WELL DONE\n");

  //print the text
  gb.display.setFontSize(1);
  gb.display.setColor(WHITE);
  gb.display.print(" YOU SAVED ");
  gb.display.print(numberOfTrees);
  gb.display.print(" TREES\n");

  if (numberOfTrees > 100) {
    gb.display.print(" THEY ABSORB THE CO2\n IT STOPS THE\n GLOBAL WARMING.\n YOU DIT IT!");
  } else if (numberOfTrees > 50) {
    gb.display.print(" GLOBAL WARMING\n HAS SLOWED DOWN\n YOU CAN DO BETTER!");
  } else {
    gb.display.print(" YOU CAN DO BETTER\n TO SAVE THE PLANET\n FROM GLOBAL WARMING");
  }

}
