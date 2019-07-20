#include "Bullet.h"

Bullet::Bullet(float X, float Y, float VX, float VY) {
  x = X;
  y = Y;
  friction = 0.9;
  bounce = 0;
  width = 2;
  height = 2;
  vx = float(random(0, 10) - 5) / 10;
  vy = 7;
  life = 1;
  collideMap = true;
  collideObjects = false;
  justCreated = true;
  y -= vy; //go back one step so the first update is done in the right place
  y += 2 * VY; //offset by the shooter's speed to avoid killing him lol
  color = LIGHTBLUE;
}

void Bullet::update() {
  Object::update();
  //kill it when it stops
  if ((abs(vx) + abs(vy)) < 2) {
    life = 0;
  }
}

void Bullet::die() {
  life = 0;
  //remove the tile with 1 chance out of 3
  if ((random(0, 3) == 0)) {
    Engine::map.setTile(x, y, 0);
  } else {
    //just splash water particles
    Engine::addObject(new Particle(x + 1, y, DARKBLUE));
    Engine::addObject(new Particle(x + 1, y, DARKBLUE));
    Engine::addObject(new Particle(x + 1, y, BLUE));
  }
  //flame particles if it's on fire
  if (Engine::map.getTile(getCenterX(), getCenterY()) == 3) {
    Engine::addObject(new Particle(x + 1, y, ORANGE));
    Engine::addObject(new Particle(x + 1, y, ORANGE));
    Engine::addObject(new Particle(x + 1, y, ORANGE));
    Engine::addObject(new Particle(x + 1, y, ORANGE));
    Engine::addObject(new Particle(x + 1, y, YELLOW));
    Engine::addObject(new Particle(x + 1, y, YELLOW));
  }
}

void Bullet::interact(Object * obj) {
  if (!life) return;
  if (!obj->collideObjects) return;  // skip objects which don't collide
  if (colliding(obj)) {  // if the bullet hits an object
    obj->life -= 4;  // reduce the object's life
    life = 0;  // remove the bullet
    return;
  }
}
