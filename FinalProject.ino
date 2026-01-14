
#include <LedControl.h>
#include "Numbers.h"

int motor = 9;

// variables for lc control
int DIN = 11;
int CS = 7;
int CLK = 13;
LedControl lc = LedControl(DIN, CLK, CS, 2);

int btnPins[] = { 5, 4, 3, 2 };
int guesses[4] = { 0, 0, 0, 0 };
int password[4] = { 6, 7, 6, 7 };

int passBtnPin = 8;

int buttonState;
int passBtnState;

// grid to create number designs universally
int grid[8];

// variables for numbers
int* left;
int* right;




void setup() {
  //LC SET UP
  lc.shutdown(0, false);  // When the device comes out of shutdown mode the same Leds will be lit as before it went to sleep
  lc.shutdown(1, false);
  lc.setIntensity(0, 1);  // set brightness
  lc.setIntensity(1, 1);

  pinMode(btnPins[0], INPUT);
  pinMode(btnPins[1], INPUT);
  pinMode(btnPins[2], INPUT);
  pinMode(btnPins[3], INPUT);

  pinMode(passBtnPin, INPUT);
}

void loop() {
  printGrid(0, guesses[0], guesses[1]);
  printGrid(1, guesses[2], guesses[3]);
  passwordChecker();
  btnRead();
}

void printGrid(int gridselectnum, int leftnum, int rightnum) {
  buildGrid(numbers[leftnum], numbers[rightnum]);
  gridselectorprnt(gridselectnum);
}

void buildGrid(int leftnum[], int rightnum[]) {
  for (int i = 0; i < 8; i++) {
    grid[i] = leftnum[i] | rightnum[i] >> 4;
  }
}

void gridselectorprnt(int gridselectnum) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(gridselectnum, i, grid[i]);
  }
}


void btnRead() {

  for (int i = 0; i < 4; i++) {
    buttonState = digitalRead(btnPins[i]);
    delay(25);
    if (buttonState == HIGH) {
      guesses[i] = guesses[i] + 1;
      if (guesses[i] > 9) {
        guesses[i] = 0;
      }
    }
  }
}


// void passwordChecker() {
//   passBtnState = digitalRead(passBtnPin);
//   if (passBtnState == HIGH) {
//     for (int i = 0; i < 4; i++) {
//       if (numbers[guesses[i]] == password[i]) {
//         Serial.println("Correct!");
//       }
//     }
//   }
// }
