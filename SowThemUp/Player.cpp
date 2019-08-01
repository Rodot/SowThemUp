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
  specialCooldown = 0;
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
  Engine::addObject(new Particle(x, y , YELLOW));
}

void Player::update() {
  if (gb.buttons.repeat(BUTTON_A, 4)) {
    //throw water
    int spread = 5;
    int bvx = float(random(0, spread * 2) - spread) / 10.0;
    int bvy = float(random(50, 70)) / 10.0;
    Engine::addObject(new Bullet(getCenterX(), y + height + 1, bvx, bvy));
  }

  if (specialCooldown > 0) {
    specialCooldown = specialCooldown - 1;
  } else {
    int x = getCenterX();
    int y = getCenterY();
    // do the special move in several steps

    if (gb.buttons.held(BUTTON_B, 1)) {
      Engine::addObject(new Bullet(x, y + 5, -2, 5));
      Engine::addObject(new Bullet(x, y + 5, -1, 6));
      Engine::addObject(new Bullet(x, y + 5, 0, 7));
      Engine::addObject(new Bullet(x, y + 5, 1, 6));
      Engine::addObject(new Bullet(x, y + 5, 2, 5));
    }
    if (gb.buttons.held(BUTTON_B, 8)) {
      Engine::growTree(x + 8, y);
      Engine::growTree(x, y + 8);
      Engine::growTree(x - 8, y);
    }
    if (gb.buttons.held(BUTTON_B, 11)) {
      Engine::growTree(x + 8, y + 8);
      Engine::growTree(x, y + 16);
      Engine::growTree(x - 8, y + 8);
    }
    if (gb.buttons.held(BUTTON_B, 13)) {
      Engine::growTree(x + 8, y + 16);
      Engine::growTree(x, y + 24);
      Engine::growTree(x - 8, y + 16);
    }
    if (gb.buttons.held(BUTTON_B, 14)) {
      Engine::growTree(x + 8, y + 24);
      Engine::growTree(x, y + 32);
      Engine::growTree(x - 8, y + 24);
    }
    if (gb.buttons.released(BUTTON_B)) {
      //reset the cooldown
      specialCooldown = 50;
    }
  }

  //move player using buttons
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

  if (y > (Engine::map.heightTiles * Engine::map.tileSize - 50)) {
    Engine::won = true;
    Engine::gameOver = false;
  }
}

void Player::interact(Object * obj) {
  // do nothing)
}
