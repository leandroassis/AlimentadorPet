/*
 * Project name:
     ESP-12F Routine
 * Revision History:
     - initial release
 * Description:
     This is a utilities header of Pet Feeder control using an ESP-12F.

 * Notes:
     I've used Arduino IDE to programming the esp12F single board using the NODEMCU pinout.
 */

#include "defines.h"

byte GetDriverData(){
  
}

void WriteEEPROM(int device_address, unsigned int memory_address, byte data) 
{
  Wire.beginTransmission(device_address);
  Wire.write((int)(memory_address >> 8));   // Byte mais significativo
  Wire.write((int)(memory_address & 0xFF)); // Byte menos significativo
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte ReadEEPROM(int device_address, unsigned int memory_address ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(device_address);
  Wire.write((int)(memory_address >> 8));   
  Wire.write((int)(memory_address & 0xFF)); 
  Wire.endTransmission();
 
  Wire.requestFrom(device_address,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}