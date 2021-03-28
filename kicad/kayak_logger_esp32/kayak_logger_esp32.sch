EESchema Schematic File Version 4
LIBS:kayak_logger_esp32-cache
EELAYER 26 0
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
L Device:R R1
U 1 1 5DBD7846
P 2616 2084
F 0 "R1" H 2686 2127 50  0000 L CNN
F 1 "R" H 2686 2041 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2546 2084 50  0001 C CNN
F 3 "~" H 2616 2084 50  0001 C CNN
	1    2616 2084
	1    0    0    -1  
$EndComp
Connection ~ 2616 2234
Wire Wire Line
	2616 2234 2616 2231
Wire Wire Line
	2616 1935 2616 1934
Connection ~ 2616 1934
Wire Wire Line
	2616 1934 2616 1517
$Comp
L Regulator_Linear:TC1262-33 U2
U 1 1 5DFAA12B
P 3326 902
F 0 "U2" H 3326 1136 50  0000 C CNN
F 1 "TC1262-33" H 3326 1050 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 3326 1127 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21373C.pdf" H 3326 602 50  0001 C CNN
	1    3326 902 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5DFAA2C0
P 3874 1120
F 0 "C2" H 3990 1163 50  0000 L CNN
F 1 "CP" H 3990 1077 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 3912 970 50  0001 C CNN
F 3 "~" H 3874 1120 50  0001 C CNN
	1    3874 1120
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5DFAA3D8
P 2748 1078
F 0 "C1" H 2864 1121 50  0000 L CNN
F 1 "CP" H 2864 1035 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 2786 928 50  0001 C CNN
F 3 "~" H 2748 1078 50  0001 C CNN
	1    2748 1078
	1    0    0    -1  
$EndComp
$Comp
L ESP32-footprints-Shem-Lib:ESP-32S U1
U 1 1 5E3224E9
P 2155 3768
F 0 "U1" H 2130 5146 60  0000 C CNN
F 1 "ESP-32S" H 2130 5045 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP-32S_thru_kayaklogger" H 2505 5118 60  0001 C CNN
F 3 "" H 1705 4218 60  0001 C CNN
	1    2155 3768
	1    0    0    -1  
$EndComp
Wire Wire Line
	2616 2234 2616 2384
Wire Wire Line
	798  2384 798  3268
Wire Wire Line
	798  3268 1205 3268
Connection ~ 1205 3268
Wire Wire Line
	1205 3268 1208 3268
Wire Wire Line
	2616 1517 639  1517
Wire Wire Line
	639  1517 639  3168
Wire Wire Line
	639  3168 1205 3168
Connection ~ 1205 3168
Wire Wire Line
	1205 3168 1208 3168
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 5E372A74
P 3828 4350
F 0 "J6" H 3933 4517 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3933 4431 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3828 4350 50  0001 C CNN
F 3 "~" H 3828 4350 50  0001 C CNN
	1    3828 4350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J1
U 1 1 5E372E3B
P 3421 2484
F 0 "J1" H 3526 2651 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3526 2565 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3421 2484 50  0001 C CNN
F 3 "~" H 3421 2484 50  0001 C CNN
	1    3421 2484
	1    0    0    -1  
$EndComp
Wire Wire Line
	3052 3418 3055 3418
Connection ~ 3055 3418
Wire Wire Line
	3055 3418 4221 3418
Wire Wire Line
	3054 3518 3055 3518
Connection ~ 3055 3518
Wire Wire Line
	3055 3518 3668 3518
Wire Wire Line
	3052 4418 3055 4418
Wire Wire Line
	4398 4418 4398 4350
Wire Wire Line
	4398 4350 4028 4350
Connection ~ 3055 4418
Wire Wire Line
	3055 4418 4398 4418
Connection ~ 4028 4350
Wire Wire Line
	4028 4350 4026 4350
Wire Wire Line
	798  2384 2616 2384
Wire Wire Line
	2616 2384 3924 2384
Wire Wire Line
	3924 2384 3924 2484
Wire Wire Line
	3924 2484 3621 2484
Connection ~ 2616 2384
Connection ~ 3621 2484
Wire Wire Line
	3621 2484 3618 2484
Text Notes 3456 2568 0    50   ~ 0
RST
Text Notes 4228 3608 0    50   ~ 0
Serial
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5E0126B9
P 1445 1001
F 0 "J3" H 1550 1168 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1550 1082 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1445 1001 50  0001 C CNN
F 3 "~" H 1445 1001 50  0001 C CNN
	1    1445 1001
	1    0    0    -1  
$EndComp
Wire Wire Line
	1643 1001 1645 1001
Wire Wire Line
	2484 1001 2484 902 
Wire Wire Line
	2484 902  2748 902 
Connection ~ 1645 1001
Wire Wire Line
	1645 1001 2484 1001
Connection ~ 3026 902 
Wire Wire Line
	3026 902  3030 902 
Wire Wire Line
	2748 930  2748 928 
Connection ~ 2748 902 
Wire Wire Line
	2748 902  3026 902 
Connection ~ 2748 928 
Wire Wire Line
	2748 928  2748 902 
Wire Wire Line
	3624 902  3626 902 
Wire Wire Line
	3874 902  3874 970 
Connection ~ 3626 902 
Wire Wire Line
	3626 902  3874 902 
Connection ~ 3874 970 
Wire Wire Line
	3874 970  3874 972 
Wire Wire Line
	3326 1200 3326 1202
Wire Wire Line
	3326 1332 3874 1332
Wire Wire Line
	3874 1332 3874 1270
Connection ~ 3326 1202
Wire Wire Line
	3326 1202 3326 1332
Connection ~ 3874 1270
Wire Wire Line
	3874 1270 3874 1267
Wire Wire Line
	2748 1225 2748 1228
Wire Wire Line
	2748 1332 3326 1332
Connection ~ 2748 1228
Wire Wire Line
	2748 1228 2748 1332
Connection ~ 3326 1332
Wire Wire Line
	1642 1101 1645 1101
Wire Wire Line
	2492 1101 2492 1332
Wire Wire Line
	2492 1332 2748 1332
Connection ~ 1645 1101
Wire Wire Line
	1645 1101 1975 1101
Connection ~ 2748 1332
Wire Wire Line
	3874 902  4164 902 
Wire Wire Line
	4164 902  4164 1517
Wire Wire Line
	4164 1517 2616 1517
Connection ~ 3874 902 
Connection ~ 2616 1517
Wire Wire Line
	1975 1101 1975 1773
Wire Wire Line
	1975 1773 918  1773
Wire Wire Line
	918  1773 918  3068
Wire Wire Line
	918  3068 1205 3068
Connection ~ 1975 1101
Wire Wire Line
	1975 1101 2492 1101
Connection ~ 1205 3068
Wire Wire Line
	1205 3068 1208 3068
Text Notes 4299 4319 0    50   ~ 0
FLASH
$Comp
L nokia_5110-3310_lcd:Nokia_5110_LCD U3
U 1 1 5E62DBF3
P 1950 5795
F 0 "U3" H 2126 5851 60  0000 L CNN
F 1 "Nokia_5110_LCD" H 2126 5750 60  0000 L CNN
F 2 "Nokia_5110-3310_LCD:Nokia_5110-3310_LCD" H 1950 5795 60  0001 C CNN
F 3 "" H 1950 5795 60  0000 C CNN
	1    1950 5795
	1    0    0    -1  
$EndComp
$Comp
L micro_sd_breakout:Micro_SD_breakout J2
U 1 1 5E638A0D
P 4562 5790
F 0 "J2" H 5392 5783 50  0000 L CNN
F 1 "Micro_SD_breakout" H 5392 5697 50  0000 L CNN
F 2 "micro_sd_breakout:micro_sd_breakout" H 5712 6090 50  0001 C CNN
F 3 "" H 4562 5790 50  0001 C CNN
	1    4562 5790
	1    0    0    -1  
$EndComp
Wire Wire Line
	1602 6095 1600 6095
Wire Wire Line
	918  6095 918  3068
Connection ~ 1600 6095
Wire Wire Line
	1600 6095 918  6095
Connection ~ 918  3068
Wire Wire Line
	3668 3518 3668 3708
Wire Wire Line
	4110 3708 4110 3623
Wire Wire Line
	3668 3708 4110 3708
Wire Wire Line
	4221 3418 4221 3517
Wire Wire Line
	3964 3623 3961 3623
Wire Wire Line
	3968 3517 3964 3517
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 5E372D81
P 3768 3517
F 0 "J5" H 3873 3684 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3873 3598 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3768 3517 50  0001 C CNN
F 3 "~" H 3768 3517 50  0001 C CNN
	1    3768 3517
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5E372CB1
P 3764 3623
F 0 "J4" H 3869 3790 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3869 3704 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3764 3623 50  0001 C CNN
F 3 "~" H 3764 3623 50  0001 C CNN
	1    3764 3623
	1    0    0    -1  
$EndComp
Connection ~ 3964 3623
Wire Wire Line
	4110 3623 3964 3623
Connection ~ 3968 3517
Wire Wire Line
	4221 3517 3968 3517
Wire Wire Line
	3666 5990 3662 5990
Wire Wire Line
	3216 5990 3216 6404
Wire Wire Line
	3216 6404 918  6404
Wire Wire Line
	918  6404 918  6095
Wire Wire Line
	3662 5990 3216 5990
Connection ~ 3662 5990
Connection ~ 918  6095
$Comp
L Connector:Conn_01x01_Male J8
U 1 1 5E64263F
P 4422 3530
F 0 "J8" H 4527 3697 50  0000 C CNN
F 1 "Conn_01x01_Male" H 4527 3611 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4422 3530 50  0001 C CNN
F 3 "~" H 4422 3530 50  0001 C CNN
	1    4422 3530
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J7
U 1 1 5E64270A
P 4421 3629
F 0 "J7" H 4526 3796 50  0000 C CNN
F 1 "Conn_01x01_Male" H 4526 3710 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4421 3629 50  0001 C CNN
F 3 "~" H 4421 3629 50  0001 C CNN
	1    4421 3629
	1    0    0    -1  
$EndComp
$Comp
L gps_breakout:gps_breakout J9
U 1 1 5E642A10
P 5222 3690
F 0 "J9" H 5398 3733 50  0000 L CNN
F 1 "gps_breakout" H 5398 3647 50  0000 L CNN
F 2 "gps_breakout:gps_breakout" H 6372 3990 50  0001 C CNN
F 3 "" H 5222 3690 50  0001 C CNN
	1    5222 3690
	1    0    0    -1  
$EndComp
Wire Wire Line
	4619 3530 4622 3530
Wire Wire Line
	4790 3530 4790 3540
Wire Wire Line
	4790 3540 4922 3540
Wire Wire Line
	4925 3540 4925 3541
Connection ~ 4622 3530
Wire Wire Line
	4622 3530 4790 3530
Connection ~ 4922 3540
Wire Wire Line
	4922 3540 4925 3540
Wire Wire Line
	4617 3629 4621 3629
Wire Wire Line
	4766 3629 4766 3640
Wire Wire Line
	4766 3640 4922 3640
Connection ~ 4621 3629
Wire Wire Line
	4621 3629 4766 3629
Connection ~ 4922 3640
Wire Wire Line
	4922 3640 4925 3640
Wire Wire Line
	4164 902  4744 902 
Wire Wire Line
	4744 902  4744 3440
Wire Wire Line
	4744 3440 4922 3440
Connection ~ 4164 902 
Connection ~ 4922 3440
Wire Wire Line
	4922 3440 4926 3440
Wire Wire Line
	3665 5490 3662 5490
Wire Wire Line
	2727 5490 2727 5130
Wire Wire Line
	2727 5130 639  5130
Wire Wire Line
	639  5130 639  3168
Connection ~ 3662 5490
Wire Wire Line
	3662 5490 2727 5490
Connection ~ 639  3168
Wire Wire Line
	3052 4018 3055 4018
Wire Wire Line
	3504 4018 3504 5590
Wire Wire Line
	3504 5590 3662 5590
Connection ~ 3055 4018
Wire Wire Line
	3055 4018 3504 4018
Connection ~ 3662 5590
Wire Wire Line
	3662 5590 3665 5590
Wire Wire Line
	3666 5690 3662 5690
Wire Wire Line
	3324 5690 3324 3218
Wire Wire Line
	3324 3218 3055 3218
Connection ~ 3662 5690
Wire Wire Line
	3662 5690 3324 5690
Connection ~ 3055 3218
Wire Wire Line
	3055 3218 3052 3218
Wire Wire Line
	3666 5790 3662 5790
Wire Wire Line
	3411 5790 3411 3918
Wire Wire Line
	3411 3918 3055 3918
Connection ~ 3662 5790
Wire Wire Line
	3662 5790 3411 5790
Connection ~ 3055 3918
Wire Wire Line
	3055 3918 3052 3918
Wire Wire Line
	3052 3818 3055 3818
Wire Wire Line
	3228 3818 3228 5890
Wire Wire Line
	3228 5890 3662 5890
Connection ~ 3055 3818
Wire Wire Line
	3055 3818 3228 3818
Connection ~ 3662 5890
Wire Wire Line
	3662 5890 3665 5890
Wire Wire Line
	639  5130 639  5895
Wire Wire Line
	639  5895 1600 5895
Connection ~ 639  5130
Connection ~ 1600 5895
Wire Wire Line
	1600 5895 1604 5895
Wire Wire Line
	4926 3740 4922 3740
Wire Wire Line
	4662 3740 4662 1332
Wire Wire Line
	4662 1332 3874 1332
Connection ~ 4922 3740
Wire Wire Line
	4922 3740 4662 3740
Connection ~ 3874 1332
Wire Wire Line
	1604 5995 1600 5995
Wire Wire Line
	1180 5995 1180 4368
Wire Wire Line
	1180 4368 1205 4368
Connection ~ 1600 5995
Wire Wire Line
	1600 5995 1180 5995
Connection ~ 1205 4368
Wire Wire Line
	1205 4368 1208 4368
Wire Wire Line
	1603 5795 1600 5795
Wire Wire Line
	1155 5795 1155 4268
Wire Wire Line
	1155 4268 1205 4268
Connection ~ 1600 5795
Wire Wire Line
	1600 5795 1155 5795
Connection ~ 1205 4268
Wire Wire Line
	1205 4268 1209 4268
Wire Wire Line
	1603 5695 1600 5695
Wire Wire Line
	1128 5695 1128 4168
Wire Wire Line
	1128 4168 1205 4168
Connection ~ 1600 5695
Wire Wire Line
	1600 5695 1128 5695
Connection ~ 1205 4168
Wire Wire Line
	1205 4168 1209 4168
Wire Wire Line
	1603 5595 1600 5595
Wire Wire Line
	1098 5595 1098 4068
Wire Wire Line
	1098 4068 1205 4068
Connection ~ 1600 5595
Wire Wire Line
	1600 5595 1098 5595
Connection ~ 1205 4068
Wire Wire Line
	1205 4068 1209 4068
Wire Wire Line
	1604 5495 1600 5495
Wire Wire Line
	1079 5495 1079 3968
Wire Wire Line
	1079 3968 1205 3968
Connection ~ 1600 5495
Wire Wire Line
	1600 5495 1079 5495
Connection ~ 1205 3968
Wire Wire Line
	1205 3968 1208 3968
Wire Wire Line
	1603 5395 1600 5395
Wire Wire Line
	1051 5395 1051 3868
Wire Wire Line
	1051 3868 1205 3868
Connection ~ 1600 5395
Wire Wire Line
	1600 5395 1051 5395
Connection ~ 1205 3868
Wire Wire Line
	1205 3868 1209 3868
$EndSCHEMATC
