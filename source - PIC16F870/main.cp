#line 1 "D:/Projetos/Alimentador-Pet/source - PIC16F870/main.c"
#line 1 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
#line 8 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
typedef unsigned char byte;
#line 20 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
void GetIncomingText();
void AddFeedInfo();

char ReadKeyboard();
void interrupt();
unsigned char VerifyTime(const short int hour[2], const short int minutes[2]);
#line 9 "D:/Projetos/Alimentador-Pet/source - PIC16F870/main.c"
sbit LCD_RS at  RA4_bit ;
sbit LCD_EN at  RA5_bit ;

sbit LCD_D4 at  RA0_bit ;
sbit LCD_D5 at  RA1_bit ;
sbit LCD_D6 at  RA2_bit ;
sbit LCD_D7 at  RA3_bit ;

sbit LCD_RS_Direction at TRISA4_bit;
sbit LCD_EN_Direction at TRISA5_bit;
sbit LCD_D4_Direction at TRISA0_bit;
sbit LCD_D5_Direction at TRISA1_bit;
sbit LCD_D6_Direction at TRISA2_bit;
sbit LCD_D7_Direction at TRISA3_bit;

byte incoming_data;

void main() {

 GIE_bit = 0x01;
 PEIE_bit = 0x00;
 INTE_bit = 0x01;
 INTEDG_bit = 0x01;

 TRISB = 0xFF;
 TRISC = 0x81;

 PORTA = 0x00;
 PORTC = 0x00;

 ADCON1 = 0x06;

 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 UART1_Init(9600);
 Delay_ms(100);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, (16-strlen("Powering up..."))/2, "Powering up...");
 do{
 if(UART1_Data_Ready()) incoming_data = UART1_Read();
 if(incoming_data == 0x07){
 GetIncomingText();
 while(1){}
 }
 else if(incoming_data == 0x1A){
 AddFeedInfo();
 }
 } while(incoming_data != 0x17);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, (16-strlen("Auto Pet Feeder"))/2, "Auto PetFeeder");
}
