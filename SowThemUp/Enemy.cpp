#include "Enemy.h"
#include <Gamebuino-Meta.h>

const uint16_t enemy_data[] = {
  6,      // frame width
  6,      // frame height
  4,      // number of frames
  0,      // animation speed
  0xf81f, // transparent color
  0,      // RGB565 color mode
  0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42,
  0xfd42, 0x0000, 0x0000, 0x0000, 0x0000, 0xfd42,
  0xfd42, 0x0000, 0x0000, 0x0000, 0x0000, 0xfd42,
  0xfd42, 0x0000, 0x0000, 0x0000, 0x0000, 0xfd42,
  0xfd42, 0x0000, 0x0000, 0x0000, 0x0000, 0xfd42,
  0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42,
};

Image enemy_image(enemy_data);

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
  image = &enemy_image;
}

void Enemy::update() {
  //move only if on screen
  if (y < (Engine::cameraY + gb.display.height())) {
    Object::update();
    //burn the trees
    if (Engine::map.getTile(getCenterX(), getCenterY()) == 2) {
      Engine::map.setTile(getCenterX(), getCenterY(), 0);
      //fire particle effect
      Engine::addObject(new Particle(x, y , ORANGE));
      Engine::addObject(new Particle(x, y , ORANGE));
      Engine::addObject(new Particle(x, y , ORANGE));
      Engine::addObject(new Particle(x, y , YELLOW));
      Engine::addObject(new Particle(x, y , YELLOW));
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
