#ifndef projectiles_h
#define projectiles_h
#include "Collision.h"

/*
Projectile types:
id - name, shoot by what, behavior
0 - high-pressure bubble, washer, (slows down, dies if it stops or if it collides with a wall)
1 - magic freeze, freezer, (doesn't move, if the player collides with it for too long it freezes the player)
2 - fireball, magmar (moves slowly, can move thru walls)
*/

struct Projectile {
  int x;
  int y;
  int8_t xSpd;
  int8_t ySpd;
  uint8_t type;
  bool exist;
};Projectile pr[4];

void createProjectile(int xA, int yA, int8_t xSpdA, int8_t ySpdA, uint8_t typA) {
  for(uint8_t x = 0; x < 4; x++) {
    if(!pr[x].exist) {
      pr[x].exist = true;
      pr[x].x = xA;
      pr[x].y = yA;
      pr[x].xSpd = xSpdA;
      pr[x].ySpd = ySpdA;
      pr[x].type = typA;
      break;
    }
  }
}

void updateProjectiles() {
  for(uint8_t x = 0; x < 4; x++) {
    if(pr[x].exist) {
      pr[x].x += pr[x].xSpd;
      pr[x].y += pr[x].ySpd;
      switch (pr[x].type) {
        case 0:
        {
          Rect prRect = Rect {pr[x].x, pr[x].y, 5, 5};
          if(collideWithTile(prRect,true)) {
            pr[x].exist = false;
          }if(collideWithPlayer(prRect)) {
            triggerHurt(1,NONE);
            pr[x].exist = false;
          }arduboy.drawRoundRect(pr[x].x, pr[x].y, 5, 5, 1, WHITE);
          arduboy.fillRect(pr[x].x + 1, pr[x].y + 1, 3, 3, BLACK);
          break;
        }
        case 1:
        {
          Rect prRect = Rect {pr[x].x, pr[x].y, 24, 24};
          if(arduboy.everyXFrames(6)) arduboy.fillRoundRect(pr[x].x, pr[x].y, 24, 24, 2, BLACK);
          if(arduboy.everyXFrames(45)) {
            if(collideWithPlayer(prRect)) player.frozen = 6;
            pr[x].exist = false;
          }
          break;
        }
        case 2:
        {
          Rect prRect = Rect {pr[x].x, pr[x].y, 3, 3};
          if(collideWithTile(prRect,true)) {
            pr[x].exist = false;
          }if(collideWithPlayer(prRect)) {
            triggerHurt(1,NONE);
            pr[x].exist = false;
          }arduboy.drawRoundRect(pr[x].x, pr[x].y, 3, 3, 1, BLACK);
          arduboy.drawPixel(pr[x].x + 1, pr[x].y + 1, WHITE);
          break;
        }
      }
    }
  }
}

void despawnAllProjectiles() {
  for(uint8_t x = 0; x < 4; x++) {
    pr[x].exist = false;
  }
}

bool alreadyExists(uint8_t typ) {
  for(uint8_t x = 0; x < 4; x++) {
    if(pr[x].type == typ and pr[x].exist) return true;
  }return false;
}

#endif
