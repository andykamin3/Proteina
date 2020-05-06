void moveStraight () {
  error = readSharp(SHARPL) - SETPOINT;

  timePrev = timeNow;
  timeNow = millis();
  elapsedTime = (timeNow - timePrev) / 1000;
  pidD = KD * ((error - previousError) / elapsedTime);
  pidP = KP * error;
  pid = pidP + pidD;
  if (pid > velocity) {
    pid = velocity;
  }
  if (pid < -velocity) {
    pid = -velocity;
  }

  motLeft = velocity - pid;
  motRight = velocity + pid;
  if (motLeft < 0) {
    motLeft = 0;
  }
  if (motRight < 0) {
    motRight = 0;
  }

  setMotors(motLeft, motRight);
  previousError = error;

}
