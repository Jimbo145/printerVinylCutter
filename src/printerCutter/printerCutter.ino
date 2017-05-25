
#include "printerCutter.h"



int motorYdir = FORWARD; //0

volatile int encoderYPos = 0;

void setup() {
  
  pinMode(ENCODERY_PIN_A, INPUT);
  pinMode(ENCODERY_PIN_B, INPUT);
  pinMode(ENCODERX_PIN_A, INPUT);
  pinMode(ENCODERX_PIN_B, INPUT);


  pinMode(MOTORY_PIN_DIR0, OUTPUT);
  pinMode(MOTORY_PIN_DIR1, OUTPUT);
  pinMode(MOTORY_PIN_PWM, OUTPUT);

  pinMode(MOTORX_PIN_DIR0, OUTPUT);
  pinMode(MOTORX_PIN_DIR1, OUTPUT);
  pinMode(MOTORX_PIN_PWM, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  
  //digitalWrite(MOTORY_PIN_DIR0, HIGH);
  //digitalWrite(MOTORY_PIN_DIR1, LOW);
  //analogWrite(MOTORY_PIN_PWM, 100);

  pinMode(END_STOP_PIN, INPUT_PULLUP);
  //digitalWrite(STEP_PIN, LOW);

  //pinMode(30, OUTPUT);

  setMotorSpeed(0, 165);
  setMotorSpeed(1, 165);
  initSerial();


  Commands::commandLoop();
}

int cnt = 1;
void loop() {
  
  
}


