#include <LiquidCrystal.h>
#include "RTClib.h"

// Pinout dos Motores
#define CTRL_MOTORS 0
#define servo_ctrl  1

// Pinout do teclado matricial
#define line1 13
#define line2 12
#define line3 11
#define line4 10
#define column1 9
#define column2 8
#define column3 A2

// Pinout do LCD
#define d4 2
#define d5 3
#define d6 4
#define d7 5
#define rs 6
#define e  7

// Inicialização das classes RTC e LCD
RTC_DS1307 rtc;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

// Protótipo das funções
char VarreTeclado();
void MoveEsquerda();
void MoveDireita();
void PressOK();


void setup() {
  lcd.begin(16, 2);
  rtc.begin();

  pinMode(CTRL_MOTORS, OUTPUT);
  pinMode(servo_ctrl, OUTPUT);
  pinMode(column1, OUTPUT);
  pinMode(column2, OUTPUT);
  pinMode(column3, OUTPUT);

  pinMode(line1, INPUT);
  pinMode(line2, INPUT);
  pinMode(line3, INPUT);
  pinMode(line4, INPUT);
}

void loop() {
  DateTime now = rtc.now();
  int hora = now.hour();
  int minutos = now.minute();
  int segundos = now.second();
 
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minutos);
  lcd.print(":");
  lcd.print(segundos);

  lcd.setCursor(1,1);
  lcd.print("<");
  lcd.setCursor(14,1);
  lcd.print(">");

  char tecla = VarreTeclado();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(tecla);
}

char VarreTeclado(){
  for(int i = 0; i<3; i++){
    int column = i;
  }

  switch(column){
    case 0:
      digitalWrite(column1, HIGH);
      delay(150);
      linha1 = digitalRead(line1);
      delay(150);
      linha2 = digitalRead(line2);
      delay(150);
      linha3 = digitalRead(line3);
      delay(150);
      linha4 = digitalRead(line4);
      delay(150);
    
      if(linha1) return "1";
      if(linha2) return "4";
      if(linha3) return "7";
      if(linha4) MoveEsquerda();
      digitalWrite(column1, LOW);
      
    case 1:
      digitalWrite(column2, HIGH);
      delay(150);
      linha1 = digitalRead(line1);
      delay(150);
      linha2 = digitalRead(line2);
      delay(150);
      linha3 = digitalRead(line3);
      delay(150);
      linha4 = digitalRead(line4);
      delay(150);
    
      if(linha1) return "2";
      if(linha2) return "5";
      if(linha3) return "8";
      if(linha4) PressOK();
      digitalWrite(column2, LOW);
      
    case 2:
      digitalWrite(column3, HIGH);
      delay(150);
      linha1 = digitalRead(line1);
      delay(150);
      linha2 = digitalRead(line2);
      delay(150);
      linha3 = digitalRead(line3);
      delay(150);
      linha4 = digitalRead(line4);
      delay(150);
    
      if(linha1) return "3";
      if(linha2) return "6";
      if(linha3) return "9";
      if(linha4) MoveDireita();
      digitalWrite(column3, LOW);
  }
}
