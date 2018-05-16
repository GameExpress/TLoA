#ifndef messages_h
#define messages_h

uint8_t messageDuration;
String message;

void createFoundLootMessage(uint8_t t, uint8_t q) {
  messageDuration = 60;
  switch (t) {
    case 0:
      if(q == 1) message = "You found a coin";
      else message = "You found coins.";
      break;
    case 1:
      if(q == 1) message = "You found a gem.";
      else message = "You found gems.";
      break;
    case 2:
      message = "You found a key.";
      break;
    case 3:
      message = "You got a heart.";
      break;
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
