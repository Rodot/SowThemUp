#include <Gamebuino-Meta.h>
#include "Engine.h"
Engine engine = Engine();

void setup() {
  gb.begin();
  engine.init();
  gb.display.clearTransparentColor();
}

void loop() {

  while (!gb.update());
  gb.display.clear();
  if (gb.buttons.pressed(BUTTON_MENU)) {
    engine.clear();
    engine.init();
  }
  engine.update();
}
