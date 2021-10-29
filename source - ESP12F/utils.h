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

void GetMemoryData(unsigned char hour, unsigned char minutes){
  Serial.print(STB);
  Serial.print(hour); // Send actual time
  Serial.print(minutes);
  for(fast i = START_BANK_ADDRESS; i < END_BANK_ADDRESS; i+6){
    if(i == NULL) break;
    for(fast j = 1; j <= 5; j++){
      Serial.print(ReadEEPROM(i+j));
    }
  }
  Serial.print(ETB);
}

void RemoveFeedConfigs(){
  byte response, address = 0, aux = 1;

  do{
    response = Serial.read();

    if((response == CAN) || (response == ERR)) break;
    if(response != STB){ // Means it is receiving data byte
      if(address == 0){
        address = BinarySearch(response);
        if(address == NULL) break;
        continue;
      }
      if(ReadEEPROM(address+aux) != response) break;
      else aux++;
    }
  }while(response != ETB);

  if(aux == 4){
    for(fast i = address-1; i <= address+4; i++) WriteEEPROM(i, NULL);
    Serial.print(DONE);
  }
  else{
    Serial.print(ERR);
  }
}

void EraseMemory(){
  for(fast i = START_BANK_ADDRESS; i < END_BANK_ADDRESS; i++) WriteEEPROM(i, 0xFF);
  Serial.print(DONE);
}

unsigned short int FoodTime(unsigned char hour, unsigned char minutes){
  unsigned short int amount;
  byte address;

  address = BinarySearch(hour);
  if(address == NULL) return 0;
  else if(ReadEEPROM(address+1) == minutes){
    amount = (0xFF00 & ReadEEPROM(address+2)) || (0x00FF & ReadEEPROM(address+3));
  }
  else return 0;

  return amount;
}

byte BinarySearch(unsigned char item){
  byte address, init, end;

  init = 0x02;
  end = 0x7A;

  while(init <= end){
    address = (init+end)/2;
    address += address-2%6;

    if(ReadEEPROM(address) == item) return address;
    if(ReadEEPROM(address) < item){
      init = address;
    }
    else{
      end = address;
    }
  }

  return NULL;
}

void LCDPrint(char *message){
  Serial.print(STX); // envia byte de inicio de transmissão de mensagem

  for(fast i = 0; i < strlen(message); i++) Serial.print(message[i]);

  Serial.print(ETX); // envia byte de fim de transmissão de mensagem

}

void AddFeedConfigs(){
  byte response;
  byte empty_address = 0x00;

  if(ReadEEPROM(0x00) == NULL) WriteEEPROM(0x00, 0x01);

  for(fast i = START_BANK_ADDRESS; i < END_BANK_ADDRESS; i+6){
    // Read the EEPROM to find the first empty address
    if(ReadEEPROM(i) == NULL){ // When find it, write the start data byte and save the next address in empty_adress variable
      empty_address = i;
      WriteEEPROM(empty_address, INB);
      empty_address++;
      break;
    }
  }
  if(!empty_address){ // If the bank is full send a cancel bit
    Serial.print(CAN);
    response = CAN;
  }
  else{
    Serial.print(DONE);
  }

  do{
    response = Serial.read(); // Read the incoming byte

    if((response == CAN) || (response == ERR)){ // If byte means error or cancel
      if(empty_address){
        // If a cancel or error byte came after already write some data byte in memory, it goes cleaning until find an INB byte
        for(fast i = empty_address; i > START_BANK_ADDRESS; i--){
          if(ReadEEPROM(i) == INB){
            WriteEEPROM(i, NULL);
            break;
          }
          WriteEEPROM(i, NULL);
        }
      }
      else break;
    }
    else{ // Means it received an STB or input data byte
      if(response != STB){ // If it really received an input data byte
        if(response == ETB) WriteEEPROM(empty_address, ENB); // If received an ETB byte write the end data byte before close the loop
        else{ // If received an normal input data byte write it 
          WriteEEPROM(empty_address, response);
          empty_address++;
        }
      }
    }
    if(empty_address > END_BANK_ADDRESS){
      Serial.print(ERR);
      break;
    }
  } while(response != ETB);  

  OrganizeEEPROM();
}

void QuickSort(byte left_limit, byte right_limit, byte bias){
  // Quick sort algorithm function
  byte median, value, aux;
  fast i;
  
  median = (START_BANK_ADDRESS+right_limit)/2;
  value = ReadEEPROM(median+bias);

  for(i = left_limit; i < right_limit;){
    for(fast j = ReadEEPROM(i+bias);  j < value;){
      if(i < right_limit) i+6;
    }
    for(fast j = ReadEEPROM(left_limit+bias); j > value;){
      if(left_limit > left_limit) right_limit-6;
    }
    if(i <= right_limit){
      for(fast w = bias; w <= 4+bias; w++){
        aux = ReadEEPROM(i+w);
        WriteEEPROM(i+w, ReadEEPROM(right_limit+w));
        WriteEEPROM(right_limit+w, aux);
      }
      i+6;
      right_limit-6;
    }
  }

  if(right_limit > left_limit) QuickSort(left_limit, right_limit, bias);
  if(i < right_limit) QuickSort(i, right_limit);

}

void OrganizeEEPROM(){ // Sort data into EEPROM for time using quick sort
  byte last_address;

  for(fast i = START_BANK_ADDRESS; i < END_BANK_ADDRESS; i+6) if(ReadEEPROM(i) == NULL) last_address = i-6;


  for(fast a = 0; a < 2; a++){

    if(fast == 0){
      QuickSort(START_BANK_ADDRESS, last_address, 1);
    }
    else{
      QuickSort(START_BANK_ADDRESS, last_address, 2);
    }

  }

}

void WriteEEPROM(unsigned int memory_address, byte data) 
{
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write((int)(memory_address >> 8));   // Byte mais significativo
  Wire.write((int)(memory_address & 0xFF)); // Byte menos significativo
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte ReadEEPROM(unsigned int memory_address)
{
  byte rdata = 0xFF;

  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write((int)(memory_address >> 8));   
  Wire.write((int)(memory_address & 0xFF)); 
  Wire.endTransmission();
 
  Wire.requestFrom(EEPROM_ADDRESS,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

void SpinAxis(unsigned short int desired_amount){
  servo1.attach(SERVO_MOTORS);
  servo1.write(0);
  servo.detach();

  while(map(analogRead(BALANCE), 0, 5, MIN_WEIGHT, MAX_WEIGHT) < desired_amount){
    digitalWrite(AXIS_MOTORS, HIGH);
    delay(140);
    digitalWrite(AXIS_MOTORS, LOW);
    delay(60);
  }

  servo1.attach(SERVO_MOTORS);
  servo1.write(90);
  servo.detach();
}