
#include "printerCutter.h"

volatile bool xMoving = false;
volatile bool yMoving = false;
int16_t destLocX = 0;
int16_t destLocY = 0;
volatile int16_t currentLocX = 0;
volatile int16_t currentLocY = 0;
float currentLocZ = 0;
bool absolute = false;

void setAbsolutePositioning(bool ab){
  absolute = ab;
}

void handleXEncoderA(void)
{
  currentLocX++;
  if (currentLocX == destLocX) {
    digitalWrite(MOTORX_PIN_DIR0, HIGH);
    digitalWrite(MOTORX_PIN_DIR1, HIGH);  
    xMoving = false;
    Serial.print(currentLocX);
    Serial.print("   ");
    Serial.println(destLocX);
  }
}

void handleXEncoderB(void)
{
  currentLocX--;
  if (currentLocX == destLocX) {
    digitalWrite(MOTORX_PIN_DIR0, HIGH);
    digitalWrite(MOTORX_PIN_DIR1, HIGH);
    xMoving = false;
  }
}

void handleYEncoderA(void)
{
  currentLocY++;
  if (currentLocY == destLocY) {
   digitalWrite(MOTORY_PIN_DIR0, HIGH);
   digitalWrite(MOTORY_PIN_DIR1, HIGH);
   yMoving = false;
  }
}

void handleYEncoderB(void)
{
  currentLocY--;
  if (currentLocY == destLocY) {
    digitalWrite(MOTORY_PIN_DIR0, HIGH);
    digitalWrite(MOTORY_PIN_DIR1, HIGH);
    yMoving = false;
  }
}

void setMotorSpeed(uint8_t motor, uint8_t spd){
  if(motor){
     analogWrite(MOTORX_PIN_PWM, spd);
  }else{
     analogWrite(MOTORY_PIN_PWM, spd);
  }
 
}


void setMotorDir(uint8_t motor, uint8_t dir){
  if(motor == MOTORX){
    detachInterrupt(digitalPinToInterrupt(ENCODERX_PIN_A));
    detachInterrupt(digitalPinToInterrupt(ENCODERX_PIN_B));
  }else{
    detachInterrupt(digitalPinToInterrupt(ENCODERY_PIN_A));
    detachInterrupt(digitalPinToInterrupt(ENCODERY_PIN_B)); 
  }
  
  if(dir == STOP){
    if(motor == MOTORX){
      xMoving = false;
      digitalWrite(MOTORX_PIN_DIR0, HIGH);
      digitalWrite(MOTORX_PIN_DIR1, HIGH);
    }else{
      yMoving = false;
      digitalWrite(MOTORY_PIN_DIR0, HIGH);
      digitalWrite(MOTORY_PIN_DIR1, HIGH);
    }
    
  }if(dir == FORWARD){
    if(motor == MOTORX){
      xMoving = true;
      attachInterrupt(digitalPinToInterrupt(ENCODERX_PIN_A), handleXEncoderA, RISING);
      digitalWrite(MOTORX_PIN_DIR0, HIGH);
      digitalWrite(MOTORX_PIN_DIR1, LOW);
    }else{
      yMoving = true;
      attachInterrupt(digitalPinToInterrupt(ENCODERY_PIN_A), handleYEncoderA, RISING);
      digitalWrite(MOTORY_PIN_DIR0, HIGH);
      digitalWrite(MOTORY_PIN_DIR1, LOW);
    }
  }if(dir == BACKWARD){
    if(motor == MOTORX){
      xMoving = true;
      attachInterrupt(digitalPinToInterrupt(ENCODERX_PIN_B), handleXEncoderB, RISING);
      digitalWrite(MOTORX_PIN_DIR0, LOW);
      digitalWrite(MOTORX_PIN_DIR1, HIGH);
    }else{
      yMoving = true;
      attachInterrupt(digitalPinToInterrupt(ENCODERY_PIN_B), handleYEncoderB, RISING);
      digitalWrite(MOTORY_PIN_DIR0, LOW);
      digitalWrite(MOTORY_PIN_DIR1, HIGH);
    }
  }
  
}

//avoid setMotorDir due to interrupt fuckery
void homeX(){
    digitalWrite(MOTORX_PIN_DIR0, LOW);
    digitalWrite(MOTORX_PIN_DIR1, HIGH);
    while(digitalRead(END_STOP_PIN));
    digitalWrite(MOTORX_PIN_DIR0, HIGH);
    currentLocX = 0;
}

void feedY(){
  moveTo(UNUSED,5);
  currentLocY = 0;
}



void eStop(){
  setMotorDir(MOTORY, STOP);
  setMotorDir(MOTORX, STOP);
}

void moveZ(float destZ){
  int steps;
  if(absolute){
    if(destZ>currentLocZ){
      digitalWrite(Z_DIR_PIN, HIGH);
      steps = (abs(destZ) - currentLocZ) ;
    }else if (destZ<currentLocZ){
      digitalWrite(Z_DIR_PIN, LOW);
      steps = ( currentLocZ - abs(destZ)) ;
    }else{
      return;
    }
    currentLocZ = destZ;
  }else{
    if(destZ>0){
      digitalWrite(Z_DIR_PIN, HIGH);
    }else if (destZ<0){
      digitalWrite(Z_DIR_PIN, LOW);
    }else{
      return;
    }
    steps = (abs(destZ)-.15) ;
    currentLocZ = currentLocZ + destZ;
  }

  for( int i = 0; i < steps; i++ ) {
      digitalWrite(Z_STEP_PIN, HIGH);
      delayMicroseconds(800);
      digitalWrite(Z_STEP_PIN, LOW);
      delayMicroseconds(800);
   }
   
}

void moveTo(float destX, float destY){
 uint16_t calcTemp;
  if(destX != UNUSED){
    if(absolute){
      calcTemp = destX * X_STEPS_PER_MM;
      if(calcTemp>=0 && calcTemp < MAX_X_LENGTH){
        destLocX = calcTemp;
      }
    }else{
      calcTemp = currentLocX + destX * X_STEPS_PER_MM;
      if(calcTemp>=0 && calcTemp < MAX_X_LENGTH){
        destLocX = calcTemp;
      }
    }
    if(destLocX>currentLocX){
      setMotorDir(MOTORX, FORWARD);
    }else if(destLocX<currentLocX){
      setMotorDir(MOTORX, BACKWARD);
    }
  }
  if(destY != UNUSED){
    if(absolute){
      destLocY = destY * Y_STEPS_PER_MM;
    }else{
      destLocY = currentLocY + destY * Y_STEPS_PER_MM;
    }
  
    if(destLocY>currentLocY){
      setMotorDir(MOTORY, FORWARD);
    }else if(destLocY<currentLocY){
      setMotorDir(MOTORY, BACKWARD);
    }
  }

}

bool isMoving(){
  if(xMoving || yMoving){
    return true;
  }else{
    return false;
  }
}






