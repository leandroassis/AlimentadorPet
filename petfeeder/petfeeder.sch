EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Pet Feeder Hardware Schema"
Date "2021-03-21"
Rev "v3"
Comp "UFRJ - Universidade Federal do Rio de Janeiro"
Comment1 "Made by: Leandro Assis dos Santos"
Comment2 "Rio de Janeiro, RJ - Brazil"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP-12F U?
U 1 1 6171FE40
P 7650 3500
F 0 "U?" H 7650 4481 50  0000 C CNN
F 1 "ESP-12F" H 7650 4390 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 7650 3500 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 7300 3600 50  0001 C CNN
	1    7650 3500
	1    0    0    -1  
$EndComp
$Comp
L Timer_RTC:DS1307+ U?
U 1 1 61722042
P 5100 2650
F 0 "U?" H 5644 2696 50  0000 L CNN
F 1 "DS1307+" H 5644 2605 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5100 2150 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1307.pdf" H 5100 2450 50  0001 C CNN
	1    5100 2650
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:LCD-016N002L U?
U 1 1 61723A65
P 6200 1350
F 0 "U?" V 6246 506 50  0000 R CNN
F 1 "LCD-016N002L" V 6155 506 50  0000 R CNN
F 2 "Display:LCD-016N002L" H 6220 430 50  0001 C CNN
F 3 "http://www.vishay.com/docs/37299/37299.pdf" H 6700 1050 50  0001 C CNN
	1    6200 1350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 617291AB
P 5100 3200
F 0 "#PWR?" H 5100 2950 50  0001 C CNN
F 1 "GND" H 5105 3027 50  0000 C CNN
F 2 "" H 5100 3200 50  0001 C CNN
F 3 "" H 5100 3200 50  0001 C CNN
	1    5100 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61729DA8
P 7650 4300
F 0 "#PWR?" H 7650 4050 50  0001 C CNN
F 1 "GND" H 7655 4127 50  0000 C CNN
F 2 "" H 7650 4300 50  0001 C CNN
F 3 "" H 7650 4300 50  0001 C CNN
	1    7650 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6172A957
P 7650 2350
F 0 "#PWR?" H 7650 2200 50  0001 C CNN
F 1 "+3.3V" H 7665 2523 50  0000 C CNN
F 2 "" H 7650 2350 50  0001 C CNN
F 3 "" H 7650 2350 50  0001 C CNN
	1    7650 2350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
