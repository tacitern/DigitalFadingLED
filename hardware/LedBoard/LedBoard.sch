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
L dk_LED-Indication-Discrete:ASMB-TTB0-0A3A2 D1
U 1 1 6191D7E3
P 6300 3350
F 0 "D1" H 6200 3950 60  0000 C CNN
F 1 "ASMB-TTB0-0A3A2" H 6300 2800 60  0001 C CNN
F 2 "digikey-footprints:6-PLCC_3.5x3.5mm" H 6500 3550 60  0001 L CNN
F 3 "https://docs.broadcom.com/docs/AV02-4415EN" H 6500 3650 60  0001 L CNN
F 4 "516-3281-1-ND" H 6500 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "ASMB-TTB0-0A3A2" H 6500 3850 60  0001 L CNN "MPN"
F 6 "Optoelectronics" H 6500 3950 60  0001 L CNN "Category"
F 7 "LED Indication - Discrete" H 6500 4050 60  0001 L CNN "Family"
F 8 "https://docs.broadcom.com/docs/AV02-4415EN" H 6500 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/broadcom-limited/ASMB-TTB0-0A3A2/516-3281-1-ND/5695368" H 6500 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "LED RGB DIFFUSED 6PLCC SMD" H 6500 4350 60  0001 L CNN "Description"
F 11 "Broadcom Limited" H 6500 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6500 4550 60  0001 L CNN "Status"
	1    6300 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic_Shielded:Conn_01x06_Shielded J1
U 1 1 6191FD81
P 4150 3550
F 0 "J1" H 4238 3371 50  0000 L CNN
F 1 "Conn_01x06_Shielded" H 4238 3462 50  0000 L CNN
F 2 "Molex_FFC:molex_FFC_0522070633" H 4150 3550 50  0001 C CNN
F 3 "~" H 4150 3550 50  0001 C CNN
	1    4150 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 3650 5550 3550
Wire Wire Line
	5550 3550 6000 3550
Wire Wire Line
	5400 3550 5400 3350
Wire Wire Line
	5400 3350 6000 3350
Wire Wire Line
	6500 3350 6850 3350
Wire Wire Line
	6850 3350 6850 3150
Wire Wire Line
	6850 3150 5250 3150
Wire Wire Line
	5250 3150 5250 3450
Wire Wire Line
	5100 3350 5100 3000
Wire Wire Line
	5100 3000 7000 3000
Wire Wire Line
	7000 3000 7000 3550
Wire Wire Line
	7000 3550 6500 3550
Wire Wire Line
	6500 3750 7150 3750
Wire Wire Line
	7150 3750 7150 2850
Wire Wire Line
	7150 2850 4950 2850
Wire Wire Line
	4950 2850 4950 3250
Text Notes 4350 3750 0    50   ~ 0
LED_BLUE_IN
Text Notes 4350 3650 0    50   ~ 0
LED_GREEN_IN
Text Notes 4350 3550 0    50   ~ 0
LED_RED_IN
Text Notes 4350 3450 0    50   ~ 0
LED_RED_OUT
Text Notes 4350 3350 0    50   ~ 0
LED_GREEN_OUT
Text Notes 4350 3250 0    50   ~ 0
LED_BLUE_OUT
NoConn ~ 4150 3050
Wire Wire Line
	4350 3250 4950 3250
Wire Wire Line
	4350 3350 5100 3350
Wire Wire Line
	4350 3450 5250 3450
Wire Wire Line
	4350 3550 5400 3550
Wire Wire Line
	4350 3650 5550 3650
Wire Wire Line
	4350 3750 6000 3750
$EndSCHEMATC
