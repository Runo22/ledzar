int dataPin = 11;   //connected to DS
int clockPin = 12;  //connected to SH_CP
int latchPin = 8;   //connected to ST_CP
int buton_pin = 2   


byte  data[7]={B100000,B1100000,B1110000,B1111000,B1111100,B1111110};
//zarın 6 durumu var 1-6

bool check_button(int pin)
{
  int button = digitalRead(pin);
  if (button == 1) {
    go();
  }
}

void setup(){
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(button_pin , INPUT);
}

void loop(){
  check_button();
  delay(100);
}

void go(void){
  int say = random(0,6);
  byte sans = data[say];
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, sans);
  digitalWrite(latchPin, 1);  
}

