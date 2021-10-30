/*
  Made by: Leandro Assis
  Date: 29/10/2021
  Description: Main source file of PIC16F870 routine
*/

#include <string.h>
#include "defines.h"

sbit LCD_RS at RS;
sbit LCD_EN at EN;

sbit LCD_D4 at DATA4;
sbit LCD_D5 at DATA5;
sbit LCD_D6 at DATA6;
sbit LCD_D7 at DATA7;

sbit LCD_RS_Direction at TRISA4_bit;
sbit LCD_EN_Direction at TRISA5_bit;
sbit LCD_D4_Direction at TRISA0_bit;
sbit LCD_D5_Direction at TRISA1_bit;
sbit LCD_D6_Direction at TRISA2_bit;
sbit LCD_D7_Direction at TRISA3_bit;

byte incoming_data;

void main() {
     // Set some register
     TRISA = 0x00;                                      // Set port A as output
     TRISB = 0xFF;                                      // Set port B as input
     TRISC = 0x81;

     ADCON1 = 0x06;                                     // Set the analog pins as digital
     
     Lcd_Init();                                        // Initialize LCD
     Lcd_Cmd(_LCD_CURSOR_OFF);                          // Turn cursor off
     UART1_Init(9600);                                  // Initialize Uart module
     Delay_ms(100);                                     // Await Uart to stabilize

     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Out(1, (16-strlen("Powering up..."))/2, "Powering up...");
     do{
        if(UART1_Data_Ready()) incoming_data = UART1_Read(); // Read the incoming data
        if(incoming_data == ERR){
             GetIncomingText();
             while(1){}
        }
        else if(incoming_data == ADD){
             AddFeedInfo();
        }
     } while(incoming_data != ETB);
     UpdateInfos();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Out(1, (16-strlen("Auto Pet Feeder"))/2, "Auto PetFeeder"); // Write centralized message
}