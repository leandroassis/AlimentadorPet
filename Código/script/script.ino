#include <Wire.h>
#include "RTClib.h"

#define CONFIG_RTC 2
#define LED 3
int controle = 0;
RTC_DS1307 rtc;

void AjustaRelogio();

void setup() {
  pinMode(CONFIG_RTC, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  DateTime now = rtc.now();

  int hora = now.hour();
  int minutos = now.minute();
  int segundos = now.second();
  
  AjustaRelogio();
  if(hora==17 && minutos==43 && segundos==10){
    for(int i=0; i<3; i++){
      digitalWrite(LED, HIGH);
      delay(2000);
      digitalWrite(LED, LOW);
      delay(2000);
    }
  }   
  delay(500);
}

void AjustaRelogio(){
  //implementar função que pega os dados de horarios de um servidor a cada 24 horas
  boolean estado = digitalRead(CONFIG_RTC);
  if(estado && controle == 0){
    rtc.adjust(DateTime(2021,03,12,0,11,0));
    controle = 1;
  }
  estado = false;
}
