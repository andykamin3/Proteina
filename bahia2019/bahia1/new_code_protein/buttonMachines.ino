void buttonThreeMachine(void) {
  button3Status = digitalRead(BTN3);
  switch (button3State) {
    case WAIT:
      if (button3Status == PRESS) {
        button3Millis = 0;
        button3State = CONFIRMATION;
      }
      break;
    case CONFIRMATION:
      if (button3Status == PRESS && button3Millis > 10) {
        button3State = LIBERATION;
      }
      break;
    case LIBERATION:
      if (button3Status == RELEASE) {
        button3State = WAIT;
        button3Flag = 1;
      }
      break;
  }
}

void buttonTwoMachine(void) {
  button2Status = digitalRead(BTN2);
  switch (button2State) {
    case WAIT:
      if (button2Status == PRESS) {
        button2Millis = 0;
        button2State = CONFIRMATION;
      }
      break;
    case CONFIRMATION:
      if (button2Status == PRESS && button2Millis > 10) {
        button2State = LIBERATION;
      }
      break;
    case LIBERATION:
      if (button2Status == RELEASE) {
        button2State = WAIT;
        button2Flag = 1;
      }
      break;
  }
}
void buttonOneMachine(void) {
  button1Status = digitalRead(BTN1);

  switch (button1State) {
    case WAIT:
      if (button1Status == PRESS) {
        button1Millis = 0;
        button1State = CONFIRMATION;
      }
      break;
    case CONFIRMATION:
      if (button1Status == PRESS && button1Millis > 10) {
        button1State = LIBERATION;
      }
      break;
    case LIBERATION:
      if (button1Status == RELEASE) {
        button1State = WAIT;
        button1Flag = 1;
      }
      break;
  }
}
