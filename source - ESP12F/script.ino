/*
 * Project name:
     ESP-12F Routine
 * Revision History:
     - initial release
 * Description:
     This is a main code file of Pet Feeder control using an ESP-12F.
 * Made by:
      Leandro Assis dos Santos

 * Note:
      In this version there isn't server comunication and app integration.
      These features can be developed someday. 
*/

#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include "defines.h"
#include "utils.h"

// RTC class inicialization
RTC_DS1307 rtc;

void setup() {
  Wire.begin();

  if(!rtc.begin()){
    LCDPrint("Couldn't find RTC module.")
    LCDPrint("Take your device into maintenance.")
    abort()
  }

  pinMode(BALANCE, INPUT);
  pinMode(AXIS_MOTORS, OUTPUT);
  pinMode(SERVO_MOTORS, OUTPUT);
  pinMode(RX_LCD, INPUT);
  pinMode(CLK_LCD, INPUT);
  pinMode(TX_LCD, OUTPUT);

  if(!rtc.isrunning()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  if(!GetDriverData(0x0)){
    LCDPrint("First boot. Please insert the desired feed configurations.");
    delay(3000);
    AdjustFeedConfigs(food);
  }
}

void loop() {
  DateTime now = rtc.now();
  int hour = now.hour();
  int minutes = now.minute();
  int seconds = now.seconds();

  

  if(hora == hora_alimentacao1 || hora == hora_alimentacao2){
    if(minutos == minutos_alimentacao1 || minutos == minutos_alimentacao2) EncheCambuca();
  }
}