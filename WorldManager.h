#ifndef worldmanager_h
#define worldmanager_h

void changeMap() {
  despawnAllEnemies();
  spawnEnemies();
  for(int x = 0; x < 48; x++){
    curLvl[x] = pgm_read_byte(&levels[Map][x]);
    if(getBlock(x%12,x/12) == 14) {
      for(uint8_t y = 0; y < DOOR_NUM; y++) {
        if(x%12 == doorLoc[y][0] and x/12 == doorLoc[y][1] and doorLoc[y][2] == Map and unlocked[y]) {
          if(x % 2 == 0) {
            curLvl[x / 2] = 0x60 + getBlock((x+1)%12,x/12);
          }else{
            curLvl[x / 2] = (getBlock((x-1)%12,x/12) << 4) + 0x06;
          }
        }
      }
    }
  }
}

void mapControl(char dir) {
  switch (dir) {
    case 0:
      return;
    case 1:
      Map--;
      break;
    case 2:
      Map++;
      break;
    case 3:
      Map-= (player.mapState == 0 ? 7 : 2);
      break;
    case 4:
      Map+= (player.mapState == 0 ? 7 : 2);
      break;
  }
  if(dir != 0) changeMap();
}

void triggerMap(uint8_t x, uint8_t y, uint8_t m, uint8_t st) {
  player.x = x;
  player.y = y;
  Map = m;
  player.mapState = st;
}

void enterTrigger() {
  delay(320);
  switch (Map) {
    case 17:
      triggerMap(8,24,37,1);
      break;
    case 37:
      triggerMap(64,24,17,0);
      break;
    case 30:
      triggerMap(8,24,41,1);
      break;
    case 41:
      triggerMap(80,40,30,0);
      break;
    case 28:
      triggerMap(48,8,44,1);
      break;
    case 44:
      triggerMap(40,48,28,0);
      break;
  }changeMap();
}

#endif
