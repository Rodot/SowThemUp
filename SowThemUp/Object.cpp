#include "Object.h"

#include "Engine.h"
#include "Toolbox.h"

Object::Object() {
  init();
}

Object::Object(float X, float Y, float W, float H, float VX, float VY) {
  init();
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
  width = W;
  height = H;
}

void Object::init() {
  x = 8;
  y = 8;
  vx = 0;
  vy = 0;
  width = 6;
  height = 6;
  friction = 0.9;
  bounce = 0;
  life = 10;
  collideMap = true;
  collideObjects = true;
  justCreated = true;
  color = RED;
}

void Object::die() {
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , YELLOW));
  Engine::addObject(new Particle(x, y , YELLOW));
}

void Object::update() {
  updatePhysics();

  //limit speeds
  vx = constrain(vx, -7, 7);
  vy = constrain(vy, -7, 7);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  x += vx;
  collideMapX();

  y += vy;
  collideMapY();


}

void Object::updatePhysics() {
  vx *= friction;
  vy *= friction;
}

int Object::collideMapX() {
  if (collideMap) {
    if (vx > 0) {
      if ((Engine::map.getTile(x + width, y) == 1) || (Engine::map.getTile(x + width, y + height) == 1)) {
        int tileX = (((int)(x + width) / (int)Engine::map.tileSize) * (int)Engine::map.tileSize);
        x = tileX - width - 0.01;
        vx *= - bounce;
        return 1;
      }
    }
    else {
      if ((Engine::map.getTile(x, y) == 1) || (Engine::map.getTile(x, y + height) == 1)) {
        int tileX = (((int)x / (int)Engine::map.tileSize) * (int)Engine::map.tileSize);
        x = tileX + Engine::map.tileSize + 0.01;
        vx *= - bounce;
        return 1;
      }
    }
  }
  //Loose life when touching fire
  if(Engine::map.getTile(getCenterX(), getCenterY()) == 3){
    life --;
  }
  return 0;
}

int Object::collideMapY() {
  if (collideMap) {
    if (vy > 0) {
      if ((Engine::map.getTile(x, y + height) == 1) || (Engine::map.getTile(x + width, y + height) == 1)) {
        int tileY = (((int)(y + height) / (int)Engine::map.tileSize) * (int)Engine::map.tileSize);
        y = tileY - height - 0.01;
        vy *= - bounce;
        return 1;
      }
    } else {
      if ((Engine::map.getTile(x, y) == 1) || (Engine::map.getTile(x + width, y) == 1)) {
        int tileY = (((int)y / (int)Engine::map.tileSize) * (int)Engine::map.tileSize);
        y = tileY + Engine::map.tileSize + 0.01;
        vy *= - bounce;
        return 1;
      }
    }
  }
  //Loose life when touching fire
  if(Engine::map.getTile(getCenterX(), getCenterY()) == 3){
    life --;
  }
  return 0;
}

void Object::interact(Object * obj) {
}

void Object::draw() {
  gb.display.setColor(color);
  gb.display.drawRect((int)(x + 0.05) - (int)Engine::cameraX, (int)(y + 0.05) - (int)Engine::cameraY, width, height);
}

int Object::collidingTile() {
  int tile = -1;
  int temp = Engine::map.getTile(x, y);
  if (temp > tile) tile = temp;
  temp = Engine::map.getTile(x + width, y);
  if (temp > tile) tile = temp;
  temp = Engine::map.getTile(x, y + height);
  if (temp > tile) tile = temp;
  temp = Engine::map.getTile(x + width, y + height);
  if (temp > tile) tile = temp;
  return tile;
}

int Object::colliding(Object * obj) {
  return collideRectRect(x, y, width, height, obj->x, obj->y, obj->width, obj->height);
}

float Object::getCenterX() {
  return (x + width / 2);
}

float Object::getCenterY() {
  return (y + height / 2);
}
