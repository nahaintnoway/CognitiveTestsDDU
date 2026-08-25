
int buttonLightTime=-1;
const int BUTTON_IN=7;
const int BUTTON_LED_OUT=6;

void reactionSetup() {
  pinMode(BUTTON_IN,INPUT);
  pinMode(BUTTON_LED_OUT,OUTPUT);
  buttonLightTime=-1;
}

void reactionLoop() {
  if(buttonLightTime==-1){
       delay(70);
    if(random(0, 100) <= 1){
      buttonLightTime=millis();
      digitalWrite(BUTTON_LED_OUT,HIGH);
      Serial.println("Click!");

    }

  } else{
    if(digitalRead(BUTTON_IN)==0){
      int delta=millis()-buttonLightTime;
      Serial.println("Your reaction time was: "+String(delta)+" ms");
      buttonLightTime=-1;
      analogWrite(BUTTON_LED_OUT,LOW);
    }
  }
}

void shuffleArray(int arr[], int size){
  for(int i = size -1; i > 0; i--) {
    int j = random(0, i + 1);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}
