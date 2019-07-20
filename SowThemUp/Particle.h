#ifndef _PARTICLE_H_
#define _PARTICL_H_

#include "Object.h"

class Particle : public Object {
  public:
    Particle(float X, float Y, Color c);
    virtual void update();
    virtual void die();
    virtual void interact(Object * obj);
};

#endif
