#ifndef _ENGINE_H_
#define	_ENGINE_H_

#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Maps.h"

#define ENGINE_NUM_OBJECTS 50

class Engine {
  public:
    static float gravity, cameraX, cameraY, cameraTargetX, cameraTargetY;
    static Object *objects[ENGINE_NUM_OBJECTS];
    static TileMap map;

    static void init();
    static void clear();
    static void update();
    static void draw();
    static int addObject(Object* object);
};

#endif // _ENGINE_H_
