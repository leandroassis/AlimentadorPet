#line 1 "D:/Projetos/Alimentador-Pet/source - PIC16F870/utils.c"
#line 1 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
#line 8 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
typedef unsigned char byte;
#line 20 "d:/projetos/alimentador-pet/source - pic16f870/defines.h"
void GetIncomingText();
void AddFeedInfo();

char ReadKeyboard();
void interrupt();
unsigned char VerifyTime(const short int hour[2], const short int minutes[2]);
#line 9 "D:/Projetos/Alimentador-Pet/source - PIC16F870/utils.c"
unsigned int column;

void GetIncomingText(){
 byte control;
 int column = 1, line = 1;

 if(UART1_Data_Ready()) control = UART1_Read();

 if(control == 0x02){
 Lcd_Cmd(_LCD_CLEAR);
 while(1){
 control = UART1_Read();
 if(control == 0x03) break;
 if(control == '\n'){
 line++;
 column = 1;
 continue;
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
 Lcd_Cmd(_LCD_CLEAR);
 }
 }
 }
}

char ReadKeyboard(){
 if(RB4_bit == 1){
 if(column == 0) return '1';
 else if(column == 1) return '2';
 else if(column == 2) return '3';
 else if(column == 3) return 'A';
 }
 else if(RB5_bit == 1){
 if(column == 0) return '4';
 else if(column == 1) return '5';
 else if(column == 2) return '6';
 else if(column == 3) return 'B';
 }
 else if(RB6_bit == 1){
 if(column == 0) return '7';
 else if(column == 1) return '8';
 else if(column == 2) return '9';
 else if(column == 3) return 'C';
 }
 else if(RB7_bit == 1){
 if(column == 0) return '*';
 else if(column == 1) return '0';
 else if(column == 2) return '#';
 else if(column == 3) return 'D';
 }
}

void interrupt(){
 if(INTF_bit){
 column++;
 INTF_bit = 0x00;
 }
 if(column > 3) column == 0;
 switch(column){
 case 0:
 RC0_bit = 0x01;
 RB1_bit = 0x00;
 RB2_bit = 0x00;
 RB3_bit = 0x00;
 break;
 case 1:
 RC0_bit = 0x00;
 RB1_bit = 0x01;
 RB2_bit = 0x00;
 RB3_bit = 0x00;
 break;
 case 2:
 RC0_bit = 0x00;
 RB1_bit = 0x00;
 RB2_bit = 0x01;
 RB3_bit = 0x00;
 break;
 case 3:
 RC0_bit = 0x00;
 RB1_bit = 0x00;
 RB2_bit = 0x00;
 RB3_bit = 0x01;
 break;
 }
}

void AddFeedInfo(){
 unsigned short int hour[2], minutes[2];
 unsigned char key;
 unsigned short int indice;

 Lcd_Out(1, (16-strlen("Add a new feed:"))/2, "Add a new feed:");
 Lcd_Out(2,6,"--:--");

 do {
 strcpy(key, ReadKeyboard());
 switch(key){
 case '#':
 if((indice == 3) || (indice == 0)) break;
 indice--;
 LCD_Out(2,6+indice, "-");
 break;
 case '*':
 break;
 case 'A':
 break;
 case 'B':
 break;
 case 'C':
 break;
 case 'D':
 break;
 default:

 if(indice == 2) break;
 else if(indice >= 3) minutes[indice-3] = key;
 else hour[indice] = key;
 LCD_Out(2, 6+indice, key);
 indice++;
 if(indice > 4) indice = 4;
 break;
 }
 } while(key != 'D');

 if(VerifyTime(hour, minutes)){

 }
}

unsigned char VerifyTime(const short int hour[2], const short int minutes[2]){

}
