EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	2600 2500 1450 2500
Wire Wire Line
	2600 2900 2300 2900
Wire Wire Line
	2300 2900 2300 3500
$Comp
L power:GND #PWR0127
U 1 1 614E918B
P 2300 3500
F 0 "#PWR0127" H 2300 3250 50  0001 C CNN
F 1 "GND" H 2305 3327 50  0000 C CNN
F 2 "" H 2300 3500 50  0001 C CNN
F 3 "" H 2300 3500 50  0001 C CNN
	1    2300 3500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 2700 4400 2700
Wire Wire Line
	4400 2700 4400 2750
$Comp
L power:GND #PWR0128
U 1 1 614EA3D1
P 4400 2750
F 0 "#PWR0128" H 4400 2500 50  0001 C CNN
F 1 "GND" H 4405 2577 50  0000 C CNN
F 2 "" H 4400 2750 50  0001 C CNN
F 3 "" H 4400 2750 50  0001 C CNN
	1    4400 2750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4950 2400 3800 2400
Wire Wire Line
	3800 3200 4950 3200
Wire Wire Line
	1450 3200 2600 3200
Text HLabel 1450 2500 0    50   Input ~ 0
TIM_GREEN
Text HLabel 1450 3200 0    50   Input ~ 0
TIM_BLUE
Text HLabel 4950 2400 2    50   Input ~ 0
LED_GREEN
Text HLabel 4950 3200 2    50   Input ~ 0
LED_BLUE
$Comp
L QS6K21:QS6K21 U3
U 1 1 615459EF
P 3200 2500
F 0 "U3" H 3200 2965 50  0000 C CNN
F 1 "QS6K21" H 3200 2874 50  0000 C CNN
F 2 "QS6K21_2Nch:QS6K21TR" H 3200 2500 50  0001 C CNN
F 3 "" H 3200 2500 50  0001 C CNN
	1    3200 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 2900 9050 2900
Connection ~ 9250 2900
Wire Wire Line
	6700 4050 9250 4050
Wire Wire Line
	9250 4050 9250 2900
$Comp
L QS6M4:QS6M4 U4
U 1 1 6154EB45
P 8450 2200
F 0 "U4" H 8450 2365 50  0000 C CNN
F 1 "QS6M4" H 8450 2274 50  0000 C CNN
F 2 "QS6M4:QS6K21TR" H 8450 2200 50  0001 C CNN
F 3 "" H 8450 2200 50  0001 C CNN
	1    8450 2200
	1    0    0    -1  
$EndComp
Text Notes 7000 4050 0    50   ~ 0
OPEN DRAIN
Text HLabel 6700 2700 0    50   Input ~ 0
TIM_RED
Text HLabel 10200 2400 2    50   Input ~ 0
LED_RED
Text HLabel 6700 3300 0    50   Output ~ 0
OUT_LUM
Text HLabel 6700 4050 0    50   Input ~ 0
TIM_LUM
Wire Wire Line
	6700 2700 7850 2700
Wire Wire Line
	7850 3300 6700 3300
Wire Wire Line
	9050 2400 10200 2400
$Comp
L power:GND #PWR0129
U 1 1 614EABEB
P 7150 2450
F 0 "#PWR0129" H 7150 2200 50  0001 C CNN
F 1 "GND" H 7155 2277 50  0000 C CNN
F 2 "" H 7150 2450 50  0001 C CNN
F 3 "" H 7150 2450 50  0001 C CNN
	1    7150 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2400 7150 2450
Wire Wire Line
	7850 2400 7150 2400
$Comp
L power:VCC #PWR0126
U 1 1 614E272F
P 10800 2050
F 0 "#PWR0126" H 10800 1900 50  0001 C CNN
F 1 "VCC" H 10815 2223 50  0000 C CNN
F 2 "" H 10800 2050 50  0001 C CNN
F 3 "" H 10800 2050 50  0001 C CNN
	1    10800 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 2900 9250 2900
$Comp
L Device:R_Small_US R12
U 1 1 614E0E19
P 9500 2900
F 0 "R12" V 9295 2900 50  0000 C CNN
F 1 "10k" V 9386 2900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" H 9500 2900 50  0001 C CNN
F 3 "~" H 9500 2900 50  0001 C CNN
	1    9500 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	10800 2050 10800 2900
Connection ~ 10800 2900
Wire Wire Line
	10800 2900 10800 3300
Wire Wire Line
	9050 3300 10800 3300
Wire Wire Line
	9600 2900 10800 2900
$EndSCHEMATC
