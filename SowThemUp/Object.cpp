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
  ax = 0;
  ay = 0;
  width = 6;
  height = 6;
  life = 10;
  collideMap = true;
  collideObjects = true;
  justCreated = true;
  color = GRAY;
}

void Object::die() {
  Engine::addObject(new Particle(x, y , vx, -3, width, height, false));
}

void Object::update() {
  updatePhysics();

  //limit speeds
  vx = constrain(vx, -7, 7);
  vy = constrain(vy, -7, 7);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  vx += ax;
  x += vx;
  collideMapX();

  vy += ay;
  y += vy;
  collideMapY();


}

void Object::updatePhysics() {
}

int Object::collideMapX() {
  if (collideMap) {
    if (vx > 0) {
      if ((Engine::map->getTile(x + width, y) == 1) || (Engine::map->getTile(x + width, y + height) == 1)) {
        int tileX = (((int)(x + width) / (int)Engine::map->tileWidth) * (int)Engine::map->tileWidth);
        x = tileX - width - 0.01;
        vx *= - 1;
        return 1;
      }
    }
    else {
      if ((Engine::map->getTile(x, y) == 1) || (Engine::map->getTile(x, y + height) == 1)) {
        int tileX = (((int)x / (int)Engine::map->tileWidth) * (int)Engine::map->tileWidth);
        x = tileX + Engine::map->tileWidth + 0.01;
        vx *= - 1;
        return 1;
      }
    }
  }
  return 0;
}

int Object::collideMapY() {
  if (collideMap) {
    if (vy > 0) {
      if ((Engine::map->getTile(x, y + height) == 1) || (Engine::map->getTile(x + width, y + height) == 1)) {
        int tileY = (((int)(y + height) / (int)Engine::map->tileHeight) * (int)Engine::map->tileHeight);
        y = tileY - height - 0.01;
        vy *= - 1;
        return 1;
      }
    } else {
      if ((Engine::map->getTile(x, y) == 1) || (Engine::map->getTile(x + width, y) == 1)) {
        int tileY = (((int)y / (int)Engine::map->tileHeight) * (int)Engine::map->tileHeight);
        y = tileY + Engine::map->tileHeight + 0.01;
        vy *= - 1;
        return 1;
      }
    }
  }
  return 0;
}

void Object::interact(Object * obj) {
  if (collideObjects && obj->collideObjects) {
    if (colliding(obj)) {
      if ((vx == 0) && (vy == 0)) {
        return;
      }
      //distance between centers
      float dx, dy;
      //penetration depth
      float px, py;

      dx = obj->getCenterX() - getCenterX();
      dy = obj->getCenterY() - getCenterY();

      if ((dx >= 0) && (dy >= 0)) { //bottom right corner
        px = (x + width) - obj->x;
        py = (y + height) - obj->y;
      } else if ((dx >= 0) && (dy <= 0)) { //top right corner
        px = (x + width) - obj->x;
        py = y - (obj->y + obj->height);
      } else if ((dx <= 0) && (dy <= 0)) { //top left corner
        px = x - (obj->x + obj->width);
        py = y - (obj->y + obj->height);
      } else { //bottom left corner
        px = x - (obj->x + obj->width);
        py = (y + height) - obj->y;
      }
      if (abs(px) < abs(py)) { //horizontal collision
        x -= (px + 0.01);
        obj->vx *= -1;

      } else { //vertical collision
        y -= (py + 0.01);
        obj->vy *= -1;
      }
    }
  }
}

void Object::draw() {
  gb.display.setColor(color);
  gb.display.drawRect((int)(x + 0.05) - (int)Engine::cameraX, (int)(y + 0.05) - (int)Engine::cameraY, width, height);
}

int Object::collidingTile() {
  int tile = -1;
  int temp = Engine::map->getTile(x, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x, y + height);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width, y + height);
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
