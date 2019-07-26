#include "Player.h"
#include <Gamebuino-Meta.h>

const uint16_t player_data[] = {
  6,      // frame width
  6,      // frame height
  4,      // number of frames
  0,      // animation speed
  0xf81f, // transparent color
  0,      // RGB565 color mode
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff,
  0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff,
  0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff,
  0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
};

Image player_image(player_data);

Player::Player() {
  init();
}

void Player::init() {
  Object::init();
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
  color = WHITE;
  image = &player_image;
}

void Player::die() {
  Engine::won = false;
  Engine::gameOver = true;
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , ORANGE));
  Engine::addObject(new Particle(x, y , YELLOW));
  Engine::addObject(new Particle(x, y , YELLOW));
}

void Player::update() {
  if (gb.buttons.repeat(BUTTON_A, 4)) {
    //throw water
    Engine::addObject(new Bullet(getCenterX(), y + height + 1, vx, vy));
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    // do nothing yet
  }

  //controls with the buttons
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

  //constant player movement, going down
  vy += 0.05;

  //reduce speed due to air friction
  vx *= friction;
  vy *= friction;

  //limit maximum speeds
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -3, 3);

  //stop if speed is really low
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  //move horizontally (x) and check for collisions with the map
  x += vx;
  collideMapX();

  //move vertically (y) and check for collisions with the map
  y += vy;
  collideMapY();

  //move the camera to follow the player
  Engine::cameraTargetX = getCenterX() - gb.display.width() / 2;
  Engine::cameraTargetY = getCenterY() - gb.display.height() / 5;
}

void Player::interact(Object * obj) {
  // do nothing)
}
