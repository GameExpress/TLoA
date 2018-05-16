#ifndef collision_h
#define collision_h

bool collideWithTile(Rect r, bool canSwim) {
  for(uint8_t x; x < 96; x++) {
    uint8_t blck = getBlock(x%12,x/12);
    if(blck != 6 and blck != 14 and (canSwim ? blck != 1 : true)) {
      Rect tileRect = Rect {x % 12 * 8, x / 12 * 8, 8, 8};
      if(arduboy.collide(r, tileRect)) return true;
    }
  }return false;
}

bool solidCollisionWith(Rect r, uint8_t ID) {
  for(uint8_t x; x < 96; x++) {
    if(getBlock(x%12,x/12) == ID) {
      Rect tileRect = Rect {x % 12 * 8, x / 12 * 8, 8, 8};
      if(arduboy.collide(r, tileRect)) return true;
    }
  }return false;
}

Rect playerRect() {
  return Rect {player.x, player.y, 8, 8};
}

bool collideWithPlayer(Rect r) {
  return arduboy.collide(r, playerRect());
}

uint8_t hA;
uint8_t s;

void triggerHurt(uint8_t a, uint8_t side) {
  hA = a;
  s = side;
}

uint8_t hurtByEnemy() {
  return hA;
}

uint8_t sideHurt() {
  return s;
}

#endif
