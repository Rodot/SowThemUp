#ifndef _ENEMY_H_
#define  _ENEMY_H_

#include "Object.h"
#include "Engine.h"

class Enemy : public Object {
  public:
    Enemy(float X, float Y, float VX, float VY);
    virtual void init();
    virtual void update();
};

#endif // _ENEMY_H_
