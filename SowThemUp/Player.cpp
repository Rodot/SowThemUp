#include "Player.h"
#include <Gamebuino-Meta.h>
#include "Toolbox.h"

Player::Player() {
  init();
}

void Player::init() {
  Object::init();
  direction = 1;
  color = WHITE;
}

void Player::die() {
  Engine::addObject(new Player());
}

void Player::update() {
  if (gb.buttons.repeat(BUTTON_A, 4)) {
    if (direction > 0) {
      Engine::addObject(new Bullet(x + width + 1, getCenterY(), vx, vy, direction));
    } else {
      Engine::addObject(new Bullet(x - 1, getCenterY(), vx, vy, direction));
    }
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    Engine::addObject(new Object(x, y - 8, 6, 6, direction , vy - 3));
  }

  ax = 0;
  ay = 0;

  //underwater
  if ((Engine::map->getTile(getCenterX(), getCenterY()) == 2)) {
    jumped = false;
    if (gb.buttons.repeat(BUTTON_UP, 1)) {
      vy -= 0.5;
    }
    if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
      vy += 0.5;
    }
  }
  if (gb.buttons.pressed(BUTTON_UP) && (!jumped)) {
    vy = -3;
    jumped = true;
  }
  if ((gb.buttons.timeHeld(BUTTON_UP) > 0) && (gb.buttons.timeHeld(BUTTON_UP) < 6) && (vy < 0)) {
    vy -= 0.5;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    vx += 1;
    direction = 1;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    vx -= 1;
    direction = -1;
  }

  updatePhysics();

  //limit speeds
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -5, 5);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  vx += ax;
  x += vx;
  int collided = collideMapX();
  //wall jump
  if ((vy > 0) && collided) {
    if (gb.buttons.pressed(BUTTON_UP)) {
      vy = -3;
      vx = - direction * 5;
      jumped = true;
    }
  }

  vy += ay;
  y += vy;
  bool falling = (vy > 0) ? true : false;
  collided = collideMapY();
  if (falling && collided) {
    jumped = false;
  }

  Engine::cameraTargetX = getCenterX() - gb.display.width() / 2 + direction * 15;
  Engine::cameraTargetY = getCenterY() - gb.display.height() / 2 ;
}

void Player::draw() {
  gb.display.setColor(WHITE);
  Object::draw();
}
