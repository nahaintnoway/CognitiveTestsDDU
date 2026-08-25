enum Game { GAME_NONE, GAME_REACTION, GAME_MEMORY };
Game currentGame = GAME_NONE;

void setup() {
  Serial.begin(9600);
  printMenu();
}

void loop() {
  if(currentGame==GAME_NONE){
    if(Serial.available() > 0){
      char choice = Serial.read();
      if(choice=='1'){
        currentGame = GAME_REACTION;
        Serial.println("Starting Reaction Test...");
        reactionSetup();
      } else if(choice=='2'){
        currentGame = GAME_MEMORY;
        Serial.println("Starting Memory Game...");
        memorySetup();
      }
    }
    return;
  }

  if(currentGame==GAME_REACTION){
    reactionLoop();
  } else if(currentGame==GAME_MEMORY){
    memoryLoop();
  }
}

void printMenu(){
  Serial.println("Select a game:");
  Serial.println("1) Reaction Test");
  Serial.println("2) Memory Game");
}
