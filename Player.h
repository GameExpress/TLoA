#ifndef player_h
#define player_h
#include "Messages.h"

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
#define NONE 4

uint8_t GameState = 0;
uint8_t Map = 23;
uint8_t durLeft;
struct Player {
  int16_t x;
  int16_t y;
  uint8_t hlth;
  uint8_t coins;
  uint8_t keys;
  uint8_t gems;
  uint8_t frm;
  bool walking;
  bool attacking;
  bool defending;
  uint8_t animTim;
  uint8_t invicTim;
  uint8_t dir;
  uint8_t hurtTrigger;
  uint8_t frozen;
  uint8_t freezeDamage;
  uint8_t mapState;
  bool swimming;
  uint8_t swDur;
  uint8_t shDur;
  uint8_t mxDur;
  uint8_t rgDur;
  uint8_t maxHlth;
  bool canSwim;
  bool canShatter;
  bool canTeleport;
};
Player player = {24,16,3,0,0,0,0,false,false,false,0,0,1,0,0,0,0,false,5,5,5,255,3,true,true,false};

void animationManager() {
  if(player.walking) {
    if(player.animTim == 3) {
      if(player.frm == 1) player.frm = 0;
      else player.frm = 1;
      player.animTim = 0;
    }else player.animTim++;
  }else if(player.attacking) {
    player.frm = 3;
    arduboy.drawBitmap(player.x + (player.dir % 2 == 0 ? (player.dir == 0 ? 8 : -8) : 0),player.y + (player.dir % 2 == 1 ? (player.dir == 1 ? 8 : -8) : 0),player_white[player.dir][4],8,8,WHITE);
    arduboy.drawBitmap(player.x + (player.dir % 2 == 0 ? (player.dir == 0 ? 8 : -8) : 0),player.y + (player.dir % 2 == 1 ? (player.dir == 1 ? 8 : -8) : 0),player_black[player.dir][4],8,8,BLACK);
    if(player.animTim == 8) {player.attacking = false; player.animTim = 0;}
    else player.animTim++;
  }else if(player.defending) {
    player.frm = 2;
    if(arduboy.justReleased(B_BUTTON)) player.defending = false;
  }else player.frm = 1;
}

#endif
