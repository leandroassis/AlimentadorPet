#include <LiquidCrystal.h>
#include "RTClib.h"

#define sensor A3

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
void EncheCambuca();
void VarreTeclado();
void AbreBandeja();
void FechaBandeja();
void MoveEsquerda(); // função para interagir com as opções no lcd
void MoveDireita(); // função para interagir com as opções no lcd
void PressOK(); // função para identificar quando se o usuário clicou em ok (segura) ou em 0 (clica e solta)

// variaveis utilizadas para exemplificar
int dose_programada = 500; // quantidade de comida em gramas
int hora_alimentacao1 = 18;
int minutos_alimentacao1 = 14;
int hora_alimentacao2 = 18;
int minutos_alimentacao2 = 15;
int peso_da_cambuca;
int contador_ctrl = 0;

void setup() {
  lcd.begin(16, 2);
  rtc.begin();

  pinMode(CTRL_MOTORS, OUTPUT);
  pinMode(servo_ctrl, OUTPUT);
  
  pinMode(sensor, INPUT);
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

  lcd.setCursor(5,0);
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minutos);
  lcd.setCursor(1,1);
  lcd.print("<");
  lcd.setCursor(14,1);
  lcd.print(">");

  if(hora == hora_alimentacao1 || hora == hora_alimentacao2){
    if(minutos == minutos_alimentacao1 || minutos == minutos_alimentacao2) EncheCambuca();
  }
  contador_ctrl = 0; 
}

void EncheCambuca(){
  peso_da_cambuca = map(analogRead(sensor), 0, 255, 0, 1000);
  while(peso_da_cambuca< dose_programada){
    peso_da_cambuca = map(analogRead(sensor), 0, 255, 0, 1000);
    AbreBandeja();
    digitalWrite(CTRL_MOTORS, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Peso da cambuca:");
    lcd.setCursor(5,1);
    lcd.print(peso_da_cambuca);
  }
  delay(50);
  FechaBandeja();
  digitalWrite(CTRL_MOTORS, LOW);
  lcd.clear();
}

void AbreBandeja(){
  digitalWrite(servo_ctrl, HIGH);
  delay(2);
  digitalWrite(servo_ctrl, LOW);
  delay(18);
}

void FechaBandeja(){
  digitalWrite(servo_ctrl, HIGH);
  delay(1);
  digitalWrite(servo_ctrl, LOW);
  delay(19);
}

/*
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
*/
