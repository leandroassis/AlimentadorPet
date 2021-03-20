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
void VarreTeclado();
void MoveEsquerda();
void MoveDireita();
void PressOK();
void MovimentaMotores();
void AbreBandeja();
void FechaBandeja();

void setup() {
  lcd.begin(16, 2);
  rtc.begin();

  pinMode(CTRL_MOTORS, OUTPUT);
  pinMode(servo_ctrl, OUTPUT);
  
  pinMode(column1, INPUT);
  pinMode(column2, INPUT);
  pinMode(column3, INPUT);
  pinMode(line1, INPUT);
  pinMode(line2, INPUT);
  pinMode(line3, INPUT);
  pinMode(line4, INPUT);
}

void loop() {
  DateTime now = rtc.now();
  int hora = now.hour();
  int minutos = now.minute();
  
  lcd.setCursor(0,0);
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minutos);
  lcd.setCursor(1,1);
  lcd.print("<");
  lcd.setCursor(14,1);
  lcd.print(">");
  
  //VarreTeclado();
  MovimentaMotores();
}

void VarreTeclado(){
  bool linha1, linha2, linha3, linha4, coluna1, coluna2, coluna3;

  coluna1 = digitalRead(column1);
  linha1 = digitalRead(line1);
  delay(50);
  linha2 = digitalRead(line2);
  delay(50);
  linha3 = digitalRead(line3);
  delay(50);
  linha4 = digitalRead(line4);
  delay(50);
  
  coluna2 = digitalRead(column2);
  linha1 = digitalRead(line1);
  delay(50);
  linha2 = digitalRead(line2);
  delay(50);
  linha3 = digitalRead(line3);
  delay(50);
  linha4 = digitalRead(line4);
  delay(50);
  
  coluna3 = digitalRead(column3);
  linha1 = digitalRead(line1);
  delay(50);
  linha2 = digitalRead(line2);
  delay(50);
  linha3 = digitalRead(line3);
  delay(50);
  linha4 = digitalRead(line4);
  delay(50);
}

void AbreBandeja(){
  digitalWrite(servo_ctrl, HIGH);
  delay(2);
  digitalWrite(servo_ctrl, LOW);
  delay(18);
}

void FechaBandeja(){
  digitalWrite(servo_ctrl, HIGH);
  delay(1.5);
  digitalWrite(servo_ctrl, LOW);
  delay(18.5);
}

void MovimentaMotores(){
  digitalWrite(CTRL_MOTORS, HIGH);
  AbreBandeja();
  delay(4000);
  digitalWrite(CTRL_MOTORS, LOW);
  FechaBandeja();
  delay(2000);
  digitalWrite(servo_ctrl, LOW);
}
