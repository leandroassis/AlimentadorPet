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
typedef struct
{
    unsigned short int hours = 0;
    unsigned short int minutes = 0;
    unsigned short int seconds = 0;
    unsigned int amount = 500;
} FeedConfigs;


// Hardware Pinout Definements

#define BALANCE       A0
#define AXIS_MOTORS   D0
#define SERVO_MOTORS  D8
#define SCL           D1
#define SDA           D2
#define RX_LCD        D5
#define CLK_LCD       D6
#define TX_LCD        D7

// LCD and Keyboard Driver Comunication

#define BITRATE       1000 // Comunication frequency in bits/s

// Peripherical Device Address

#define EEPROM_ADDRESS 0x50

// Variables 

int bowl_weight;
byte driverBytes[];
FeedConfigs *food;

// Functions Declaration
unsigned short int LCDPrint(char *message); // Send some string to the LCD Driver
byte GetDriverData();
void AdjustFeedConfigs(FeedConfigs *array); // Edit some feed parameters
void WriteEEPROM(unsigned int memory_address, byte data); // Write a data into eeprom
byte ReadEEPROM(unsigned int memory_address); // Read a data into eeprom
