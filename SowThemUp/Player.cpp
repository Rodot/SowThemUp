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
    //throw water
    Engine::addObject(new Bullet(getCenterX(), y + height + 1, vx, vy));
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    //add a tree
    Engine::map->setTile(getCenterX(), getCenterY(), 2);
    Engine::addObject(new Particle(getCenterX(), getCenterY(), LIGHTGREEN));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), LIGHTGREEN));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), LIGHTGREEN));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), LIGHTGREEN));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), LIGHTGREEN));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), YELLOW));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), YELLOW));
    Engine::addObject(new Particle(getCenterX(), getCenterY(), YELLOW));
  }

  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    vx += 0.5;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    vx -= 0.5;
  }
  if (gb.buttons.repeat(BUTTON_UP, 1)) {
    vy -= 0.05;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
    vy += 0.1;
  }

  //constant player movement
  vy += 0.05;

  updatePhysics();

  //limit speeds
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -3, 3);
  //stop if moving too slow
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  x += vx;
  int collided = collideMapX();

  y += vy;
  collided = collideMapY();

  Engine::cameraTargetX = getCenterX() - gb.display.width() / 2;
  Engine::cameraTargetY = getCenterY() - gb.display.height() / 5;
}


void Player::draw(){
  Object::draw();
  //gb.display.println(life);
}
