/*
  Made by: Leandro Assis
  Date: 29/10/2021
  Description: Definitions header file
*/

// Type definitions

typedef unsigned char byte;

// Labels and Control Bytes

#define NULL          0xFF // NUll byte
#define STX           0x02 // Start of text byte
#define ETX           0x03 // End of text byte
#define DONE          0X04 // Done byte
#define CAN           0x18 // Cancel byte
#define STB           0x01 // Start transmission byte
#define ETB           0x17 // End transmission byte
#define ERR           0x07 // Error byte
#define INB           0x1E // Start of data in memory
#define ENB           0x1F // End of data in memory

#define ADD           0x1A
#define REM           0x11
#define CLR           0x12
#define GET           0x13

// Pin assignment

#define CLMN1    RC0_bit
#define CLMN2    RB1_bit
#define CLMN3    RB2_bit
#define CLMN4    RB3_bit
#define LINE1    RB4_bit
#define LINE2    RB5_bit
#define LINE3    RB6_bit
#define LINE4    RB7_bit

#define CLK_IN   RB0_bit
#define TX       RC6_bit
#define RX       RC7_bit

#define RS       RA4_bit
#define RW       RC1_bit
#define EN       RA5_bit
#define DATA0    RC2_bit
#define DATA1    RC3_bit
#define DATA2    RC4_bit
#define DATA3    RC5_bit
#define DATA4    RA0_bit
#define DATA5    RA1_bit
#define DATA6    RA2_bit
#define DATA7    RA3_bit

// Functions

void GetIncomingText(); // Deal incoming text and show it in LCD
void AddFeedInfo();     // Add new feed info
void UpdateInfos();     // Get next feeds and currently time