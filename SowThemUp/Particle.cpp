#include "Particle.h"

Particle::Particle(float X, float Y, float VX, float VY, float W, float H, boolean collide){
  init();
  x = X;
  y = Y;
  vx = random(0,3)-1;
  vy = random(0,3)-1;
  width = W;
  height = H;
  collideMap = collide;
  collideObjects = false;
  life = 50;
  color = DARKBLUE;
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
