#include <TimerOne.h>
#include <EEPROM.h>
#include "ShieldLib.h"
#include "pid.h"
#include "mapeo.h"
#include "buttonMachines.h"

///////////////pid CONSTANTS///////////////
//float escapeTurnTimeChoice[2] = {500, 500};
//float turnTimeChoice[2] = {100, 50};
float KPchoice[2] = {80, 100}; //17                           //Elección de constante proporcional del PID
float KDchoice[2]  = {1, 500}; //0.5                          //Elección de constante derivada del PID
float velocityChoice[2] = {500, 800}; //150                   //Elección de velocidad
float delayChoice[2] = {400, 275};
//float multChoice [2] = {1.4, 1.8};
//float mult;
float KP , KD, tiempoDelay;
float velocity;                                               
////////////////////////
///////////////////
//long mainMillis;
long mazeMillis;
char estadoMain;
char estadoCases;
void mazeMachine(void);
void mazeCases(void);
String movements;                                             //String en el que se guardarán los movimientos realizados

///////////////////////////////////////////

void setup() {
  inicializar();                                              

}

void loop() {
  mazeMachine();
  buttonOneMachine();
  buttonTwoMachine();
  buttonThreeMachine();
}


void mazeMachine(void) {
  switch (estadoMain) {
    case WAIT:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      if (1 == button1Flag && button2Flag == 0) {
        button1Flag = 0;
        velocity = velocityChoice[SLOW];
        KP = KPchoice[SLOW];
        KD = KDchoice[SLOW];
        //mult = multChoice[SLOW];
        tiempoDelay = delayChoice[SLOW];
        //turnTime = turnTimeChoice[SLOW];
        //escapeTurnTime = escapeTurnTimeChoice[SLOW];
        estadoMain = FIRST_RUN;
      }
      else if (button2Flag == 1 && button1Flag == 0) {
        button2Flag = 0;
        velocity = velocityChoice[FAST];
        KP = KPchoice[FAST];
        KD = KDchoice[FAST];
        //mult = multChoice[FAST];
        tiempoDelay = delayChoice[FAST];
        //turnTime = turnTimeChoice[FAST];
        //escapeTurnTime = escapeTurnTimeChoice[FAST];
        estadoMain = FIRST_RUN;
        digitalWrite(LED2, HIGH);
      }
      else if(button3Flag == 1 && button1Flag == 0 && button2Flag == 0){
        readEeprom();
        estadoMain = SECOND_RUN;
      }
      break;
    case FIRST_RUN:
      if ((analogRead(SENFLOOR2) < VALORBLANCO1))
      {
        mazeMillis = 0;
        while(mazeMillis<tiempoDelay){
          setMotors(velocity, velocity);
        }
        setMotors(0, 0);
        digitalWrite(LED1, LOW);
        mapGenerator();
        estadoMain = WAIT;
      }
      else if (button1Flag) {
        button1Flag = 0;
        setMotors(0, 0);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED1, LOW);
        estadoMain = WAIT;
      }
      else {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        mazeCases();

      }
      break;
    case SECOND_RUN:
      if(LEFT_FREE){
        if(FRONT_FREE || RIGHT_FREE){
          readMovements(finalMovements);
        }
        else{
          turnLeft90(velocity);
          moveCell(velocity);
        }
      }
      else if (FRONT_FREE && RIGHT_FREE){
        readMovements(finalMovements);  
      }
      else if(FRONT_FREE){
         moveCell(velocity); 
      }
      else if(RIGHT_FREE){
        turnRight90(velocity);
        moveCell(velocity);
      }
      else{
        turn180(velocity);
      }
      break;
  }
}

void mazeCases(void) {
  switch (estadoCases) {
    case START:
      if (LEFT_FREE) {
        setMotors(-velocity, velocity);
        estadoCases = LEFT_NOO;
        mazeMillis = 0;
        resetTicks();
      }
      else if (FRONT_FREE) {
        moveStraight();
        estadoCases = FRONT_NOO;
        mazeMillis = 0;
        resetTicks();
      }
      else if (RIGHT_FREE) {
        setMotors(velocity, -velocity);
        estadoCases = RIGHT_NOO;
        mazeMillis = 0;
      }
      else {
        setMotors(velocity, -velocity);
        estadoCases = NO_OPTION;
        mazeMillis = 0;
      }
      break;
    case LEFT_NOO:
      if (getEncoderDistance(LEFT) > LEFT_TURN90) {
        movements += 'L';
        mazeMillis = 0;
        setMotors(0, 0);
        resetTicks();
        estadoCases = POST_TURN;
      }
      break;
    case POST_TURN:
      if (getEncoderDistance(LEFT) > CELL) {
        setMotors(velocity,-velocity);
        movements += 'F';
        estadoCases = START;
      }
      break;
    case FRONT_NOO:
      if (getEncoderDistance(LEFT) > CELL) {
        setMotors(0, 0);
        movements += 'F';
        estadoCases = START;
      }
      break;
    case RIGHT_NOO:
      if (getEncoderDistance(LEFT) > RIGHT_TURN90) {
        movements += 'R';
        mazeMillis = 0;
        setMotors(0, 0);
        estadoCases = POST_TURN;
      }
      break;
    case NO_OPTION:
      if (getEncoderDistance(LEFT)> TURN_180) {
        estadoCases = START;
      }
      break;
  }
}
void timer() {
  //mainMillis += 1;
  button1Millis += 1;
  button2Millis += 1;
  mazeMillis += 1;
}
