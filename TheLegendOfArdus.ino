#include <Arduboy2.h>
Arduboy2 arduboy;
#include "Gameplay.h"

/* BREAK IN CASE OF EMERGENCY!!! (out of memory)
int main() {
  init();
  setup();
  while(true) {
    loop();
  }
  return 0;
}
*/
void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(30);
  Serial.begin(9600);
  loadGame();
  randomSeed(player.coins + player.gems + player.keys + opened[0] * 2 + opened[3] * 7);
}
void loop() {
  if(!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  game();
  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  arduboy.display(true);
}
