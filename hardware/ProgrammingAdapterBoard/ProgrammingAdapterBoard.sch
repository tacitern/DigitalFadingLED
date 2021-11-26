EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Connector_Generic:Conn_02x07_Odd_Even J1
U 1 1 61913376
P 3950 3100
F 0 "J1" H 4000 3617 50  0000 C CNN
F 1 "Conn_02x07_Odd_Even" H 4000 3526 50  0000 C CNN
F 2 "FTSH-107-01-L-DV-K-A:SAMTEC_FTSH-107-01-L-DV-K-A" H 3950 3100 50  0001 C CNN
F 3 "~" H 3950 3100 50  0001 C CNN
	1    3950 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J2
U 1 1 619146A9
P 7300 3050
F 0 "J2" H 7380 3092 50  0000 L CNN
F 1 "Conn_01x07" H 7380 3001 50  0000 L CNN
F 2 "851-87-007-20-001101:851-87-007-20-001101" H 7300 3050 50  0001 C CNN
F 3 "~" H 7300 3050 50  0001 C CNN
	1    7300 3050
	1    0    0    -1  
$EndComp
NoConn ~ 3750 2800
NoConn ~ 3750 3200
NoConn ~ 4250 3200
NoConn ~ 4250 3100
NoConn ~ 4250 2800
Wire Wire Line
	3750 3300 2100 3300
Wire Wire Line
	3750 3100 2100 3100
Wire Wire Line
	2100 3100 2100 3300
Wire Wire Line
	3750 3000 2100 3000
Wire Wire Line
	2100 3000 2100 3100
Connection ~ 2100 3100
Wire Wire Line
	2100 3300 2100 3600
Connection ~ 2100 3300
Wire Wire Line
	3750 3400 2800 3400
Wire Wire Line
	2100 2900 2100 2650
Wire Wire Line
	2100 2900 3750 2900
Wire Wire Line
	5200 2900 4250 2900
Wire Wire Line
	5200 3000 4250 3000
Wire Wire Line
	5200 3300 4250 3300
Wire Wire Line
	5200 3400 4250 3400
Wire Wire Line
	7100 2750 6150 2750
Wire Wire Line
	7100 2850 6150 2850
Wire Wire Line
	7100 2950 6150 2950
Wire Wire Line
	7100 3050 6150 3050
Wire Wire Line
	7100 3150 6150 3150
Wire Wire Line
	7100 3250 6150 3250
Wire Wire Line
	7100 3350 6150 3350
Text Notes 3250 2900 0    50   ~ 0
T_VCC
Text Notes 3250 3000 0    50   ~ 0
GND
Text Notes 3250 3100 0    50   ~ 0
GND
Text Notes 3250 3300 0    50   ~ 0
GNDDetect
Text Notes 3250 3400 0    50   ~ 0
T_VCP_RX
Text Notes 4400 3400 0    50   ~ 0
T_VCP_TX
Text Notes 4400 3300 0    50   ~ 0
T_NRST
Text Notes 4400 3000 0    50   ~ 0
T_SWCLK
Text Notes 4400 2900 0    50   ~ 0
T_SWDIO
Text Label 5200 2900 2    50   ~ 0
SWDIO
Text Label 5200 3000 2    50   ~ 0
SWCLK
Text Label 5200 3300 2    50   ~ 0
NRST
Text Label 5200 3400 2    50   ~ 0
VCP_TX
Text Label 2800 3400 0    50   ~ 0
VCP_RX
$Comp
L power:GND #PWR0101
U 1 1 61917FA9
P 2100 3600
F 0 "#PWR0101" H 2100 3350 50  0001 C CNN
F 1 "GND" H 2105 3427 50  0000 C CNN
F 2 "" H 2100 3600 50  0001 C CNN
F 3 "" H 2100 3600 50  0001 C CNN
	1    2100 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 61918329
P 2100 2650
F 0 "#PWR0102" H 2100 2500 50  0001 C CNN
F 1 "+3.3V" H 2115 2823 50  0000 C CNN
F 2 "" H 2100 2650 50  0001 C CNN
F 3 "" H 2100 2650 50  0001 C CNN
	1    2100 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0103
U 1 1 61918657
P 6150 2500
F 0 "#PWR0103" H 6150 2350 50  0001 C CNN
F 1 "+3.3V" H 6165 2673 50  0000 C CNN
F 2 "" H 6150 2500 50  0001 C CNN
F 3 "" H 6150 2500 50  0001 C CNN
	1    6150 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 61918F1E
P 6150 3600
F 0 "#PWR0104" H 6150 3350 50  0001 C CNN
F 1 "GND" H 6155 3427 50  0000 C CNN
F 2 "" H 6150 3600 50  0001 C CNN
F 3 "" H 6150 3600 50  0001 C CNN
	1    6150 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2750 6150 2500
Wire Wire Line
	6150 3350 6150 3600
Text Label 6150 3050 0    50   ~ 0
VCP_TX
Text Label 6150 3250 0    50   ~ 0
NRST
Text Label 6150 2950 0    50   ~ 0
SWCLK
Text Label 6150 2850 0    50   ~ 0
SWDIO
Text Label 6150 3150 0    50   ~ 0
VCP_RX
$EndSCHEMATC
