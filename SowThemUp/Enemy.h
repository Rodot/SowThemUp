#ifndef _ENEMY_H_
#define  _ENEMY_H_

#include "Object.h"

class Enemy : public Object {
  public:
    Enemy(float X, float Y, float VX, float VY);
    virtual void init();
};

#endif // _ENEMY_H_
