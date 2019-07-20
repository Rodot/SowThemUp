#ifndef _OBJECT_H_
#define  _OBJECT_H_

#include <Arduino.h>
#include <Gamebuino-Meta.h>

class Object {
  public:
    float x, y, vx, vy, width, height, friction, bounce;
    int life;
    bool collideMap, collideObjects, justCreated;
    Color color;

    Object();
    virtual void init();
    virtual void update();
    virtual void die();
    virtual int collideMapX();
    virtual int collideMapY();
    virtual void interact(Object* obj);
    virtual void draw();
    int collidingTile();
    int colliding(Object* obj);
    float getCenterX();
    float getCenterY();
};

#endif // _OBJECT_H_
