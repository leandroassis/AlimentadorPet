/*
 * Project name:
     ESP-12F Routine
 * Revision History:
     - initial release
 * Description:
     This is a define header file of Pet Feeder control using an ESP-12F.

 * Notes:
     I've used Arduino IDE to programming the esp12F single board using the NODEMCU pinout.
*/

// Variable types definition
typedef register fast;
typedef unsigned char byte;

// Labels and Control bytes Definements

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

// Hardware Pinout Definements

#define BALANCE       A0
#define AXIS_MOTORS   D0
#define SERVO_MOTORS  D7
#define SCL           D1
#define SDA           D2

// Peripherical Memory Organization

#define EEPROM_ADDRESS              0x50 // EEPROM I2C Bus Address
#define BOOT_CHECK_MEMORY_ADDRESS   0x00 // Check boot byte address
#define START_BANK_ADDRESS          0x01 // Begin of feed configurations variables bank
#define END_BANK_ADDRESS            0x7F // End of feed configurations variables bank 

// Code Utils 
#define MAX_WEIGHT    1000
#define MIN_WEIGHT    0
unsigned char hour;
unsigned char minutes;
byte incoming_data;

// Functions Declaration
void AddFeedConfigs(); // Add some feed parameters
void RemoveFeedConfigs();

void OrganizeEEPROM();
void QuickSort(byte left_limit, byte right_limit, byte bias);

unsigned short int FoodTime(unsigned char hour, unsigned char minutes);
byte BinarySearch(unsigned char item);

void LCDPrint(char *message);
void WriteEEPROM(unsigned int memory_address, byte data); // Write a data into eeprom
byte ReadEEPROM(unsigned int memory_address); // Read a data into eeprom
void SpinAxis(unsigned short int desired_amount);
void EraseMemory();
void GetMemoryData(unsgined char hour, unsigned char minutes);

