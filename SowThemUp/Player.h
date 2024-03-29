#ifndef _PLAYER_H_
#define  _PLAYER_H_

#include "Object.h"
#include "Engine.h"
#include "Bullet.h"

class Player : public Object {
  public:
    Player();
    void init();
    void die();
    void update();
    virtual void interact(Object* obj);
    int specialCooldown;
};

#endif // _PLAYER_H_
