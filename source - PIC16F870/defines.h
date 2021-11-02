/*
  Made by: Leandro Assis
  Date: 29/10/2021
  Description: Definitions header file
*/

// Type and variables definitions
typedef unsigned char byte;

// Pin assignment
#define RS       RA4_bit
#define EN       RA5_bit
#define DATA4    RA0_bit
#define DATA5    RA1_bit
#define DATA6    RA2_bit
#define DATA7    RA3_bit

// Functions

void GetIncomingText(); // Deal incoming text and show it in LCD
void AddFeedInfo();     // Add new feed info
//void UpdateInfos();     // Get next feeds and currently time
char ReadKeyboard();
void interrupt();
unsigned char VerifyTime(const short int hour[2], const short int minutes[2]);