EESchema Schematic File Version 4
LIBS:esp32_mpu9250-cache
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
L Connector:Conn_01x04_Male J2
U 1 1 5DBD7E18
P 5940 3414
F 0 "J2" H 6045 3681 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6045 3595 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5940 3414 50  0001 C CNN
F 3 "~" H 5940 3414 50  0001 C CNN
	1    5940 3414
	1    0    0    -1  
$EndComp
Wire Wire Line
	6654 3314 6140 3314
Connection ~ 6140 3314
Wire Wire Line
	6140 3314 6136 3314
Wire Wire Line
	5111 3525 5111 3760
Wire Wire Line
	5111 3760 6656 3760
Wire Wire Line
	6656 3760 6656 3414
Wire Wire Line
	6656 3414 6564 3414
Connection ~ 6140 3414
Wire Wire Line
	6140 3414 6137 3414
Connection ~ 6564 3414
Wire Wire Line
	6564 3414 6140 3414
Wire Wire Line
	5278 1822 6444 1822
$Comp
L Regulator_Linear:TC1262-33 U2
U 1 1 5DFAA12B
P 6918 758
F 0 "U2" H 6918 992 50  0000 C CNN
F 1 "TC1262-33" H 6918 906 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6918 983 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21373C.pdf" H 6918 458 50  0001 C CNN
	1    6918 758 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5DFAA2C0
P 7734 980
F 0 "C2" H 7850 1023 50  0000 L CNN
F 1 "CP" H 7850 937 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 7772 830 50  0001 C CNN
F 3 "~" H 7734 980 50  0001 C CNN
	1    7734 980 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5DFAA3D8
P 6396 930
F 0 "C1" H 6512 973 50  0000 L CNN
F 1 "CP" H 6512 887 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 6434 780 50  0001 C CNN
F 3 "~" H 6396 930 50  0001 C CNN
	1    6396 930 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7214 758  7218 758 
Wire Wire Line
	7734 758  7734 830 
Connection ~ 7218 758 
Wire Wire Line
	7218 758  7734 758 
Connection ~ 7734 830 
Wire Wire Line
	7734 830  7734 832 
Wire Wire Line
	6396 783  6396 780 
Connection ~ 6396 780 
Wire Wire Line
	6396 780  6396 758 
Wire Wire Line
	6396 1076 6396 1080
Wire Wire Line
	6396 1148 6918 1148
Wire Wire Line
	6918 1148 6918 1058
Connection ~ 6396 1080
Wire Wire Line
	6396 1080 6396 1148
Connection ~ 6918 1058
Wire Wire Line
	6918 1058 6918 1056
Wire Wire Line
	7734 1129 7734 1130
Wire Wire Line
	7734 1164 7201 1164
Wire Wire Line
	7028 1164 7028 1148
Wire Wire Line
	7028 1148 6918 1148
Connection ~ 7734 1130
Wire Wire Line
	7734 1130 7734 1164
Connection ~ 6918 1148
Wire Wire Line
	7734 758  8094 758 
Wire Wire Line
	8094 758  8094 1455
Wire Wire Line
	8094 1455 4149 1455
Wire Wire Line
	4149 1455 4149 1517
Connection ~ 7734 758 
Wire Wire Line
	6654 1628 6074 1628
Wire Wire Line
	6074 1628 6074 758 
Wire Wire Line
	6074 758  6396 758 
Connection ~ 7201 1164
Wire Wire Line
	7201 1164 7028 1164
Wire Wire Line
	6619 758  6618 758 
Connection ~ 6396 758 
Connection ~ 6618 758 
Wire Wire Line
	6618 758  6396 758 
Wire Wire Line
	6384 1938 6385 1938
Wire Wire Line
	5490 1938 6384 1938
Connection ~ 6384 1938
Wire Wire Line
	6384 1938 6384 2599
Wire Wire Line
	6384 2599 7738 2599
Connection ~ 6384 2599
Wire Wire Line
	6384 2599 6384 2600
Wire Wire Line
	6444 1822 6444 2543
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5E0126B9
P 7593 2172
F 0 "J3" H 7698 2339 50  0000 C CNN
F 1 "Conn_01x02_Male" H 7698 2253 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7593 2172 50  0001 C CNN
F 3 "~" H 7593 2172 50  0001 C CNN
	1    7593 2172
	1    0    0    -1  
$EndComp
Wire Wire Line
	6654 1944 8085 1944
Wire Wire Line
	8085 1944 8085 2172
Wire Wire Line
	8085 2172 7793 2172
Wire Wire Line
	6654 1628 6654 1944
Connection ~ 6654 1944
Connection ~ 7793 2172
Wire Wire Line
	7793 2172 7790 2172
Wire Wire Line
	7201 2354 7938 2354
Wire Wire Line
	7938 2354 7938 2272
Wire Wire Line
	7938 2272 7793 2272
Connection ~ 7793 2272
Wire Wire Line
	7793 2272 7791 2272
Wire Wire Line
	7201 1164 7201 2354
Wire Wire Line
	7201 2354 7201 2417
Wire Wire Line
	7201 2417 6564 2417
Connection ~ 7201 2354
Wire Wire Line
	6564 2417 6564 3414
Wire Wire Line
	6654 1944 6654 3314
$Comp
L ESP32-footprints-Shem-Lib:ESP-32S U1
U 1 1 5E3224E9
P 2155 3768
F 0 "U1" H 2130 5146 60  0000 C CNN
F 1 "ESP-32S" H 2130 5045 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP-32S_thru_mpu9250" H 2505 5118 60  0001 C CNN
F 3 "" H 1705 4218 60  0001 C CNN
	1    2155 3768
	1    0    0    -1  
$EndComp
Wire Wire Line
	5490 3989 3567 3989
Wire Wire Line
	3567 3989 3567 3418
Wire Wire Line
	3567 3418 3055 3418
Wire Wire Line
	5490 1938 5490 3989
Connection ~ 3055 3418
Wire Wire Line
	3055 3418 3053 3418
Wire Wire Line
	5278 4068 3496 4068
Wire Wire Line
	3496 4068 3496 3518
Wire Wire Line
	3496 3518 3055 3518
Wire Wire Line
	5278 1822 5278 4068
Connection ~ 3055 3518
Wire Wire Line
	3055 3518 3052 3518
Wire Wire Line
	3654 3525 5111 3525
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
Connection ~ 2616 1517
Connection ~ 1205 3168
Wire Wire Line
	1205 3168 1208 3168
Wire Wire Line
	2616 1517 4149 1517
Wire Wire Line
	798  2384 2409 2384
Wire Wire Line
	2409 2384 2409 1287
Wire Wire Line
	2409 1287 8339 1287
Wire Wire Line
	8339 1287 8339 3143
Connection ~ 2409 2384
Wire Wire Line
	2409 2384 2616 2384
Wire Wire Line
	6774 2626 6774 2628
Wire Wire Line
	6774 4418 3055 4418
Connection ~ 3055 4418
Wire Wire Line
	3055 4418 3052 4418
Wire Wire Line
	6136 3514 6140 3514
Wire Wire Line
	6354 3514 6354 4122
Wire Wire Line
	6354 4122 3444 4122
Wire Wire Line
	3444 4122 3444 3318
Wire Wire Line
	3444 3318 3055 3318
Connection ~ 6140 3514
Wire Wire Line
	6140 3514 6354 3514
Connection ~ 3055 3318
Wire Wire Line
	3055 3318 3052 3318
Wire Wire Line
	6136 3614 6140 3614
Wire Wire Line
	6271 3614 6271 4167
Wire Wire Line
	6271 4167 3364 4167
Wire Wire Line
	3364 4167 3364 3618
Wire Wire Line
	3364 3618 3055 3618
Connection ~ 6140 3614
Wire Wire Line
	6140 3614 6271 3614
Connection ~ 3055 3618
Wire Wire Line
	3055 3618 3054 3618
Text Notes 7164 3270 0    50   ~ 0
PGM pins
Text Notes 5916 3072 0    50   ~ 0
IMU pins
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 5E372A74
P 6888 2898
F 0 "J6" H 6993 3065 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6993 2979 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6888 2898 50  0001 C CNN
F 3 "~" H 6888 2898 50  0001 C CNN
	1    6888 2898
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5E372CB1
P 6870 3092
F 0 "J4" H 6975 3259 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6975 3173 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6870 3092 50  0001 C CNN
F 3 "~" H 6870 3092 50  0001 C CNN
	1    6870 3092
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 5E372D81
P 6875 3210
F 0 "J5" H 6980 3377 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6980 3291 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6875 3210 50  0001 C CNN
F 3 "~" H 6875 3210 50  0001 C CNN
	1    6875 3210
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J1
U 1 1 5E372E3B
P 6865 3360
F 0 "J1" H 6970 3527 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6970 3441 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6865 3360 50  0001 C CNN
F 3 "~" H 6865 3360 50  0001 C CNN
	1    6865 3360
	1    0    0    -1  
$EndComp
Wire Wire Line
	7143 2628 7143 2898
Wire Wire Line
	7143 2898 7088 2898
Wire Wire Line
	6774 2628 7143 2628
Connection ~ 6774 2628
Wire Wire Line
	6774 2628 6774 4418
Connection ~ 7088 2898
Wire Wire Line
	7088 2898 7084 2898
Wire Wire Line
	6444 2543 7169 2543
Wire Wire Line
	7169 2543 7169 3092
Wire Wire Line
	7169 3092 7070 3092
Connection ~ 6444 2543
Wire Wire Line
	6444 2543 6444 2547
Connection ~ 7070 3092
Wire Wire Line
	7070 3092 7063 3092
Wire Wire Line
	7738 3087 7250 3087
Wire Wire Line
	7250 3087 7250 3210
Wire Wire Line
	7250 3210 7075 3210
Wire Wire Line
	7738 2599 7738 3087
Connection ~ 7075 3210
Wire Wire Line
	7075 3210 7072 3210
Wire Wire Line
	7317 3143 7317 3360
Wire Wire Line
	7317 3360 7065 3360
Wire Wire Line
	7317 3143 8339 3143
Connection ~ 7065 3360
Wire Wire Line
	7065 3360 7061 3360
Wire Wire Line
	3654 2504 989  2504
Wire Wire Line
	989  2504 989  3068
Wire Wire Line
	989  3068 1205 3068
Wire Wire Line
	3654 2504 3654 3525
Connection ~ 1205 3068
Wire Wire Line
	1205 3068 1208 3068
$EndSCHEMATC
