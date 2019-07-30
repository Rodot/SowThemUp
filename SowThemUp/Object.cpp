#include "Object.h"
#include "Engine.h"

Object::Object() {
  init();
}

void Object::init() {
  image = 0;
  //all fields to be set the the child class' init
  /*
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    width = 8;
    height = 8;
    friction = 1;
    bounce = 0;
    life = 10;
    collideMap = true;
    collideObjects = true;
    justCreated = true;
    color = PINK;
  */
}

void Object::update() {
  //reduce speed due to air friction
  vx *= friction;
  vy *= friction;

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

void Object::die() {
  //do nothing
}

void Object::interact(Object * obj) {
  // do nothing
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
  if (Engine::map.getTile(getCenterX(), getCenterY()) == 3) {
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
  if (Engine::map.getTile(getCenterX(), getCenterY()) == 3) {
    life --;
  }
  return 0;
}

void Object::draw() {
  // skip object above and below screen
  if ((y < Engine::cameraY) || (y > (Engine::cameraY + gb.display.height()))) return;
  //draw object
  if (image) {
    gb.display.drawImage((int)(x + 0.05) - (int)Engine::cameraX, (int)(y + 0.05) - (int)Engine::cameraY, *image, width, height);
  } else {
    gb.display.setColor(color);
    gb.display.drawRect((int)(x + 0.05) - (int)Engine::cameraX, (int)(y + 0.05) - (int)Engine::cameraY, width, height);
  }
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
  return gb.collideRectRect(x, y, width, height, obj->x, obj->y, obj->width, obj->height);
}

float Object::getCenterX() {
  return (x + width / 2);
}

float Object::getCenterY() {
  return (y + height / 2);
}
