void inicializar() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(DIR_L1, OUTPUT);
  pinMode(DIR_L2, OUTPUT);
  pinMode(DIR_R1, OUTPUT);
  pinMode(DIR_R2, OUTPUT);
  pinMode(PWML, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(ENC_L, INPUT);
  pinMode(ENC_R, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_L), updateLeftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_R), updateRightEncoder, RISING);
  estadoCases = START;
  estadoMain = WAIT;
  button1State = WAIT;
  button2State = WAIT;
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timer);
  Serial.begin(9600);
}

void updateLeftEncoder() {
  encoderTicks[LEFT] += 1;
}
void updateRightEncoder() {
  encoderTicks[RIGHT] += 1;
}

float getEncoderDistance(int dir) {
  return (float)WHEEL_PER * encoderTicks[dir] / TICKS_REV ;
}
float getEncoderRevolutions(int dir) {
  return (float)encoderTicks[dir] / TICKS_REV ;
}

void delay_ms(int ms) {
  long tiempo = millis();
  while (tiempo + ms > millis()) {}
}

//LED1 o LED2
void setLED(int led, int state) {
  digitalWrite(led, state);
}

//BTN1 o BTN2
int getBTN(int btn) {
  return !digitalRead(btn);
}

void setMotorL(int spd) {
  digitalWrite(DIR_L1, spd > 0);
  digitalWrite(DIR_L2, spd < 0);
  analogWrite(PWML, abs(spd));
}

void setMotorR(int spd) {
  digitalWrite(DIR_R1, spd > 0);
  digitalWrite(DIR_R2, spd < 0);
  analogWrite(PWMR, abs(spd));
}

//Entre -1000 y 1000
void setMotors(int v1, int v2) {
  v1 = constrain(v1, -1000, 1000);
  v2 = constrain(v2, -1000, 1000);
  v1 = map(v1, -1000, 1000, -255, 255);
  v2 = map(v2, -1000, 1000, -255, 255);
  setMotorL(v1);
  setMotorR(v2);
}

//Entre -1000 y 1000

void turnLeft(int velocity) {
  setMotors(-velocity, velocity);
}

void turnRight(int velocity) {
  setMotors(velocity, -velocity);
}
float readSharp (int pin) /*Lectura buenas entre 3cm a 25cm*/
{
  float aux = analogRead(pin);

  aux /= 1024; // convierto a volt
  aux *= 5;

  if (aux <= 0.35)
    aux = 0.35;

  aux = pow(aux - 0.3, 0.25);/*convertimos a cm con un aproximacion grafica*/
  aux = 27.5 / aux;           /*no preguntar por los valores*/
  aux -= 18;

  return aux;
}

void turnLeft90(int velocity) {
  float initialDistance = getEncoderDistance(LEFT);
  while (getEncoderDistance(LEFT) - initialDistance < LEFT_TURN90) {
    setMotors(-velocity, velocity);
  }
  setMotors(0, 0);
}
void turnRight90(int velocity) {
  float initialDistance = getEncoderDistance(LEFT);
  while (getEncoderDistance(LEFT) - initialDistance < RIGHT_TURN90) {
    setMotors(velocity, -velocity);
  }
  setMotors(0, 0);
}
void turn180(int velocity) {
  float initialDistance = getEncoderDistance(LEFT);
  while (getEncoderDistance(LEFT) - initialDistance < TURN_180) {
    setMotors(velocity, -velocity);
  }
  setMotors(0, 0);
}
void moveCell(int velocity) {
  float initialDistance = getEncoderDistance(LEFT);
  while (getEncoderDistance(LEFT) - initialDistance < CELL) {
    moveStraight();
  }
  setMotors(0, 0);
}
void readMovements(){
  
}


void resetTicks(void){
  encoderTicks[LEFT] = 0;
  encoderTicks[RIGHT] = 0;
}
