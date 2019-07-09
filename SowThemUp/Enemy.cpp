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
  Object::update();
  //burn the trees
  if (Engine::map->getTile(getCenterX(), getCenterY()) == 2) {
    Engine::map->setTile(getCenterX(), getCenterY(), 0);
  }
}
