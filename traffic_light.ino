// Traffic light with warning buzzer for yellow light
// by Bill Jenkins
// this sketch simulates a traffic light's operation 
// cycle is green -> yellow -> red
// it features a warning buzzer which sounds while yellow is lit


// Pin assignments for lights and buzzer

int RED = 10;             // red light
int YELLOW = 9;           // yellow light
int GREEN = 8;            // green light
int BUZZER = 11;          // buzzer

//  Variables for warning buzzer

int PITCH = 193;          // tone (G3) for yellow light warning 
int CYCLE = 400;          // pitch time in milliseconds
int i;                    // loop counter - how many times to repeat the warning sound

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins for red, yellow, green and buzzer as an output.


  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

// the loop function runs over and over again forever

void loop() {
 
  // green light = 8 sec.
  digitalWrite(RED, LOW);   
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  delay(8000);                       
  
  // yellow light = 4 sec., sound warning buzzer 
  digitalWrite(RED, LOW);   
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, LOW);
  for (i=0; i<4; i++) {
    tone(BUZZER, PITCH);
    delay(CYCLE); 
    tone(BUZZER, PITCH*2);
    delay(CYCLE);
  }
  tone(BUZZER, PITCH*4);
  delay(CYCLE);
  noTone(BUZZER);
  delay(CYCLE);
  
  // red light = 8 sec.
  digitalWrite(RED, HIGH);   
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  delay(8000);                       
 
}

