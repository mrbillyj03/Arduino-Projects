//  1-digit BCD Counter - by Bill Jenkins 07-17-2018
//  This sketch simulates a one digit BCD counter
//  with the clock time set by parameter

// define variables for BCD output, d = high order bit, a = low order bit
int BCDd = 11;    // high order bit
int BCDc = 10;
int BCDb = 9;
int BCDa = 8;     // low order bit
int CYCLE = 1000; // delay time in milliseconds
int i = 0;        // test for start

void setup() {    // initialize output pins
  pinMode(BCDd, OUTPUT);
  pinMode(BCDc, OUTPUT);
  pinMode(BCDb, OUTPUT);
  pinMode(BCDa, OUTPUT);
  
}

void loop() {
  
  //light all four LEDs to indicate sequence start
  if (i==0){
  digitalWrite(BCDd, HIGH);
  digitalWrite(BCDc, HIGH);
  digitalWrite(BCDb, HIGH);
  digitalWrite(BCDa, HIGH);
  delay(CYCLE);
  i++;
  }
  
  // write a BCD '0'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, LOW);
  digitalWrite(BCDb, LOW);
  digitalWrite(BCDa, LOW);
  delay(CYCLE);

  // write a BCD '1'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, LOW);
  digitalWrite(BCDb, LOW);
  digitalWrite(BCDa, HIGH);
  delay(CYCLE);

  // write a BCD '2'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, LOW);
  digitalWrite(BCDb, HIGH);
  digitalWrite(BCDa, LOW);
  delay(CYCLE);

  // write a BCD '3'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, LOW);
  digitalWrite(BCDb, HIGH);
  digitalWrite(BCDa, HIGH);
  delay(CYCLE);

  // write a BCD '4'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, HIGH);
  digitalWrite(BCDb, LOW);
  digitalWrite(BCDa, LOW);
  delay(CYCLE);

  // write a BCD '5'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, HIGH);
  digitalWrite(BCDb, LOW);
  digitalWrite(BCDa, HIGH);
  delay(CYCLE);

  // write a BCD '6'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, HIGH);
  digitalWrite(BCDb, HIGH);
  digitalWrite(BCDa, LOW);
  delay(CYCLE);

  // write a BCD '7'
  digitalWrite(BCDd, LOW);
  digitalWrite(BCDc, HIGH);
  digitalWrite(BCDb, HIGH);
  digitalWrite(BCDa, HIGH);
  delay(CYCLE);

  // write a BCD '8'
  digitalWrite(BCDd, HIGH);
  digitalWrite(BCDc, LOW);
  digitalWrite(BCDb, LOW);
  digitalWrite(BCDa, LOW);
  delay(CYCLE);

  // write a BCD '9'
  digitalWrite(BCDd, HIGH);
  digitalWrite(BCDc, LOW);
  digitalWrite(BCDb, LOW);
  digitalWrite(BCDa, HIGH);
  delay(CYCLE);
  
}

