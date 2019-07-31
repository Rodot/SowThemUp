#include "Bullet.h"

Bullet::Bullet(float X, float Y, float VX, float VY) {
  width = 2;
  height = 2;
  x = X - width / 2;
  y = Y - height / 2;
  friction = 0.9;
  bounce = 0;
  vx = VX;
  vy = VY;
  life = 1;
  collideMap = true;
  collideObjects = false;
  justCreated = true;
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

  //just splash water particles
  Engine::addObject(new Particle(x + 1, y, BLUE));
  Engine::addObject(new Particle(x + 1, y, DARKBLUE));
  Engine::addObject(new Particle(x + 1, y, DARKBLUE));

  //if it's a tree
  if (Engine::map.getTile(x, y) == 2) {
    int s = Engine::map.tileSize;
    //if the space is empty, grow a tree
    Engine::growTree(x + s, y);
    Engine::growTree(x - s, y);
    Engine::growTree(x, y + s);
    Engine::growTree(x, y - s);
  }
}

void Bullet::interact(Object * obj) {
  if (!life) return;
  if (!obj->collideObjects) return;  // skip objects which don't collide
  if (colliding(obj)) {  // if the bullet hits an object
    obj->life -= 10;  // reduce the object's life
    life = 0;  // remove the bullet
    return;
  }
}
