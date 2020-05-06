String mapGenerator(){
  repeatReduction();
  writeEeprom();
}
void writeEeprom (){
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  for(int j = 0; j<movements.length(); j++){
    EEPROM.update(j,movements.charAt(j));  
  }
}
void readEeprom (){
  for(int h = 0; h<EEPROM.length();h++){
      charEeprom = EEPROM.read(h);
      finalMovements += charEeprom;
  }
}

void repeatReduction(){
  for (int i = 0; i < movements.length(); i ++)
  {
    if(movements.charAt(i) == 'B'){
      reducing();
      i= 0;  
    }
  }
}
void reducing() {
  int a = -1;
  while (movements.charAt(a) != 'B') {
    a++;
  }
  switch (movements.charAt(a - 1)) {
    case 'R':
      switch (movements.charAt(a + 1)) {
        case 'R':
          movements.remove(a, 2);
          movements.setCharAt(a - 1, 'F');
          return;
        case 'L':
          movements.setCharAt(a - 1, 'B');
          movements.remove(a, 2);
          return;
        case 'F':
          movements.setCharAt(a - 1, 'L');
          movements.remove(a, 2);
          return;
      }
    case 'L':
      switch (movements.charAt(a + 1)) {
        case 'R':
          movements.setCharAt(a - 1, 'B');
          movements.remove(a, 2);
          return;
        case 'L':
          movements.setCharAt(a - 1, 'F');
          movements.remove(a, 2);
          return;
        case 'F':
          movements.setCharAt(a - 1, 'R');
          movements.remove(a, 2);
          return;
      }
    case 'F':
      switch (movements.charAt(a + 1)) {
        case 'R':
          movements.setCharAt(a - 1, 'L');
          movements.remove(a, 2);
          return;
        case 'L':
          movements.setCharAt(a - 1, 'R');
          movements.remove(a, 2);
          return;
      }
  }
  return;
}
void readMovements(String finalM){
  if(finalM.charAt(moveCounter)== 'L'){
    turnLeft90(velocity);  
  }  
  else if(finalM.charAt(moveCounter)== 'F'){
    moveCell(velocity);
  }
  else if(finalM.charAt(moveCounter)== 'R'){
    turnRight90(velocity);
  }
  else{
    estadoMain = FIRST_RUN;
  }
  moveCounter = moveCounter+1;
}
