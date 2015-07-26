EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ph-modules
LIBS:Resonator_3pins
LIBS:prog_sockets
LIBS:schaltwandler
LIBS:w_microcontrollers
LIBS:ph-diodes
LIBS:ph-sensor
LIBS:stm32 APRS Tracker-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 6700 3500 2    60   Input ~ 0
D0
Text HLabel 6700 3400 2    60   Input ~ 0
D1
Text HLabel 6700 4400 2    60   Input ~ 0
D2
Text HLabel 6700 4300 2    60   Input ~ 0
D3
Text HLabel 6700 4200 2    60   Input ~ 0
D4
Text HLabel 6700 4100 2    60   Input ~ 0
D5
Text HLabel 6700 4000 2    60   Input ~ 0
D6
Text HLabel 6700 3900 2    60   Input ~ 0
D7
Text HLabel 5500 4500 0    60   Input ~ 0
Rst
Text HLabel 5500 4400 0    60   Input ~ 0
CS
Text HLabel 5500 4200 0    60   Input ~ 0
WR
Text HLabel 5500 4300 0    60   Input ~ 0
RS
Text HLabel 5500 4100 0    60   Input ~ 0
RD
Text HLabel 6700 3100 2    60   Output ~ 0
SD_MISO
Text HLabel 6700 3200 2    60   Input ~ 0
SD_MOSI
Text HLabel 6700 3000 2    60   Input ~ 0
SD_SCK
Text HLabel 6700 3300 2    60   Input ~ 0
SD_CS
Text HLabel 4200 3000 0    60   Input ~ 0
SD_ON
$Comp
L CONN_01X06 P301
U 1 1 55A2146D
P 5700 3450
F 0 "P301" H 5700 3800 50  0000 C CNN
F 1 "CONN_01X06" V 5800 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 5700 3450 60  0001 C CNN
F 3 "" H 5700 3450 60  0000 C CNN
	1    5700 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P302
U 1 1 55A21517
P 5700 4350
F 0 "P302" H 5700 4700 50  0000 C CNN
F 1 "CONN_01X06" V 5800 4350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 5700 4350 60  0001 C CNN
F 3 "" H 5700 4350 60  0000 C CNN
	1    5700 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P304
U 1 1 55A2156F
P 6500 4250
F 0 "P304" H 6500 4700 50  0000 C CNN
F 1 "CONN_01X08" V 6600 4250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 6500 4250 60  0001 C CNN
F 3 "" H 6500 4250 60  0000 C CNN
	1    6500 4250
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X08 P303
U 1 1 55A215CD
P 6500 3150
F 0 "P303" H 6500 3600 50  0000 C CNN
F 1 "CONN_01X08" V 6600 3150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 6500 3150 60  0001 C CNN
F 3 "" H 6500 3150 60  0000 C CNN
	1    6500 3150
	-1   0    0    -1  
$EndComp
Text HLabel 5500 3200 0    60   Input ~ 0
Reset
$Comp
L +3.3V #PWR0116
U 1 1 55A21974
P 5500 3300
F 0 "#PWR0116" H 5500 3150 50  0001 C CNN
F 1 "+3.3V" H 5500 3440 50  0000 C CNN
F 2 "" H 5500 3300 60  0000 C CNN
F 3 "" H 5500 3300 60  0000 C CNN
	1    5500 3300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR0117
U 1 1 55A219AE
P 5500 3500
F 0 "#PWR0117" H 5500 3250 50  0001 C CNN
F 1 "GND" H 5500 3350 50  0000 C CNN
F 2 "" H 5500 3500 60  0000 C CNN
F 3 "" H 5500 3500 60  0000 C CNN
	1    5500 3500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0118
U 1 1 55A21C31
P 5500 3600
F 0 "#PWR0118" H 5500 3350 50  0001 C CNN
F 1 "GND" H 5500 3450 50  0000 C CNN
F 2 "" H 5500 3600 60  0000 C CNN
F 3 "" H 5500 3600 60  0000 C CNN
	1    5500 3600
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR0119
U 1 1 55A21C48
P 5500 3700
F 0 "#PWR0119" H 5500 3550 50  0001 C CNN
F 1 "+3.3V" H 5500 3840 50  0000 C CNN
F 2 "" H 5500 3700 60  0000 C CNN
F 3 "" H 5500 3700 60  0000 C CNN
	1    5500 3700
	0    -1   -1   0   
$EndComp
$Comp
L BC807-40 Q301
U 1 1 55A21C5D
P 4700 3000
F 0 "Q301" H 4900 3075 50  0000 L CNN
F 1 "BC807-40" H 4900 3000 50  0000 L CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 4900 2925 50  0000 L CIN
F 3 "" H 4700 3000 50  0000 L CNN
	1    4700 3000
	1    0    0    1   
$EndComp
$Comp
L C C301
U 1 1 55A21D11
P 4800 3550
F 0 "C301" H 4825 3650 50  0000 L CNN
F 1 "100n" H 4825 3450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4838 3400 30  0001 C CNN
F 3 "" H 4800 3550 60  0000 C CNN
	1    4800 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0120
U 1 1 55A21D74
P 4800 3700
F 0 "#PWR0120" H 4800 3450 50  0001 C CNN
F 1 "GND" H 4800 3550 50  0000 C CNN
F 2 "" H 4800 3700 60  0000 C CNN
F 3 "" H 4800 3700 60  0000 C CNN
	1    4800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3400 4800 3400
Wire Wire Line
	4800 3400 4800 3200
$Comp
L +3.3V #PWR0121
U 1 1 55A21DE4
P 4800 2800
F 0 "#PWR0121" H 4800 2650 50  0001 C CNN
F 1 "+3.3V" H 4800 2940 50  0000 C CNN
F 2 "" H 4800 2800 60  0000 C CNN
F 3 "" H 4800 2800 60  0000 C CNN
	1    4800 2800
	1    0    0    -1  
$EndComp
$Comp
L R R301
U 1 1 55A22035
P 4350 3000
F 0 "R301" V 4430 3000 50  0000 C CNN
F 1 "1k" V 4350 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4280 3000 30  0000 C CNN
F 3 "" H 4350 3000 30  0000 C CNN
	1    4350 3000
	0    -1   -1   0   
$EndComp
NoConn ~ 5500 4600
NoConn ~ 6700 4600
NoConn ~ 6700 4500
NoConn ~ 6700 2800
NoConn ~ 6700 2900
Wire Notes Line
	6550 2600 6550 4800
Wire Notes Line
	6550 4800 5650 4800
Wire Notes Line
	5650 4800 5650 2600
Wire Notes Line
	5650 2600 6550 2600
$EndSCHEMATC
