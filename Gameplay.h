#ifndef gameplay_h
#define gameplay_h
#include "Images.h"
#include "Player.h"
#include "Levels.h"
#include "Enemies.h"
#include "Collision.h"
#include "WorldManager.h"

#define CHEST_NUM 30

//0 = Map, 1 = Loot Type, 2 = Loot Quantity
//Loot types: 0 = coins, 1 = gems, 2 = keys, 3 = health, 4 = dur+ (increase mxDur), 5 = reg+ (decrease rgDur), 6 = hlth+ (increase max amount of health), 7 = canSwim:true, 8 = shatterIce:true, 9 = teleport:true
const uint8_t chestLoot[CHEST_NUM][3] = {
  {28,0,8},
  {38,2,1},
  {13,1,4},
  {18,1,6},
  {27,1,8},
  {34,0,16},
  {42,5,75},
  {46,2,1},
  {45,1,3},
  {43,0,8},
  {48,4,5},
  {47,0,12},
  {50,1,4},
  //TEMPLE 5 CHEST
  //TEMPLE 5 CHEST BONUS
  //TEMPLE 5 CHEST BONUS
  //TEMPLE 6 CHEST
  //TEMPLE 6 CHEST BONUS
  //TEMPLE 6 CHEST BONUS
  //TEMPLE 7 CHEST
  //TEMPLE 7 CHEST BONUS
  //TEMPLE 7 CHEST BONUS
  //TEMPLE 8 CHEST 1
  //TEMPLE 8 CHEST 2
  //TEMPLE 8 CHEST 3
  //TEMPLE 8 CHEST 4
  {71,7,1},
  {70,8,1},
  {68,9,1},
  //PRIZE 4
};

bool opened[CHEST_NUM];

#include "EEPROM_save.h"

void openChest() {
  for(uint8_t id = 0; id < CHEST_NUM; id++) {
    if(chestLoot[id][0] == Map and solidCollisionWith(playerRect(),11) and !opened[id]) {
      opened[id] = true;
      switch (chestLoot[id][1]) {
        case 0:
          player.coins += chestLoot[id][2];
          break;
        case 1:
          player.gems += chestLoot[id][2];
          break;
        case 2:
          player.keys += chestLoot[id][2];
          break;
        case 4:
          player.mxDur += chestLoot[id][2];
          player.swDur += chestLoot[id][2];
          player.shDur += chestLoot[id][2];
          break;
        case 5:
          player.rgDur -= chestLoot[id][2];
          break;
        case 6:
          player.maxHlth += chestLoot[id][2];
          player.hlth += chestLoot[id][2];
          break;
        case 7:
          player.canSwim = true;
          break;
        case 8:
          player.canShatter = true;
          break;
        case 9:
          player.canTeleport = true;
      }createFoundLootMessage(chestLoot[id][1]);
      break;
    }
  }
}

void drawHUD() {
  //HUD background
  arduboy.fillRect(96,0,32,64,BLACK);
  //Life Meter
  arduboy.setCursor(101,0);
  arduboy.print(F("LIFE"));
  for(uint8_t x; x < player.maxHlth; x++){
    if(player.hlth > x) Sprites::drawOverwrite(98+(x%5)*6,9+(x/5)*7,heart_1,0);
    else Sprites::drawOverwrite(98+(x%5)*6,9+(x/5)*7,heart_0,0);
  }
  //Teleport power
  //coming soon
  //Letter A
  arduboy.drawRect(98,24,4,3,WHITE);
  arduboy.drawPixel(98,27,WHITE);
  arduboy.drawPixel(101,27,WHITE);
  //Letter B
  arduboy.drawRect(113,25,4,3,WHITE);
  arduboy.drawLine(113,24,115,24,WHITE);
  //Equipment Boxes
  durLeft = (player.swDur * 8) / player.mxDur;
  arduboy.fillRect(104,28 + (8 - durLeft),7,durLeft,WHITE);
  durLeft = (player.shDur * 8) / player.mxDur;
  arduboy.fillRect(119,28 + (8 - durLeft),7,durLeft,WHITE);
  arduboy.drawBitmap(103,26,player_black[3][4],8,8,BLACK);
  arduboy.drawBitmap(120,28,shield_icon,5,8,BLACK);
  arduboy.drawLine(105,34,109,34,BLACK);
  arduboy.drawPixel(107,35,BLACK);
  arduboy.drawRect(103,27,9,10,WHITE);
  arduboy.drawRect(118,27,9,10,WHITE);
  if(player.swDur < player.mxDur) arduboy.drawLine(100,36,100,36 - (((arduboy.frameCount % player.rgDur) * 4) / player.rgDur),WHITE);
  if(player.shDur < player.mxDur) arduboy.drawLine(115,36,115,36 - (((arduboy.frameCount % player.rgDur) * 4) / player.rgDur),WHITE);
  //Coins,keys,gems
  Sprites::drawOverwrite(98,38,coin,0);
  Sprites::drawOverwrite(98,47,key,0);
  Sprites::drawOverwrite(98,57,gem,0);
  arduboy.setCursor(104,38);
  if(player.coins < 10) {arduboy.print("x00");arduboy.print(player.coins);}
  else if(player.coins < 100) {arduboy.print("x0");arduboy.print(player.coins);}
  else {arduboy.print('x');arduboy.print(player.coins);}
  arduboy.setCursor(107,47);
  if(player.keys < 10) {arduboy.print("x0");arduboy.print(player.keys);}
  else {arduboy.print('x');arduboy.print(player.keys);}
  arduboy.setCursor(107,57);
  if(player.gems < 10) {arduboy.print("x0");arduboy.print(player.gems);}
  else {arduboy.print('x');arduboy.print(player.gems);}
}
void drawMap() {
  for(uint8_t y; y < 96; y++){
    uint8_t blck = getBlock(y%12,y/12);
    Sprites::drawOverwrite((y%12)*8,(y/12)*8,tiles[blck],0);
    if(blck == 11) {
      for(uint8_t c = 0; c < CHEST_NUM; c++) {
        if(chestLoot[c][0] == Map and opened[c]) Sprites::drawOverwrite((y%12)*8,(y/12)*8,chest_open,0);
      }
    }
  }
}

void controlPlayer() {
  Rect pLRect = Rect {player.x, player.y + 1, 1, 6};
  Rect pDRect = Rect {player.x + 1, player.y + 7, 6, 1};
  Rect pRRect = Rect {player.x + 7, player.y + 1, 1, 6};
  Rect pURect = Rect {player.x + 1, player.y, 6, 1};
  if(!player.attacking and !player.defending and player.hurtTrigger == 0 and player.frozen == 0) {
    if(player.swimming ? arduboy.everyXFrames(2) : true) {
      if(arduboy.pressed(LEFT_BUTTON) and !collideWithTile(pLRect,player.canSwim)) {
        if(player.x < -7) {player.x = 95;mapControl(1);}
        player.x--;
        player.walking = true;
        player.dir = LEFT;
      }else if(arduboy.pressed(RIGHT_BUTTON) and !collideWithTile(pRRect,player.canSwim)) {
        if(player.x > 95) {player.x = -7;mapControl(2);}
        player.x++;
        player.walking = true;
        player.dir = RIGHT;
      }else if(arduboy.pressed(UP_BUTTON) and !collideWithTile(pURect,player.canSwim)) {
        if(player.y < -7) {player.y = 63;mapControl(3);}
        player.y--;
        player.walking = true;
        player.dir = UP;
      }else if(arduboy.pressed(DOWN_BUTTON) and !collideWithTile(pDRect,player.canSwim)) {
        if(player.y > 63) {player.y = -7;mapControl(4);}
        player.y++;
        player.walking = true;
        player.dir = DOWN;
      }else {
        player.walking = false;
        Rect swordRect = Rect {player.x + (player.dir % 2 == 0 ? (player.dir == 0 ? 8 : -8) : 0), player.y + (player.dir % 2 == 1 ? (player.dir == 1 ? 8 : -8) : 0), 8, 8};
        if(arduboy.justPressed(A_BUTTON) and player.swDur > 0) {
          player.attacking = true;
          damageEnemy(swordRect, 1);
          if(player.canShatter) shatterIce(swordRect);
          player.swDur--;
          if(player.swDur == 0) createMessage("Your sword broke");
        }if(arduboy.justPressed(B_BUTTON) and !player.swimming and player.shDur > 0) player.defending = true;
      }
    }
  }if(player.invicTim % 2 == 0) {
    arduboy.drawBitmap(player.x,player.y,player_white[player.dir][player.frm],8,8,WHITE);
    arduboy.drawBitmap(player.x,player.y,player_black[player.dir][player.frm],8,8,BLACK);
  }if(solidCollisionWith(playerRect(),10) and player.invicTim == 0) {
    triggerHurt(1,player.dir == RIGHT ? LEFT : player.dir == LEFT ? RIGHT : player.dir == UP ? DOWN : UP);
  }if(player.invicTim > 0) {player.invicTim--; triggerHurt(0,0);}
  if(hurtByEnemy() > 0) {
    player.hurtTrigger = 4;
    if(player.defending) {triggerHurt(0,player.dir == RIGHT ? LEFT : player.dir == LEFT ? RIGHT : player.dir == UP ? DOWN : UP); player.shDur--; if(player.shDur == 0) {createMessage("Your shield broke"); player.defending = false;}}
    if(player.invicTim == 0) {
      player.hlth -= hurtByEnemy();
      player.invicTim = 30;
    }
  }if(player.hurtTrigger > 0) player.hurtTrigger--;
  if(player.hurtTrigger > 0) {
    if(collideWithTile(playerRect(),false)) player.hurtTrigger = 0;
    else {
      if(sideHurt() == LEFT) player.x--;
      if(sideHurt() == RIGHT) player.x++;
      if(sideHurt() == UP) player.y--;
      if(sideHurt() == DOWN) player.y++;
    }
  }if(player.frozen > 0) {
    if(player.freezeDamage < 108 / player.hlth) player.freezeDamage++;
    else {triggerHurt(1,NONE); player.freezeDamage = 0;}
    if(arduboy.justPressed(A_BUTTON)) {player.frozen--; arduboy.fillRoundRect(player.x,player.y,8,8,1,BLACK);}
    else arduboy.drawRoundRect(player.x,player.y,8,8,1,BLACK);
  }if(solidCollisionWith(playerRect(),7)) enterTrigger();
  if(solidCollisionWith(playerRect(),1) and player.canSwim) player.swimming = true;
  else player.swimming = false;
  if(player.swimming) arduboy.fillRect(player.x,player.y + 6,8,2,BLACK);
  if(arduboy.everyXFrames(player.rgDur)) {if(player.swDur < player.mxDur) player.swDur++; if(player.shDur < player.mxDur) player.shDur++;}
  if(solidCollisionWith(playerRect(),14) and player.keys > 0) {
    for(uint8_t x = 0; x < DOOR_NUM; x++) {
      if(doorLoc[x] == Map) {
        uint8_t dTemp = locCollisionWith(playerRect(),14);
        if(dTemp % 2 == 0) {
          curLvl[dTemp / 2] = 0x60 + getBlock((dTemp+1)%12,dTemp/12);
        }else{
          curLvl[dTemp / 2] = (getBlock((dTemp-1)%12,dTemp/12) << 4) + 0x06;
        }
        unlocked[x] = true;
        createMessage("Door Unlocked");
        player.keys--;
      }
    }
  }
}

uint8_t saveTimer = 0;
uint8_t saveDelay = 0;
uint8_t delTimer = 0;

void game() {
  switch (GameState) {
    case 0: //Main Menu
      arduboy.drawBitmap(40,24,Ardus,48,12,WHITE);
      arduboy.drawRect(27,14,72,26,WHITE);
      arduboy.drawBitmap(31,18,TLO,64,4,WHITE);
      arduboy.setCursor(14,48);
      arduboy.print(F("PRESS A TO PLAY"));
      if(arduboy.justPressed(A_BUTTON)) GameState = 1;
      if(arduboy.pressed(B_BUTTON) and delTimer < 150) delTimer++;
      else if(delTimer < 150) delTimer = 0;
      if(delTimer == 150) {arduboy.digitalWriteRGB(RED_LED, RGB_ON); delay(1000); delTimer = 152; deleteGame(); arduboy.digitalWriteRGB(RED_LED, RGB_OFF);}
      if(delTimer == 152) {arduboy.setCursor(0,0); arduboy.print(F("Reboot to delete\nsave data"));}
      break;
    case 1: //Playing
      if(player.hlth == 0) {delay(250); GameState = 2;}
      drawMap();
      enemyUpdate();
      controlPlayer();
      drawHUD();
      animationManager();
      openChest();
      displayMessage();
      if(arduboy.pressed(A_BUTTON) and arduboy.pressed(B_BUTTON) and saveDelay == 0) saveTimer++;
      else saveTimer = 0;
      if(saveTimer == 90) {
        createMessage("Game Saved!");
        saveGame();
        saveDelay = 150;
      }if(saveDelay > 0) saveDelay--;
      break;
    case 2: //Game Over
      player.frm = 1;
      for(uint8_t x = 0; x < 3; x++) {
        for(uint8_t y = 0; y < 4; y++) {
          arduboy.fillScreen(WHITE);
          arduboy.drawBitmap(player.x,player.y,player_white[player.dir][player.frm],8,8,WHITE);
          arduboy.drawBitmap(player.x,player.y,player_black[player.dir][player.frm],8,8,BLACK);
          if(player.dir == 3) player.dir = 0;
          else player.dir++;
          arduboy.display(true);
          delay(100);
        }
      }arduboy.drawCircle(player.x + 4,player.y + 4,4,WHITE);
      arduboy.drawRect(player.x,player.y,8,8,BLACK);
      arduboy.display(true);
      delay(400);
      arduboy.display(true);
      delay(200);
      arduboy.setCursor(22,28);
      arduboy.print(F("Game Over!"));
      arduboy.display();
      saveGame();
      while(true) {}
  }
}
#endif
