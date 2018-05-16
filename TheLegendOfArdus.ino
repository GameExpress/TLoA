//The Legend of Ardus
//Version 0.1

//License:
//This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
//To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

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
