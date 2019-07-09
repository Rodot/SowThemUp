#include "Bullet.h"

Bullet::Bullet(float X, float Y, float VX, float VY) {
  Object::init();
  x = X;
  y = Y;
  width = 2;
  height = 2;
  vx = float(random(0, 10) - 5) / 10;
  vy = 5;
  life = 1;
  collideMap = true;
  collideObjects = false;
  y -= vy; //go back one step so the first update is done in the right place
  y += 2 * VY; //offset by the shooter's speed to avoid killing him lol
  color = BLUE;
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
  Engine::addObject(new Particle(x + 1, y , vx, vy, 1, 1, true));
  Engine::addObject(new Particle(x + 1, y , vx, vy, 1, 1, true));
  Engine::addObject(new Particle(x + 1, y , vx, vy, 1, 1, true));
}

void Bullet::updatePhysics() {
    vx *= 0.95;
    vy *= 0.95;
}

void Bullet::interact(Object * obj) {
  if (!life) return;
  if(!obj->collideObjects) return;
  if (colliding(obj)) {
    obj->life -= 3;
    life = 0;
    return;
  }
}
