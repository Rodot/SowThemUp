#include "Particle.h"

Particle::Particle(float X, float Y, Color c){
  init();
  x = X;
  y = Y;
  vx = float(random(0,11)-5)/5.0;
  vy = float(random(0,11)-5)/5.0;
  width = random(1,3);
  height = width;
  collideMap = true;
  collideObjects = false;
  life = 50;
  color = c;
}

void Particle::update(){
  Object::update();
  //kill it when it stops
  if ((abs(vx) + abs(vy)) < 0.5) {
    life = 0;
  }
  //limit lifespan
  life --;
}

void Particle::die(){
  //do nothing
}
