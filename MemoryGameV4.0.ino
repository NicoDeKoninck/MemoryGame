int led1 = 6;
int led2 = 7;
int led3 = 8;
int led4 = 9;

int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;
int startButton = 10;

int buzzer = 11;

int sol1 = 0;
int sol2 = 0;
int sol3 = 0;
int sol4 = 0;

int input1 = 0;
int input2 = 0;
int input3 = 0;
int input4 = 0;

int buttonPressed = 6;
int difficulty = 1;
int ledSpeed = 1000;
int score = 0;

boolean changingDifficulty = false;
boolean gameActive = false;
boolean displayedSolution = false;
boolean waitingInput = false;
boolean victory = false;
boolean defeat = false;

void setup() {
  Serial.begin(9600);
  
  for(int i = 6; i < 10; ++i){ // Initializing all leds
    pinMode(i, OUTPUT);
  }

  for(int i = 2; i < 6; ++i){ // Initialzing all buttons
    pinMode(i, INPUT);
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(startButton, INPUT);
  pinMode(startButton, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

}

void loop() {
  checkStartButton();
  while(changingDifficulty == true){
    displayDifficulty();
    changeDifficulty();
    checkButtonsPressed();
    if(buttonPressed == 5){
      changingDifficulty = false;
      gameActive = true;
    }
  }
  while(gameActive == true){
    Serial.println("The game has started");
    allLedsOut();
    Solution();
    displaySolution();
    if(displayedSolution == true){
      waitingInput = true;
    }
    while(waitingInput == true){
      input1 = getUserInput();
      input2 = getUserInput();
      input3 = getUserInput();
      input4 = getUserInput();
      waitingInput = false;
    }
    checkInput();
    if(victory == true){
      tone(buzzer, 1000, 500);
      delay(1000);
      tone(buzzer, 1000, 500);
      delay(1000);
      tone(buzzer, 1000, 500);
      delay(1000);
      tone(buzzer, 1000, 500);
      delay(1000);
      Serial.println("You won");
      Serial.println("The game is now over");
      delay(5000);
      victory = false;
      score = 0;
      sol1 = 0;
      sol2 = 0;
      sol3 = 0;
      sol4 = 0;
      input1 = 0;
      input2 = 0;
      input3 = 0;
      input4 = 0;
      gameActive = false;
    }
    if(defeat == true){
      tone(buzzer, 500, 1000);
      delay(2000);
      tone(buzzer, 500, 1000);
      Serial.println("You lost with the following score:");
      Serial.println(score);
      Serial.println("The game is now over");
      delay(5000);
      defeat = false;
      score = 0;
      sol1 = 0;
      sol2 = 0;
      sol3 = 0;
      sol4 = 0;
      input1 = 0;
      input2 = 0;
      input3 = 0;
      input4 = 0;
      gameActive = false;
    }
  }
}

void checkButtonsPressed(){ // This function will check all buttons if they are pressed or not
  if(digitalRead(button1) == HIGH){
    buttonPressed = 1;
  }
  else if(digitalRead(button2) == HIGH){
    buttonPressed = 2;
  }
  else if(digitalRead(button3) == HIGH){
    buttonPressed = 3;
  }
  else if(digitalRead(button4) == HIGH){
    buttonPressed = 4;
  }
  else if(digitalRead(startButton) == HIGH){
    buttonPressed = 5;
  }
  else{
    buttonPressed = 6;
  }
}

void checkStartButton(){ // This function will check if the start button has been pressed longer then 5 seconds
  checkButtonsPressed();
  int held = 0;
  while(digitalRead(startButton) == HIGH && held <100){
      delay(100);
      held++;
      
      if(held < 50){
        changingDifficulty = false;
        gameActive = true;
      }else{
        changingDifficulty = true;
      }
    }
}

void displayDifficulty(){ // This function will display the current difficulty
  switch(difficulty){
    case 1:
      digitalWrite(led1, HIGH);
      for(int i = 7; i < 10; ++i){
        digitalWrite(i, LOW);
      }
      break;
    case 2:
      for(int i = 6; i < 8; ++i){
        digitalWrite(i, HIGH);
      }
      for(int i = 8; i < 10; ++i){
        digitalWrite(i, LOW);
      }
      break;
    case 3:
      for(int i = 6; i < 9; ++i){
        digitalWrite(i, HIGH);
      }
      digitalWrite(led4, LOW);
      break;
    case 4:
      for(int i = 6; i < 10; ++i){
        digitalWrite(i, HIGH);
      }
      break;
  }
}

void changeDifficulty(){ // This function will change the difficulty
  checkButtonsPressed();
  switch(buttonPressed){
    case 1:
      difficulty = 1;
      break;
    case 2:
      difficulty = 2;
      break;
    case 3:
      difficulty = 3;
      break;
    case 4:
      difficulty = 4;
      break;
    default:
      difficulty = difficulty;
      break;
  }
  changeLedSpeed();
}

void changeLedSpeed(){ // This function will change the duration that the led is active
  
  switch(difficulty){
    case 1:
      ledSpeed = 1000;
      break;
    case 2:
      ledSpeed = 750;
      break;
    case 3:
      ledSpeed = 500;
      break;
    case 4:
      ledSpeed = 250;
      break;
  }
}

void checkInput(){
  if(input1 == sol1){
    ++score;
  }
  if(input2 == sol2){
    ++score;
  }
  if(input3 == sol3){
    ++score;
  }
  if(input4 == sol4){
    ++score;
  }
  if(score == 4){
    victory = true;
  }else{
    defeat = true;
  }
}

int getUserInput(){ // This function will get the users input
  boolean btnPressed = false;
  int result = 0;
  int held = 0;
  while(btnPressed == false){
    while(digitalRead(button1) == HIGH && held <10){
      delay(100);
      held++;
      
      if(held < 10){
        result = button1 - 1;
        btnPressed = true;
      }
    }
    while(digitalRead(button2) == HIGH && held <10){
      delay(100);
      held++;
      
      if(held < 10){
        result = button2 - 1;
        btnPressed = true;
      }
    }
    while(digitalRead(button3) == HIGH && held <10){
      delay(100);
      held++;
      
      if(held < 10){
        result = button3 - 1;
        btnPressed = true;
      }
    }
    while(digitalRead(button4) == HIGH && held <10){
      delay(100);
      held++;
      
      if(held < 10){
        result = button4 - 1;
        btnPressed = true;
      }
    }
  }
  return result;
}

void displaySolution(){ // This function will display the random order of leds
  digitalWrite(sol1 + 5, HIGH);
  delay(ledSpeed);
  digitalWrite(sol1 + 5, LOW);
  digitalWrite(sol2 + 5, HIGH);
  delay(ledSpeed);
  digitalWrite(sol2 + 5, LOW);
  digitalWrite(sol3 + 5, HIGH);
  delay(ledSpeed);
  digitalWrite(sol3 + 5, LOW);
  digitalWrite(sol4 + 5, HIGH);
  delay(ledSpeed);
  digitalWrite(sol4 + 5, LOW);
  displayedSolution = true;
}

void Solution(){ // This function will fetch 4 random values
  sol1 = randomNumber();
  sol2 = randomNumber();
  sol3 = randomNumber();
  sol4 = randomNumber();
}

int randomNumber(){ // This function will generate a random number between 0 and 4
  return random(1,5);
}

void allLedsOut(){ // This function will dim all leds
  for(int i = 1; i < 5; ++i){
    digitalWrite(i + 5, LOW);
  }
}

