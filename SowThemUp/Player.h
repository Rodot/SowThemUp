#ifndef _PLAYER_H_
#define  _PLAYER_H_

#include "Object.h"
#include "Engine.h"
#include "Bullet.h"

class Player : public Object {
  public:
    Player();
    virtual void init();
    virtual void die();
    virtual void update();
};

#endif // _PLAYER_H_
