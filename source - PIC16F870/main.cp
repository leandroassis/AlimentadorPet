#line 1 "D:/Projetos/Alimentador-Pet/source - PIC16F870/main.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/string.h"





void * memchr(void *p, char n, unsigned int v);
int memcmp(void *s1, void *s2, int n);
void * memcpy(void * d1, void * s1, int n);
void * memmove(void * to, void * from, int n);
void * memset(void * p1, char character, int n);
char * strcat(char * to, char * from);
char * strchr(char * ptr, char chr);
int strcmp(char * s1, char * s2);
char * strcpy(char * to, char * from);
int strlen(char * s);
char * strncat(char * to, char * from, int size);
char * strncpy(char * to, char * from, int size);
int strspn(char * str1, char * str2);
char strcspn(char * s1, char * s2);
int strncmp(char * s1, char * s2, char len);
char * strpbrk(char * s1, char * s2);
char * strrchr(char *ptr, char chr);
char * strstr(char * s1, char * s2);
char * strtok(char * s1, char * s2);
#line 1 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
#line 9 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
typedef unsigned char byte;
#line 58 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
void GetIncomingText();
void AddFeedInfo();
void UpdateInfos();
#line 10 "D:/Projetos/Alimentador-Pet/source - PIC16F870/main.c"
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

 TRISA = 0x00;
 TRISB = 0xFF;
 TRISC = 0x81;

 ADCON1 = 0x06;

 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 UART1_Init(9600);
 Delay_ms(100);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, (16-strlen("Powering up..."))/2, "Powering up...");
 do{
 if(UART1_Data_Ready()) incoming_data = UART1_Read();
 if(incoming_data ==  0x07 ){
 GetIncomingText();
 while(1){}
 }
 else if(incoming_data ==  0x1A ){
 AddFeedInfo();
 }
 } while(incoming_data !=  0x17 );
 UpdateInfos();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, (16-strlen("Auto Pet Feeder"))/2, "Auto PetFeeder");
}
