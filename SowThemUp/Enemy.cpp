#include "Enemy.h"
#include <Gamebuino-Meta.h>
#include "Toolbox.h"

Enemy::Enemy(float X, float Y, float VX, float VY) {
  init();
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
}

void Enemy::init() {
  Object::init();
  color = ORANGE;
  friction = 1;
  bounce = 1;
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
