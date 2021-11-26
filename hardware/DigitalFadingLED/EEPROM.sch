EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 34AA02_EEPROM:34AA02 U6
U 1 1 61526810
P 5500 3100
F 0 "U6" H 5500 3265 50  0000 C CNN
F 1 "34AA02" H 5500 3174 50  0000 C CNN
F 2 "34AA02:34AA02" H 5500 3100 50  0001 C CNN
F 3 "" H 5500 3100 50  0001 C CNN
	1    5500 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R18
U 1 1 615270EA
P 4500 2900
F 0 "R18" H 4568 2946 50  0000 L CNN
F 1 "2k" H 4568 2855 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 4500 2900 50  0001 C CNN
F 3 "~" H 4500 2900 50  0001 C CNN
	1    4500 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R17
U 1 1 61527AF8
P 4000 2900
F 0 "R17" H 4068 2946 50  0000 L CNN
F 1 "2k" H 4068 2855 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 4000 2900 50  0001 C CNN
F 3 "~" H 4000 2900 50  0001 C CNN
	1    4000 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3000 4500 3200
Wire Wire Line
	4500 3200 4900 3200
Wire Wire Line
	4000 3000 4000 3600
Wire Wire Line
	4000 3600 4900 3600
Wire Wire Line
	4000 3600 3500 3600
Connection ~ 4000 3600
Wire Wire Line
	4500 3200 3500 3200
Connection ~ 4500 3200
Wire Wire Line
	4900 3400 4500 3400
Wire Wire Line
	4500 3400 4500 3950
$Comp
L power:GND #PWR0143
U 1 1 6152887B
P 4500 3950
F 0 "#PWR0143" H 4500 3700 50  0001 C CNN
F 1 "GND" H 4505 3777 50  0000 C CNN
F 2 "" H 4500 3950 50  0001 C CNN
F 3 "" H 4500 3950 50  0001 C CNN
	1    4500 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0144
U 1 1 61528DD8
P 6500 2950
F 0 "#PWR0144" H 6500 2800 50  0001 C CNN
F 1 "+3.3V" H 6515 3123 50  0000 C CNN
F 2 "" H 6500 2950 50  0001 C CNN
F 3 "" H 6500 2950 50  0001 C CNN
	1    6500 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3200 6500 3200
Wire Wire Line
	6500 3200 6500 2950
Wire Wire Line
	6100 3400 6500 3400
Wire Wire Line
	6500 3400 6500 3600
Wire Wire Line
	6100 3600 6500 3600
Connection ~ 6500 3600
Wire Wire Line
	6500 3600 6500 4000
$Comp
L power:GND #PWR0145
U 1 1 6152A1C7
P 6500 4000
F 0 "#PWR0145" H 6500 3750 50  0001 C CNN
F 1 "GND" H 6505 3827 50  0000 C CNN
F 2 "" H 6500 4000 50  0001 C CNN
F 3 "" H 6500 4000 50  0001 C CNN
	1    6500 4000
	1    0    0    -1  
$EndComp
Text HLabel 3500 3200 0    50   Input ~ 0
SCL
Text HLabel 3500 3600 0    50   Input ~ 0
SDA
$Comp
L power:+3.3V #PWR0146
U 1 1 6152A97D
P 4000 2700
F 0 "#PWR0146" H 4000 2550 50  0001 C CNN
F 1 "+3.3V" H 4015 2873 50  0000 C CNN
F 2 "" H 4000 2700 50  0001 C CNN
F 3 "" H 4000 2700 50  0001 C CNN
	1    4000 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0147
U 1 1 6152B158
P 4500 2700
F 0 "#PWR0147" H 4500 2550 50  0001 C CNN
F 1 "+3.3V" H 4515 2873 50  0000 C CNN
F 2 "" H 4500 2700 50  0001 C CNN
F 3 "" H 4500 2700 50  0001 C CNN
	1    4500 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2800 4500 2700
Wire Wire Line
	4000 2800 4000 2700
$EndSCHEMATC
