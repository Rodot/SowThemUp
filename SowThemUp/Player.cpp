#include "Player.h"
#include <Gamebuino-Meta.h>
#include "Toolbox.h"

Player::Player() {
  init();
}

void Player::init() {
  Object::init();
  color = WHITE;
}

void Player::die() {
  Engine::addObject(new Player());
}

void Player::update() {
  if (gb.buttons.repeat(BUTTON_A, 4)) {
    Engine::addObject(new Bullet(x + width + 1, getCenterY(), vx, vy, 0));
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    Engine::addObject(new Object(x, y - 8, 6, 6, 0 , vy - 3));
  }

  ax = 0;
  ay = 0;

  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    vx += 0.5;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    vx -= 0.5;
  }
  if (gb.buttons.repeat(BUTTON_UP, 1)) {
    vy -= 1;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
    vy += 0.1;
  }

  //air friction
  vx *= 0.9;
  vy *= 0.9;

  //constant player movement
  vy = max(vy, 0.1);

  updatePhysics();

  //limit speeds
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -5, 5);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  vx += ax;
  x += vx;
  int collided = collideMapX();

  vy += ay;
  y += vy;
  bool falling = (vy > 0) ? true : false;
  collided = collideMapY();
  if (falling && collided) {
    jumped = false;
  }

  Engine::cameraTargetX = getCenterX() - gb.display.width() / 2;
  Engine::cameraTargetY = getCenterY() - gb.display.height() / 5;
}

void Player::draw() {
  gb.display.setColor(WHITE);
  Object::draw();
}
