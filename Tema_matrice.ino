 
#include <LedControl.h> 
#include <LiquidCrystal.h>

LedControl lc = LedControl(11, 13, 10, 1); 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define V0_PIN 9

#define SW_PIN 51 // digital pin connected to switch output
#define joyPin1 A0 // analog pin connected to X output
#define joyPin2 A1 //analog pin connected to Y output

const int buttonPin = 53;     // the number of the pushbutton pin
int buttonState = LOW; 

int xAxis = 0;
int yAxis = 0;

String direction; //Variable that stores the direction the snake is moving in.

int snakeX[36]; //Variable that stores all the x coordinates of the snake.
int snakeY[36]; //Variable that stores all the y coordinates of the snake.

int speed; //Delay time for each movement.

int snakeSize; 

int foodX; //Variable that stores the x coordinate of the food.
int foodY; //Variable that stores the y coordinate of the food.

boolean inGame = false; //Variable that tells us if the game is running.
int score = 0; 
int life = 3;
int period;
unsigned long timeNow = 0;
void setup() { 
    pinMode(V0_PIN, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP); 
    analogWrite(V0_PIN, 90);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SNAKE GAME");
    period = 2000;
    timeNow = millis();
    while(millis() < timeNow + period);
    lcd.setCursor(3, 0);
    lcd.print("PRESS START");
    lcd.setCursor(3, 1);
    lcd.print("TO PLAY");
    period = 2000;
    timeNow = millis();
    while(millis() < timeNow + period);
    lc.shutdown(0, false); //Turn off power saving, enables display
    lc.setIntensity(0, 8); //Brightness (0-15)
    lc.clearDisplay(0); //Clear Screen
    Serial.begin(9600);
    while(digitalRead(buttonPin) == LOW);
      newGame(); //setup everything
}

void loop() {
    if(inGame) { //Checks if game is running. 
        lc.clearDisplay(0); //Clear screen
        
        xAxis = analogRead(joyPin1); 
        yAxis = analogRead(joyPin2); 
      
        Serial.println(xAxis); //Prints the x axis to the serial for debugging.
        Serial.println(yAxis); //Prints the y axis to the serial for debugging.
        
        if(yAxis > 600 && direction != "up") { //If player moves the analog stick up, and if snake isn't going down.
            direction = "up";
        }
        if(yAxis < 400 && direction != "down") { //If player moves the analog stick down, and if snake isn't going up.
            direction = "down";
        }
        if(xAxis > 600 && direction != "right") { //If player moves the analog stick right, and if snake isn't going left.
            direction = "right";
        }
        if(xAxis < 400 && direction != "left") { //If player moves the analog stick left, and if snake isn't going right.
            direction = "left";
        }
        
        move(direction); //Move the snake in the direction.
        
        checkIfHitFood(); //Checks if the snake moves onto the food.
        checkIfHitSelf(); //Checks if the snake hits itself.
        
        drawSnake(); //Draws the snake on the MAX7219.
        drawFood(); //Draws the food on the MAX7219.
        //lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("SCORE: ");
        lcd.print(score);
        lcd.setCursor(3, 1);
        lcd.print("LIFE: ");
        lcd.print(life);
        timeNow = millis();
        while(millis() < timeNow + speed);
    }
}
void newGame() {
    for(int i=0; i<36; i++) { //Sets all the values in the snake array to be off the screen
        snakeX[i] = -1;
        snakeY[i] = -1;
    }
    snakeX[0] = 4; 
    snakeY[0] = 8; 
    direction = "up"; //Start with moving upward.
    snakeSize = 1; //Start with only 1 snake part. (Which is the snake head)
    newFood(); //Randomly create a new food.
    inGame = true; //Set this variable to true so the loop() method could start.
    speed = 900;
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("NEW GAME");
    period = 2000;
    timeNow = millis();
    while(millis() < timeNow + period);
}
void newFood() {
    int newFoodX = random(0, 8);
    int newFoodY = random(0, 8);
    while(isSnake(newFoodX, newFoodY)){ //If the new food coordinates are in the snake, then keep trying until they're not.
        newFoodX = random(0, 8);
        newFoodY = random(0, 8);
    }
    foodX = newFoodX;
    foodY = newFoodY;
}
//Checks if the given coordinates are part of the snake.
//Used when checking where to generate new food.
boolean isSnake(int x, int y){
    for(int i=0; i<snakeSize-1; i++){
        if((x == snakeX[i]) && (y == snakeY[i])){
            return true;
        }
    }
    return false;
}
//This method makes the snake move in the direction provided in the param.
void move(String dir) {
    for(int i=snakeSize-1; i>0; i--){ //Go through all the snake body parts (excluding the head), and set it to the previous position.
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }

    if(dir == "up") {
  if(snakeY[0] == 0) { //If snake tries to get out of bounds, teleport him on the opposite side.
      snakeY[0] = 7;
  } else {
            snakeY[0]--;
  }
    } else if(dir == "down") {
  if(snakeY[0] == 7) { 
      snakeY[0] = 0;
  } else {
      snakeY[0]++;
        }
    } else if(dir == "left") {
  if(snakeX[0] == 0) { 
      snakeX[0] = 7;
  } else {
      snakeX[0]--;
  }
    } else if(dir == "right") {
  if(snakeX[0] == 7) {
      snakeX[0] = 0;
  } else {
      snakeX[0]++;
  }
    }
}
//This method checks if the snake moves onto the food.
void checkIfHitFood() {
    if(snakeX[0] == foodX && snakeY[0] == foodY) {
  snakeSize++; //Add a snake body part.
  speed = speed - 100;
  score = score + 10;
  newFood(); //Create a new food at a new location.
    }
}
//This method checks if the snake moves onto itself.
void checkIfHitSelf() {
    for(int i=1; i<snakeSize-1; i++){
  if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      life--;
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER");
      period = 2000;
      timeNow = millis();
      while(millis() < timeNow + period);
      gameOver();
  }
    }
}
//This method is called when the snake hits itself.
void gameOver() {
    inGame = false; //Makes sure the game is stopped.
    for(int x=0; x<8; x++) {
       for(int y=0; y<8; y++) {
           lc.setLed(0, y, x, true);
           period = 20;
            timeNow = millis();
            while(millis() < timeNow + period);
           lc.setLed(0, y, x, false);
       }
    }
    if(life == 0){
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Score: ");
    lcd.print(score);
    period = 2000;
    timeNow = millis();
    while(millis() < timeNow + period);
    lcd.setCursor(3, 0);
    lcd.print("PRESS START");
    lcd.setCursor(3, 1);
    lcd.print("TO PLAY");
    period = 2000;
    timeNow = millis();
    while(millis() < timeNow + period);
    while(digitalRead(buttonPin) == LOW);
    life = 3;
    score = 0;
    newGame();
    }
    else
    {
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("Score: ");
      lcd.print(score);
      period = 2000;
      timeNow = millis();
      while(millis() < timeNow + period);
      newGame();
    }
}
//This method loops through all the snake parts and draws them on the matrix.
void drawSnake() {
    for (int i = 0; i < snakeSize; i++) {
        lc.setLed(0, snakeY[i], snakeX[i], true);
    }
}

//This method draws the food on the matrix.
void drawFood() {
    lc.setLed(0, foodY, foodX, true);
    period = 50;
    timeNow = millis();
    while(millis() < timeNow + period); 
    //Have a short delay here to make the food blink and differentiate from the snake parts.
    lc.setLed(0, foodY, foodX, false);
}
