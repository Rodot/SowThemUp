#include "Enemy.h"
#include <Gamebuino-Meta.h>

Enemy::Enemy(float X, float Y) {
  init();
  x = X;
  y = Y;
}

void Enemy::init() {
  vx = 0.5;
  vy = 0;
  width = 6;
  height = 6;
  friction = 1;
  bounce = 1;
  life = 10;
  collideMap = true;
  collideObjects = true;
  justCreated = true;
  color = ORANGE;
}

void Enemy::update() {
  //move only if on screen
  if (y < (Engine::cameraY + gb.display.height())) {
    Object::update();
    //burn the trees
    if (Engine::map.getTile(getCenterX(), getCenterY()) == 2) {
      Engine::map.setTile(getCenterX(), getCenterY(), 0);
    }
  }
}

void Enemy::interact(Object * obj) {
  if (!life) return;
  if (!obj->collideObjects) return;
  if (colliding(obj)) {
    obj->life -= 10;
    life = 0;
    return;
  }
}

void Enemy::die() {
  //particle effects
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , YELLOW));
  Engine::addObject(new Particle(x, y , YELLOW));
}
