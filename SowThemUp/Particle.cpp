#include "Particle.h"

Particle::Particle(float X, float Y, Color c) {
  x = X;
  y = Y;
  vx = float(random(0, 11) - 5) / 5.0;
  vy = float(random(0, 11) - 5) / 5.0;
  friction = 0.9;
  bounce = 1;
  width = random(1, 3);
  height = width;
  collideMap = true;
  collideObjects = false;
  justCreated = true;
  life = 50;
  color = c;
}

void Particle::update() {
  Object::update();
  //if the particle doesn't move, kill it
  if ((abs(vx) + abs(vy)) < 0.5) {
    life = 0;
  }
  //limit lifespan
  life --;
}

void Particle::die() {
  //do nothing
}

void Particle::interact(Object * obj) {
  // do nothing
}
