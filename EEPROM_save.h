#ifndef eeprom_save_h
#define eeprom_save_h
#define save_space EEPROM_STORAGE_SPACE_START + 240
#define cl_save_space save_space + 2
#define ch_save_space cl_save_space + 3
#define ul_save_space ch_save_space + CHEST_NUM

void saveGame() {
  //UPDATE CHARACTERS FOR GAME
  EEPROM.update(save_space, 'L');
  EEPROM.update(save_space + 1, 'A');
  //SAVE ALL COLLECTABLES (coins, gems, keys, etc.)
  EEPROM.put(cl_save_space, player.coins);
  EEPROM.put(cl_save_space + 1, player.gems);
  EEPROM.put(cl_save_space + 2, player.keys);
  //SAVE ALL OPENED CHESTS
  for(uint8_t x = 0; x < CHEST_NUM; x++) {
    EEPROM.put(ch_save_space + x, opened[x]);
  }
  //SAVE ALL UNLOCKED DOORS
  for(uint8_t x = 0; x < DOOR_NUM; x++) {
    EEPROM.put(ul_save_space + x, unlocked[x]);
  }
}

void loadGame() {
  //CHECK IF A SAVE FILE EXISTS
  if(EEPROM.read(save_space) != 'L' or EEPROM.read(save_space + 1) != 'A') return;
  //LOAD ALL COLLECTABLES (coins, gems, keys, etc.)
  player.coins = EEPROM.read(cl_save_space);
  player.gems = EEPROM.read(cl_save_space + 1);
  player.keys = EEPROM.read(cl_save_space + 2);
  //LOAD ALL OPENED CHESTS
  for(uint8_t x = 0; x < CHEST_NUM; x++) {
    opened[x] = EEPROM.read(ch_save_space + x);
  }
  //LOAD ALL UNLOCKED DOORS
  for(uint8_t x = 0; x < DOOR_NUM; x++) {
    unlocked[x] = EEPROM.read(ul_save_space + x);
  }
}

void deleteGame() {
  EEPROM.update(save_space, (unsigned char)0);
  EEPROM.update(save_space + 1, (unsigned char)0);
}

#endif
