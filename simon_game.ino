int memory_buttonLightTime=-1;
const int NUM_BUTTONS=3;
const int SLEEP_BETWEEN_CORRECT_DISPLAY=500;
const int pattern_length=4;
int ledPins[]={2,4,6};
int buttonPins[]={3,5,7};
int correctPath[pattern_length];
int userPath[pattern_length];
int currentIndex=-1;
bool memory_gameStarted=false;

void memorySetup() {
  for(int i = 0; i < NUM_BUTTONS; i++){
    pinMode(ledPins[i],OUTPUT);
    digitalWrite(ledPins[i], LOW);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(A0));
  currentIndex=-1;
  memory_gameStarted=true;
}

void memoryLoop() {
  if(currentIndex==-1){
    generatePath(correctPath, pattern_length);
    for(int i = 0; i < pattern_length; i++){
      digitalWrite(correctPath[i],HIGH);
      delay(SLEEP_BETWEEN_CORRECT_DISPLAY);
      digitalWrite(correctPath[i],LOW);
      delay(SLEEP_BETWEEN_CORRECT_DISPLAY);
    }
    currentIndex = 0;
  }
  else if(currentIndex<pattern_length && currentIndex != -1){
    for(int i = 0; i < NUM_BUTTONS; i++){
      if(digitalRead(buttonPins[i])==LOW){
        userPath[currentIndex]=ledPins[i];
        currentIndex++;
        while(digitalRead(buttonPins[i])==LOW);
        break;
      }
    }

  }
  else if (currentIndex==pattern_length) {
    Serial.print("your path: ");
    for(int i = 0; i < pattern_length; i++) {
      Serial.print(String(userPath[i]) + " ");
    }
    Serial.println("Correct path: ");
    for(int i = 0; i < pattern_length; i++) {
      Serial.print(String(correctPath[i]) + " ");
    }
    bool wrongOrder = false;
    for (int i = 0; i < pattern_length; i++)  {
      if (correctPath[i] != userPath[i]) {
        // forkert
        wrongOrder = true;
        for (int i = 0; i < 3; i++)  {
          for (int j = 0; j < NUM_BUTTONS; j++) {
            digitalWrite(ledPins[j], HIGH);
          }
          delay(800);
          for (int j = 0; j < NUM_BUTTONS; j++) {
            digitalWrite(ledPins[j], LOW);
          }
          delay(800);
        }
        break;
      }
    }
    if(!wrongOrder) {
      // rigtigt
        for (int i = 0; i < 3; i++)  {
          for (int j = 0; j < NUM_BUTTONS; j++) {
            digitalWrite(ledPins[j], HIGH);
          }
          delay(100);
          for (int j = 0; j < NUM_BUTTONS; j++) {
            digitalWrite(ledPins[j], LOW);
          }
          delay(100);
        }
    }
    currentIndex=-1;
    delay(400);
  }
}

void generatePath(int arr[], int size){
  for(int i = 0; i < size; i++) {
    arr[i] = ledPins[random(0, NUM_BUTTONS)];
    Serial.println("Path " + String(i) + " = " + String(arr[i]));
  }
}
