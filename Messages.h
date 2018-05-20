#ifndef messages_h
#define messages_h

uint8_t messageDuration;
String message;

void createFoundLootMessage(uint8_t t) {
  messageDuration = 60;
  switch (t) {
    case 0:
      message = "You found coins.";
      break;
    case 1:
      message = "You found gems.";
      break;
    case 2:
      message = "You found a key.";
      break;
    case 3:
      message = "You got a heart.";
      break;
    case 4:
      message = "You obtained:   \nUnbreaking";
      break;
    case 5:
      message = "You obtained:   \nMending";
      break;
    case 6:
      message = "You obtained:   \nHeart boost";
      break;
    case 7:
      message = "You acquired:   \nSwimming";
      break;
    case 8:
      message = "You acquired:   \nSword Melting";
      break;
    case 9:
      message = "You acquired:   \nTeleportation";
  }
}

void createMessage(String m) {
  messageDuration = 60;
  message = m;
}

void displayMessage() {
  if(messageDuration > 0) {
    messageDuration--;
    arduboy.setCursor(0,0);
    arduboy.print(message);
  }
}

#endif
