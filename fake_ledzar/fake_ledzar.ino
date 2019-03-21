#include <SPI.h>
#include <MFRC522.h>

int dataPin = 11;   //connected to DS
int clockPin = 12;  //connected to SH_CP
int latchPin = 8;   //connected to ST_CP
int buton_pin = 2;   

int SS_PIN = 10;  //sda pin
int RST_PIN = 9;  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);

int button;
byte  data[6]={B100000,B1100000,B1110000,B1111000,B1111100,B1111110};       //zarın 6 durumu var 1-6


bool check_button()
{
  button = digitalRead(buton_pin);
  if (button == 1) {
    go();
  }
}

void setup(){
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buton_pin , INPUT);
}

void loop(){
  hile();
  delay(100);
}

void go(void){
  int say = random(0,6);
  byte sans = data[say];
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, sans);
  digitalWrite(latchPin, 1);  
}

void hile() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()){return;}    // Look for new cards
  if ( ! mfrc522.PICC_ReadCardSerial()){return;}      // Select one of the cards
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();                          // iki kart istersen ) ve slash lari sil. alttaki akbil.
  if (content.substring(1) == "EA EB 2F 2E" )     //|| content.substring(1) == "AE 83 1D D9") 
  {
    while (true){
      button = digitalRead(buton_pin);
      if (button == 1) {
        int kesin_sans = data[5];
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, LSBFIRST, kesin_sans);
        digitalWrite(latchPin, 1);
        break;
      } 
      delay(100);
    } 
  } 
  else{
    check_button();
  }
}
