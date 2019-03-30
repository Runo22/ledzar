int dataPin = 4;   //connected to DS
int clockPin = 6;  //connected to SH_CP
int latchPin = 5;   //connected to ST_CP
int buton_pin = 2;   


byte  data[6]={B100000,B1100000,B1110000,B1111000,B1111100,B1111110};
//zarın 6 durumu var 1-6

bool check_button()
{
  int button = digitalRead(buton_pin);
  if (button == 1) {
    int elma = 0;
    while (elma<10){
      go();
      delay(300);
      elma++; 
    }
  }
}

void setup(){
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buton_pin , INPUT);
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
