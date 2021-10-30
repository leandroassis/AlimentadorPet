/*
  Made by: Leandro Assis
  Date: 29/10/2021
  Description: Utilities code file
*/

#include <stdlib.h>
#include <string.h>
#include "defines.h"

byte memory_dump[5];

void GetIncomingText(){
     byte control;
     int column = 1, line = 1;

     if(UART1_Data_Ready()) control = UART1_Read(); // Read the next byte
     
     if(control == STX){
                Lcd_Cmd(__LCD_CLEAR);               // Cleans the Lcd
                while(1){
                   control = UART1_Read();
                   if(control == ETX) break;
                   if(control == '\n'){
                              line++;
                              column = 1;
                   }
                   Lcd_Out(line, column, control);
                   column++;
                   if(column > 16){
                             line++;
                             column = 1;
                   }
                   if(line > 2){
                    line = 1;
                    Delay_ms(1000);
                    Lcd_Cmd(__LCD_CLEAR);
                   }
                }
     }
}

void AddFeedInfo(){
     byte hour[2], minutes[2];
     Lcd_Out(1, (16-strlen("Add a new feed:"))/2, "Add a new feed");

}