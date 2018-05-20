#ifndef enemies_h
#define enemies_h
#include "Collision.h"
#include "Projectiles.h"

/*
Enemy types:
id - image (name), health, attack damage, (touch attack, range attack, move behavior, other)
0 - bumper, 1, 1, (touching, no range attacks, move slowly towards player)
1 - washer, 2, 1, (no touch attacks, shoots high-pressure water bubble, stationary)
2 - busht, 5, 1, (thorns, no range attacks, stationary)
3 - freezer, 3, 1, (freeze player, freeze player if stands near for too long, stationary)
4 - magmar, 2, 2, (touching, shoots fireballs, moves very slowly on ground & stationary on lava)
5 - mrk, 1, 2, (touching, no range attacks, moves slowly towards player & can move thru walls, dies on impact)
6 - knight, 4, 3, (attacks with sword, no range attacks, moves very slowly)
7 - (temple enemy 1)
8 - (temple enemy 2)
9 - (temple enemy 3)
*/

struct Enemy {
  int x;                      //x-pos
  int y;                      //y-pos
  const unsigned char* image; //image
  uint8_t type;               //type
  uint8_t hlth;               //health
  bool exist;                 //does it exist? If true, update!
  uint8_t id;                 //id of enemy in 'enemyLoc'
  uint8_t attDmg;             //attack damage
};
Enemy en[4];

#define ENEMY_NUM 81

//0 = xTile, 1 = yTile, 2 = type, 3 = map
const uint8_t enemyLoc[ENEMY_NUM][4] = {
  //GROUND ENEMIES
  {3,5,0,16},
  {3,2,0,17},
  {6,3,0,17},
  {4,2,1,28},
  {5,3,2,22},
  {6,3,2,14},
  {5,6,2,14},
  {1,6,0,21},
  {6,3,2,21},
  {10,4,2,21},
  {2,5,0,28},
  {10,2,0,28},
  {4,1,0,15},
  {8,3,0,15},
  {2,2,0,29},
  {9,4,0,29},
  {4,2,1,30},
  {9,4,1,30},
  {6,5,0,8},
  {2,4,0,8},
  {8,2,1,8},
  {8,4,0,7},
  {6,3,0,7},
  {5,2,3,9},
  {8,4,0,9},
  {2,1,0,10},
  {5,1,0,10},
  {6,4,0,10},
  {9,2,4,10},
  {6,5,4,11},
  {3,3,4,5},
  {8,4,4,5},
  {6,5,4,6},
  {3,3,0,12},
  {9,4,0,12},
  {4,2,0,19},
  {7,2,4,18},
  {1,5,4,18},
  {3,3,4,13},
  {5,2,0,13},
  {5,4,0,13},
  {10,3,0,19},
  {8,6,0,19},
  {4,5,2,24},
  {4,2,5,25},
  {6,4,5,25},
  //TEMPLE ENEMIES
  //TEMPLE 1
  {3,5,0,35},
  {8,3,0,35},
  {2,2,0,36},
  {7,3,0,36},
  {8,6,0,36},
  {8,1,0,37},
  {3,6,0,38},
  {8,6,0,38},
  //TEMPLE 2
  {3,2,1,39},
  {9,4,0,39},
  {5,2,0,40},
  {8,4,1,40},
  {8,6,1,41},
  {2,2,1,42},
  {9,3,1,42},
  //TEMPLE 3
  {7,1,2,43},
  {1,2,2,43},
  {5,6,2,43},
  {10,6,2,43},
  {9,2,2,44},
  {10,4,2,44},
  {4,3,2,44},
  {4,6,2,44},
  {1,2,2,45},
  {6,3,2,45},
  {9,4,2,45},
  {4,6,2,45},
  {4,2,2,46},
  {3,5,2,46},
  {8,3,2,46},
  {7,6,2,46},
};
bool killed[ENEMY_NUM];

void dropRandomItem() {
  if(random(4) == 1) {
    switch (random(10)) {
      case 0 ... 5: //50% chance of getting coins
        player.coins += random(2,5);
        createFoundLootMessage(0);
        break;
      case 6 ... 8: //30% chance of getting a heart
        player.hlth++;
        if(player.hlth > player.maxHlth) player.hlth = player.maxHlth;
        createFoundLootMessage(3);
        break;
      default: //20% chance of getting a gem
        player.gems++;
        createFoundLootMessage(1);
        break;
    }
  }
}

void spawnEnemy(uint8_t id) {
  if(Map == enemyLoc[id][3] and !killed[id]) {
    for(uint8_t x; x < 4; x++) {
      if(!en[x].exist) {
        en[x].exist = true;
        en[x].x = enemyLoc[id][0] * 8;
        en[x].y = enemyLoc[id][1] * 8;
        en[x].type = enemyLoc[id][2];
        en[x].id = id;
        switch(en[x].type) {
          case 0:
            en[x].image = bumper;
            en[x].hlth = 1;
            en[x].attDmg = 1;
            break;
          case 1:
            en[x].image = washer;
            en[x].hlth = 2;
            en[x].attDmg = 1;
            break;
          case 2:
            en[x].image = busht;
            en[x].hlth = 5;
            en[x].attDmg = 1;
            break;
          case 3:
            en[x].image = freezer;
            en[x].hlth = 3;
            en[x].attDmg = 1;
            break;
          case 4:
            en[x].image = magmar;
            en[x].hlth = 2;
            en[x].attDmg = 2;
            break;
          case 5:
            en[x].image = mrk;
            en[x].hlth = 1;
            en[x].attDmg = 2;
        }break;
      }
    }
  }
}

void despawnAllEnemies() {
  for(uint8_t x = 0; x < 4; x++) {
    en[x].exist = false;
  }despawnAllProjectiles();
}

void spawnEnemies() {
  for(uint8_t x = 0; x < ENEMY_NUM; x++) {
    if(enemyLoc[x][3] == Map) spawnEnemy(x);
  }
}

void enemyUpdate() {
  for(uint8_t x; x < 4; x++) {
    if(en[x].exist) {
      Rect enRect = Rect {en[x].x, en[x].y, 8, 8};
      Rect eLRect = Rect {en[x].x, en[x].y + 1, 1, 6};
      Rect eDRect = Rect {en[x].x + 1, en[x].y + 7, 6, 1};
      Rect eRRect = Rect {en[x].x + 7, en[x].y + 1, 1, 6};
      Rect eURect = Rect {en[x].x + 1, en[x].y, 6, 1};
      Rect attRadius = Rect {en[x].x - 24, en[x].y - 24, 56, 56};
      if((en[x].type % 2 == 0 or en[x].type == 5) and collideWithPlayer(enRect)) {
        if(collideWithPlayer(eLRect)) triggerHurt(en[x].attDmg,LEFT);
        if(collideWithPlayer(eRRect)) triggerHurt(en[x].attDmg,RIGHT);
        if(collideWithPlayer(eDRect)) triggerHurt(en[x].attDmg,DOWN);
        if(collideWithPlayer(eURect)) triggerHurt(en[x].attDmg,UP);
      }
      switch (en[x].type) {
        case 0: //Bumper
          if(collideWithPlayer(attRadius) and !collideWithPlayer(enRect) and arduboy.everyXFrames(3)) { //Attack the player
            if(player.x < en[x].x and !collideWithTile(eLRect,false)) en[x].x--;
            if(player.x > en[x].x and !collideWithTile(eRRect,false)) en[x].x++;
            if(player.y < en[x].y and !collideWithTile(eURect,false)) en[x].y--;
            if(player.y > en[x].y and !collideWithTile(eDRect,false)) en[x].y++;
          }break;
        case 1: //Washer
          if(arduboy.everyXFrames(106)) {
            createProjectile(en[x].x + 1, en[x].y + 1, (player.x < en[x].x ? -2 : (player.x > en[x].x ? 2 : 0)), (player.y < en[x].y ? -2 : (player.y > en[x].y ? 2 : 0)), 0);
          }break;
        case 3: //Freezer
          if(collideWithPlayer(enRect)) {
            if(collideWithPlayer(eLRect)) {triggerHurt(1,LEFT); player.frozen = 3;}
            if(collideWithPlayer(eRRect)) {triggerHurt(1,RIGHT); player.frozen = 3;}
            if(collideWithPlayer(eDRect)) {triggerHurt(1,DOWN); player.frozen = 3;}
            if(collideWithPlayer(eURect)) {triggerHurt(1,UP); player.frozen = 3;}
          }if(collideWithPlayer(attRadius) and !alreadyExists(1) and player.frozen == 0 and arduboy.everyXFrames(90)) createProjectile(en[x].x - 8, en[x].y - 8, 0, 0, 1);
          break;
        case 4: //Magmar
          if(collideWithPlayer(attRadius) and !collideWithPlayer(enRect) and arduboy.everyXFrames(5) and !solidCollisionWith(enRect,10)) { //Attack the player
            if(player.x < en[x].x and !collideWithTile(eLRect,false)) en[x].x--;
            if(player.x > en[x].x and !collideWithTile(eRRect,false)) en[x].x++;
            if(player.y < en[x].y and !collideWithTile(eURect,false)) en[x].y--;
            if(player.y > en[x].y and !collideWithTile(eDRect,false)) en[x].y++;
          }if(arduboy.everyXFrames(82)) {
            createProjectile(en[x].x + 1, en[x].y + 1, (player.x < en[x].x ? -2 : (player.x > en[x].x ? 2 : 0)), (player.y < en[x].y ? -2 : (player.y > en[x].y ? 2 : 0)), 2);
          }break;
        case 5: //Mrk
          if(arduboy.everyXFrames(6)) {
            if(player.x < en[x].x) en[x].x--;
            if(player.x > en[x].x) en[x].x++;
            if(player.y < en[x].y) en[x].y--;
            if(player.y > en[x].y) en[x].y++;
          }if(collideWithPlayer(enRect)) en[x].exist = false;
          break;
      }Sprites::drawOverwrite(en[x].x,en[x].y,en[x].image,0);
    }
  }updateProjectiles();
}

void damageEnemy(Rect r, uint8_t a) {
  for(uint8_t x; x < 4; x++) {
    Rect enRect = Rect {en[x].x, en[x].y, 8, 8};
    if(arduboy.collide(r, enRect)) {
      en[x].hlth -= a;
      if(en[x].hlth < 1) {en[x].exist = false; killed[en[x].id] = true; dropRandomItem();}
      for(uint8_t y; y < 4; y++) {
        if(collideWithTile(enRect,false) and (en[x].type == 4 ? !solidCollisionWith(enRect,10) : true)) break;
        en[x].x += player.dir % 2 == 0 ? (player.dir == 0 ? 1 : -1) : 0;
        en[x].y += player.dir % 2 == 1 ? (player.dir == 1 ? 1 : -1) : 0;
      }
    }
  }
}

#endif
