# Razer Atrox XBO USB packets reference

## Notes
* Two USB end-points:
  * 0x01 used for sending the init/keepalive packet
  * 0x81 used for receiving data from the controller
* 1st byte is packet type:
  * 0x03 for heartbeat
  * 0x05 for init controller
  * 0x07 for guide button
  * 0x20 for button press data
* See
  * https://github.com/paroj/xpad/blob/master/xpad.c
  * https://github.com/quantus/xbox-one-controller-protocol/blob/master/README.md
  
  
## Handshake Packets

```
000007: PnP Event: Device Connected (UP), 2020-07-20 11:23:10.8806610 +2.6730150 (1. Device: Razer Atrox Arcade Stick)
The USB device has just been connected to the system.

000008: PnP Event: Query Interface (DOWN), 2020-07-20 11:23:10.8806676 +0.0000066 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {2AEB0243-6A6E-486B-82FC-D815F6B97006}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0

000009: PnP Event: Query Interface (UP), 2020-07-20 11:23:10.8806696 +0.0000020 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {2AEB0243-6A6E-486B-82FC-D815F6B97006}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0

000010: PnP Event: Query Interface (DOWN), 2020-07-20 11:23:10.8806703 +0.0000007 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {DC7A8E51-49B3-4A3A-9E81-625205E7D729}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0

000011: PnP Event: Query Interface (UP), 2020-07-20 11:23:10.8806711 +0.0000008 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {DC7A8E51-49B3-4A3A-9E81-625205E7D729}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0x00000000
Information: 0x0

000012: PnP Event: Query Interface (DOWN), 2020-07-20 11:23:10.8806921 +0.0000210 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {DEEE98EA-C0A1-42C3-9738-A04606C84E93}
Interface Size: 0xc8 bytes
Interface Version: 0x603
Status: 0xc00000bb
Information: 0x0

000013: PnP Event: Query Interface (UP), 2020-07-20 11:23:10.8806952 +0.0000031 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {DEEE98EA-C0A1-42C3-9738-A04606C84E93}
Interface Size: 0xc8 bytes
Interface Version: 0x603
Status: 0x00000000
Information: 0x0

000014: Get Descriptor Request (DOWN), 2020-07-20 11:23:10.8806967 +0.0000015 (1. Device: Razer Atrox Arcade Stick)
Descriptor Type: Device
Descriptor Index: 0x0
Transfer Buffer Size: 0x12 bytes

000015: Control Transfer (UP), 2020-07-20 11:23:10.8815812 +0.0008845. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: Control Pipe
 12 01 00 02 FF FF FF 40 32 15 00 0A 00 01 01 02   ....ÿÿÿ@2.......
 03 01                                             ..
Setup Packet
 80 06 00 01 00 00 12 00                           €.......
Recipient: Device
Request Type: Standard
Direction: Device->Host
Request: 0x6 (GET_DESCRIPTOR)
Value: 0x100
Index: 0x0
Length: 0x12

000016: Get Descriptor Request (DOWN), 2020-07-20 11:23:10.8815892 +0.0000080 (1. Device: Razer Atrox Arcade Stick)
Descriptor Type: Configuration
Descriptor Index: 0x0
Transfer Buffer Size: 0x9 bytes

000017: Control Transfer (UP), 2020-07-20 11:23:10.8835773 +0.0019881. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: Control Pipe
 09 02 20 00 01 01 00 A0 64                        .. .... d
Setup Packet
 80 06 00 02 00 00 09 00                           €.......
Recipient: Device
Request Type: Standard
Direction: Device->Host
Request: 0x6 (GET_DESCRIPTOR)
Value: 0x200
Index: 0x0
Length: 0x9

000018: Get Descriptor Request (DOWN), 2020-07-20 11:23:10.8835849 +0.0000076 (1. Device: Razer Atrox Arcade Stick)
Descriptor Type: Configuration
Descriptor Index: 0x0
Transfer Buffer Size: 0x20 bytes

000019: Control Transfer (UP), 2020-07-20 11:23:10.8855911 +0.0020062. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: Control Pipe
 09 02 20 00 01 01 00 A0 64 09 04 00 00 02 FF 47   .. .... d.....ÿG
 D0 00 07 05 01 03 40 00 04 07 05 81 03 40 00 04   Ð.....@.....@..

Setup Packet
 80 06 00 02 00 00 20 00                           €..... .
Recipient: Device
Request Type: Standard
Direction: Device->Host
Request: 0x6 (GET_DESCRIPTOR)
Value: 0x200
Index: 0x0
Length: 0x20

000020: Get Status Request (DOWN), 2020-07-20 11:23:10.8855985 +0.0000074 (1. Device: Razer Atrox Arcade Stick)
Get status from Device. Data length 0x2 bytes
 B0 88                                             °ˆ

000021: Control Transfer (UP), 2020-07-20 11:23:10.8875700 +0.0019715. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: Control Pipe
 02 00                                             ..
Setup Packet
 80 00 00 00 00 00 02 00                           €.......
Recipient: Device
Request Type: Standard
Direction: Device->Host
Request: 0x0 (GET_STATUS)
Value: 0x0
Index: 0x0
Length: 0x2

000022: PnP Event: Query Interface (DOWN), 2020-07-20 11:23:10.8875784 +0.0000084 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {B1A96A13-3DE0-4574-9B01-C08FEAB318D6}
Interface Size: 0x48 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0

000023: PnP Event: Query Interface (UP), 2020-07-20 11:23:10.8875818 +0.0000034 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {B1A96A13-3DE0-4574-9B01-C08FEAB318D6}
Interface Size: 0x48 bytes
Interface Version: 0x1
Status: 0x00000000
Information: 0x0

000024: Select Configuration (DOWN), 2020-07-20 11:23:10.8875930 +0.0000112 (1. Device: Razer Atrox Arcade Stick)
Configuration Index: 1

000025: Select Configuration (UP), 2020-07-20 11:23:10.8945454 +0.0000003. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Configuration Index: 1
Configuration Handle: 0x697fabf0

000030: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1195789 +0.0329859. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x20 bytes from the device
 02 20 01 1C 21 03 40 B2 83 A6 00 00 32 15 00 0A   . ..!.@²ƒ¦..2...
 01 00 00 00 63 09 00 03 00 01 01 00 01 00 01 00   ....c...........

000032: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.1305790 +0.0109763 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x4 bytes to the device
 04 20 01 00                                       . ..

000034: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1355958 +0.0030355. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 F0 01 3A B3 02 10 00 01 00 00 00 00 00 00 00   .ð.:³...........
 00 00 00 00 33 01 C6 00 16 00 1B 00 1C 00 23 00   ....3.Æ.......#.
 29 00 95 00 00 00 00 00 00 00 00 00 01 01 00 00   ).•.............
 00 00 06 01 02 03 04 06 07 05 01 04 05 06 0A 03   ................

000035: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.1356083 +0.0000125 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 04 20 3A 00 00 00 F9 00            . .... :...ù.

000038: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1395963 +0.0030347. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 BA 00 3A 20 00 4D 69 63 72 6F 73 6F 66   . .º.: .Microsof
 74 2E 58 62 6F 78 2E 49 6E 70 75 74 2E 41 72 63   t.Xbox.Input.Arc
 61 64 65 53 74 69 63 6B 1E 00 57 69 6E 64 6F 77   adeStick..Window
 73 2E 58 62 6F 78 2E 49 6E 70 75 74 2E 41 72 63   s.Xbox.Input.Arc

000040: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1435964 +0.0039933. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 BA 00 74 61 64 65 53 74 69 63 6B 27 00   . .º.tadeStick'.
 57 69 6E 64 6F 77 73 2E 58 62 6F 78 2E 49 6E 70   Windows.Xbox.Inp
 75 74 2E 4E 61 76 69 67 61 74 69 6F 6E 43 6F 6E   ut.NavigationCon
 74 72 6F 6C 6C 65 72 03 CC 54 20 33 4B A3 D5 41   troller.ÌT 3K£ÕA

000042: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1475979 +0.0039959. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A AE 01 A3 4A A6 A6 71 1E C4 B3 E7 1F   . .:®.£J¦¦q.Ä³ç.
 F3 B8 86 73 E9 40 A9 F8 2F 21 26 3A CF B7 56 FF   ó¸†sé@©ø/!&:Ï·Vÿ
 76 97 FD 9B 81 45 AD 45 B6 45 BB A5 26 D6 04 17   v—ý›E­E¶E»¥&Ö..
 00 20 1E 00 01 00 10 00 00 00 00 00 00 00 00 00   . ..............

000044: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1515954 +0.0039883. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A E8 01 00 00 00 00 00 00 17 00 0A 05   . .:è...........
 00 01 00 08 00 00 00 00 00 00 00 00 00 00 00 00   ................
 00 00 00 17 00 21 17 00 01 00 10 00 00 00 00 00   .....!..........
 00 00 00 00 00 00 00 00 00 00 17 00 22 18 00 01   ............"...

000046: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1555705 +0.0039703. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x17 bytes from the device
 04 B0 01 11 A2 02 00 10 00 00 00 00 00 00 00 00   .°..¢...........
 00 00 00 00 00 00 00                              .......

000047: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.1555796 +0.0000091 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 04 20 33 01 00 00 00 00            . .... 3.....

000050: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1595565 +0.0029951. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 04 A0 01 00 B3 02                                 . ..³.

000052: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.1705861 +0.0110185 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x13 bytes to the device
 05 20 02 0F 06 00 00 00 00 00 00 55 53 00 00 00   . .........US...
 00 00 00                                          ...

000054: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.1725760 +0.0000065 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x5 bytes to the device
 05 20 03 01 00                                    . ...

000055: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1755615 +0.0029855. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 02 09 02 05 20 0F 00 00 00 0F 00            . .... ......

000058: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.1765596 +0.0000023 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x7 bytes to the device
 0A 20 04 03 00 01 14                              . .....

000059: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.1795582 +0.0029986. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x8 bytes from the device
 03 20 01 04 80 00 00 00                           . ..€...

000062: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.2185753 +0.0380183 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x3e bytes to the device
 06 30 01 3A 00 41 00 01 00 2C 01 01 00 28 73 81   .0.:.A...,...(s
 A4 E7 56 7F 58 1B 02 97 61 3F E6 65 21 F3 9A C5   ¤çVX..—a?æe!óšÅ
 F5 65 59 45 46 56 8E EE DD 7B 55 B1 58 FF 00 00   õeYEFVŽîÝ{U±Xÿ..
 00 00 45 7B AF E9 00 00 00 00 00 00 00 00         ..E{¯é........

000064: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.2235653 +0.0029547. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 01 09 00 06 30 3A 00 00 00 3A 00            . ....0:...:.

000066: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.2475616 +0.0239818. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xa bytes from the device
 06 30 01 06 00 C1 00 01 00 00                     .0...Á....

000067: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.2475832 +0.0000216 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 06 20 06 00 00 00 00 00            . .... ......

000070: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.2515611 +0.0029862. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 01 00 06 00                                 . ....

000072: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.2665722 +0.0150018 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x12 bytes to the device
 06 30 02 0E 00 42 00 02 00 54 00 00 00 00 00 00   .0...B...T......
 00 00                                             ..

000074: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.2715664 +0.0029964. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 02 09 00 06 30 0E 00 00 00 0E 00            . ....0......

000076: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.3156094 +0.0440327. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 F0 02 BA 00 5A 00 C2 00 02 00 54 02 01 00 50   .ð.º.Z.Â...T...P
 BF BA 4F 45 2B 74 49 88 23 26 5D 91 1F 93 56 24   ¿ºOE+tIˆ#&]‘.“V$
 63 A5 04 BF 60 01 6F 58 9F 04 F3 26 ED 4E 47 63   c¥.¿`.oXŸ.ó&íNGc
 C7 2F 6C F2 00 00 03 E9 00 41 02 05 A0 9D 00 17   Ç/lò...é.A.. ..

000077: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.3156270 +0.0000176 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 02 09 00 06 20 3A 00 00 00 20 00            . .... :... .

000080: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.3195996 +0.0030256. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x26 bytes from the device
 06 B0 02 A0 00 3A 00 3D 00 35 81 A3 40 90 03 00   .°. .:.=.5£@..
 01 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00   .€..............
 00 00 00 00 00 00                                 ......

000081: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.3196105 +0.0000109 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 02 09 00 06 20 5A 00 00 00 00 00            . .... Z.....

000084: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.3235698 +0.0029938. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 02 00 5A 00                                 . ..Z.

000086: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.3465703 +0.0229914 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x12 bytes to the device
 06 30 03 0E 00 42 00 03 04 04 00 00 00 00 00 00   .0...B..........
 00 00                                             ..

000088: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.3515781 +0.0030002. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 03 09 00 06 30 0E 00 00 00 0E 00            . ....0......

000090: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.4596127 +0.1080242. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 F0 03 3A B9 06 01 C2 00 03 03 33 03 01 03 2F   .ð.:¹..Â...3.../
 30 82 03 2B 30 82 02 13 A0 03 02 01 02 02 04 23   0‚.+0‚.. ......#
 7E 35 55 30 0D 06 09 2A 86 48 86 F7 0D 01 01 0B   ~5U0...*†H†÷....
 05 00 30 76 31 0B 30 09 06 03 55 04 06 13 02 44   ..0v1.0...U....D

000091: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.4596384 +0.0000257 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 3A 00 00 00 FF 02            . .... :...ÿ.

000094: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.4636083 +0.0030342. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 BA 00 3A 45 31 0F 30 0D 06 03 55 04 08   . .º.:E1.0...U..
 13 06 53 61 78 6F 6E 79 31 16 30 14 06 03 55 04   ..Saxony1.0...U.
 0A 13 0D 53 75 62 63 6C 61 73 73 20 30 30 30 31   ...Subclass 0001
 31 11 30 0F 06 03 55 04 0B 13 08 43 6C 61 73 73   1.0...U....Class

000096: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.4676149 +0.0039978. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 BA 00 74 20 30 33 31 2B 30 29 06 03 55   . .º.t 031+0)..U
 04 03 13 22 58 62 6F 78 20 41 63 63 65 73 73 6F   ..."Xbox Accesso
 72 69 65 73 20 43 6C 61 73 73 20 50 72 6F 64 20   ries Class Prod 
 43 41 20 30 30 31 30 1E 17 0D 31 35 31 30 30 31   CA 0010...151001

000098: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.4716532 +0.0040269. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A AE 01 31 39 31 35 31 38 5A 17 0D 34   . .:®.191518Z..4
 33 30 32 32 32 32 33 35 39 35 39 5A 30 00 30 82   30222235959Z0.0‚
 01 22 30 0D 06 09 2A 86 48 86 F7 0D 01 01 01 05   ."0...*†H†÷.....
 00 03 82 01 0F 00 30 82 01 0A 02 82 01 01 00 B2   ..‚...0‚...‚...²

000100: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.4756674 +0.0040043. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x3b bytes from the device
 06 B0 03 35 E8 01 5F 75 E3 D8 C9 CE 44 14 E3 4B   .°.5è._uãØÉÎD.ãK
 FC 69 F8 AA 96 8E 2E 1C E8 29 0A BF 36 0B C4 EC   üiøª–Ž..è).¿6.Äì
 41 DD B9 BA 52 1E E7 81 F5 CF 8F 60 FA 96 9D AE   AÝ¹ºR.çõÏ`ú–®
 DD 54 E8 14 F5 6D 59 3D 05 89 DB                  ÝTè.õmY=.‰Û

000101: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.4756792 +0.0000118 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 1D 01 00 00 1C 02            . .... ......

000104: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5036104 +0.0270366. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A 9D 02 E3 68 98 2A E5 DD 13 64 B4 A8   . .:.ãh˜*åÝ.d´¨
 80 61 7E 6F 1D 9C DB 5D D3 C1 42 60 84 6E EE 29   €a~o.œÛ]ÓÁB`„nî)
 3A AF 98 BC 23 23 65 A4 34 6A 19 84 C7 59 9F 82   :¯˜¼##e¤4j.„ÇYŸ‚
 B4 DE F6 D9 CB 99 6B D7 7D C5 10 44 61 EF A3 00   ´ÞöÙË™k×}Å.Daï£.

000106: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5076077 +0.0039845. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A D7 02 F6 AA ED 2D 88 56 84 00 66 73   . .:×.öªí-ˆV„.fs
 63 14 77 15 5F 6B D6 24 D2 4B 3D E1 A9 95 67 E1   c.w._kÖ$ÒK=á©•gá
 11 86 53 83 33 51 E2 C9 0B 8F 8E 8D BB 25 01 EA   .†Sƒ3QâÉ.Ž»%.ê
 B1 50 DF 5D EC 9A B3 DE 38 43 AF 51 31 40 01 6F   ±Pß]ìš³Þ8C¯Q1@.o

000108: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5119775 +0.0043615. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A 91 03 5D E2 06 02 5D DC A6 B2 AF 04   . .:‘.]â..]Ü¦²¯.
 25 D8 7E 9F BD C9 14 81 CD 80 99 42 4E EF D6 B6   %Ø~Ÿ½É.Í€™BNïÖ¶
 C6 89 7D 17 0E EB EC 49 3C 17 3C 4C ED 68 0C 87   Æ‰}..ëìI<.<Líh.‡
 1D DE C2 6F 9B 4A 99 7B DF 62 F6 63 A4 AB 6F 22   .ÞÂo›J™{ßböc¤«o"

000110: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5156619 +0.0036744. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A CB 03 21 1E CC B8 CB D6 75 5F 08 1D   . .:Ë.!.Ì¸ËÖu_..
 84 28 98 F2 11 6B 37 98 81 7F E2 2E B6 5C A8 B4   „(˜ò.k7˜â.¶\¨´
 5F 5D 02 03 01 00 01 A3 37 30 35 30 0E 06 03 55   _].....£7050...U
 1D 0F 01 01 FF 04 04 03 02 00 B0 30 0C 06 03 55   ....ÿ.....°0...U

000112: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5196040 +0.0039322. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x3a bytes from the device
 06 B0 03 34 85 04 1D 13 01 01 FF 04 02 30 00 30   .°.4….....ÿ..0.0
 15 06 03 55 1D 25 04 0E 30 0C 06 0A 2B 06 01 04   ...U.%..0...+...
 01 82 37 78 03 01 30 0D 06 09 2A 86 48 86 F7 0D   .‚7x..0...*†H†÷.
 01 01 0B 05 00 03 82 01 01 00                     ......‚...

000113: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.5196159 +0.0000119 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 39 02 00 00 00 01            . .... 9.....

000116: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5436120 +0.0230380. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A B9 04 27 64 5B C9 6E AA 89 A6 8D A2   . .:¹.'d[Énª‰¦¢
 CB 05 88 0C DD 0F 0F D4 2C 3D 4B 1E CE 9C 32 E8   Ë.ˆ.Ý..Ô,=K.Îœ2è
 9E 8C EA 34 D8 06 8D E4 40 67 3C E1 5E DD 16 C7   žŒê4Ø.ä@g<á^Ý.Ç
 E0 9D EF 38 B0 02 2B FC E8 6A 10 D6 38 B7 4D EC   àï8°.+üèj.Ö8·Mì

000118: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5476125 +0.0039873. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A F3 04 AD DA D0 7A A1 FB 8A DD 9B EA   . .:ó.­ÚÐz¡ûŠÝ›ê
 48 8B 50 11 B9 4C 86 E6 51 54 40 41 DF 8E F8 C9   H‹P.¹L†æQT@AßŽøÉ
 D7 D5 FF 8B 6A 65 20 97 28 E8 22 E5 EE 63 08 F2   ×Õÿ‹je —(è"åîc.ò
 13 BF 99 F3 C9 80 1B 20 72 CD 8E E6 B5 40 B5 DA   .¿™óÉ€. rÍŽæµ@µÚ

000120: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5516093 +0.0039862. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A AD 05 06 BC EE C4 43 65 6C 50 26 AC   . .:­..¼îÄCelP&¬
 AA E4 55 7C 05 40 49 C9 BB 0A 6D 04 C5 D4 E5 9D   ªäU|.@IÉ».m.ÅÔå
 06 41 AC E7 4C 23 6C 0F 0D 4B EA 99 3F D4 AC A6   .A¬çL#l..Kê™?Ô¬¦
 9F 16 80 EF B5 F9 07 36 C3 EE E2 C5 20 E0 1A 4F   Ÿ.€ïµù.6ÃîâÅ à.O

000122: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5556088 +0.0039893. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A E7 05 4D 78 61 50 53 B0 D2 DA C3 F0   . .:ç.MxaPS°ÒÚÃð
 91 0B 03 6D 91 21 A8 A7 B2 C0 EC C2 BF 2F 45 96   ‘..m‘!¨§²ÀìÂ¿/E–
 47 C4 EF EE 51 F8 07 A8 69 F4 0D EB EE 2F 9C BE   GÄïîQø.¨iô.ëî/œ¾
 B1 64 50 98 A0 39 EA 63 9D 00 C1 98 30 17 A7 80   ±dP˜ 9êc.Á˜0.§€

000124: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5595877 +0.0039691. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 06 B0 03 18 A1 06 8F F4 9D D4 13 86 AC 74 CE 43   .°..¡.ôÔ.†¬tÎC
 37 6A 08 5F C5 16 1E 7F 54 55 45 EB 84 69         7j._Å..TUEë„i

000125: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.5596030 +0.0000153 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 39 03 00 00 00 00            . .... 9.....

000128: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5635695 +0.0029948. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 03 00 B9 06                                 . ..¹.

000130: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.5866050 +0.0230256 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 F0 04 3A 92 02 00 41 00 05 01 04 05 01 01 00   .ð.:’..A........
 24 7D 6A 75 C0 4D 40 20 E4 76 32 86 0C 07 32 6C   $}juÀM@ äv2†..2l
 D8 41 14 03 B2 3A B7 4A ED F0 F3 C8 DF 9A 39 E6   ØA..²:·JíðóÈßš9æ
 A6 AD B0 BE 25 D6 FA 3D 31 13 30 03 0B 65 49 92   ¦­°¾%Öú=1.0..eI’

000132: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.5915766 +0.0029642. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 04 09 00 06 F0 3A 00 00 00 E3 00            . ....ð:...ã.

000134: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.5946157 +0.0030286 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 A0 04 BA 00 3A CA 2A 2F 4F E3 7C A1 3F B7 C7   . .º.:Ê*/Oã|¡?·Ç
 90 F2 C8 3E 2D 13 86 8F 93 22 B9 A4 0C 18 CA 44   òÈ>-.†“"¹¤..ÊD
 28 7B 53 74 86 97 57 D9 A2 E9 36 64 3F 32 A4 DA   ({St†—WÙ¢é6d?2¤Ú
 BC 62 A2 94 91 02 61 20 6B 73 26 54 FC 84 98 F0   ¼b¢”‘.a ks&Tü„˜ð

000136: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.5966156 +0.0000046 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 A0 04 BA 00 74 10 5A 68 5D E0 EB 84 0D EB 89   . .º.t.Zh]àë„.ë‰
 62 BF CB A6 AC 41 0A BD 94 A4 80 06 7F 7A 35 5D   b¿Ë¦¬A.½”¤€.z5]
 03 67 4E 61 D5 6B D8 2D 4D BF 48 CF 5B 84 91 0B   .gNaÕkØ-M¿HÏ[„‘.
 DC FB 0E 76 BF A3 1A D6 09 FC 4F 85 42 2C 7B AD   Üû.v¿£.Ö.üO…B,{­

000138: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.6006163 +0.0000056 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 A0 04 3A AE 01 1E B9 4A 25 5B C0 5C C5 40 23   . .:®..¹J%[À\Å@#
 0E 15 81 F6 BA 55 08 C7 75 75 42 D2 28 2C CA B4   ..öºU.ÇuuBÒ(,Ê´
 E6 67 82 AA 23 2A 8D 5E 26 93 04 D2 E4 28 8A A3   æg‚ª#*^&“.Òä(Š£
 4F 53 9F 52 72 DC AD 5F B5 C9 A2 39 3D 8B 2F F8   OSŸRrÜ­_µÉ¢9=‹/ø

000140: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.6046155 +0.0000055 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x30 bytes to the device
 06 B0 04 2A E8 01 99 E2 9E CC 28 FD DC 53 A4 D3   .°.*è.™âžÌ(ýÜS¤Ó
 DA D8 4C C4 9D 7D 8D 17 55 E2 49 4D 51 57 3C D0   ÚØLÄ}.UâIMQW<Ð
 45 92 38 94 00 D5 D7 C6 00 00 00 00 00 00 00 00   E’8”.Õ×Æ........

000142: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:11.6116536 +0.0025583. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 04 09 00 06 F0 12 01 00 00 0B 00            . ....ð......

000144: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:11.6186354 +0.0069592 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x6 bytes to the device
 06 A0 04 00 92 02                                 . ..’.

000146: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.2835677 +0.6629935. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xa bytes from the device
 06 30 04 06 00 C1 00 01 00 00                     .0...Á....

000147: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.2835874 +0.0000197 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 04 09 00 06 20 06 00 00 00 00 00            . .... ......

000150: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.2875702 +0.0029955. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 04 00 06 00                                 . ....

000152: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.3066670 +0.0190881 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x36 bytes to the device
 06 30 05 32 00 41 00 07 00 24 07 01 00 20 E8 E8   .0.2.A...$... èè
 C3 C9 6D 0F 59 71 05 AA 93 66 63 FB A1 EE 78 E7   ÃÉm.Yq.ª“fcû¡îxç
 E5 22 1C 3B 3A 7B 15 17 A0 F1 6E 73 FB 8A 00 00   å".;:{.. ñnsûŠ..
 00 00 00 00 00 00                                 ......

000154: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.3120783 +0.0034712. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 05 09 00 06 30 32 00 00 00 32 00            . ....02...2.

000156: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.4515787 +0.1394901. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xa bytes from the device
 06 30 05 06 00 C1 00 01 00 00                     .0...Á....

000157: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.4515993 +0.0000206 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 05 09 00 06 20 06 00 00 00 00 00            . .... ......

000160: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.4555727 +0.0029968. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 05 00 06 00                                 . ....

000162: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.4746877 +0.0191048 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x12 bytes to the device
 06 30 06 0E 00 42 00 08 00 44 00 00 00 00 00 00   .0...B...D......
 00 00                                             ..

000164: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.4795745 +0.0025408. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 06 09 00 06 30 0E 00 00 00 0E 00            . ....0......

000166: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.6396126 +0.1600297. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 F0 06 BA 00 4A 00 C2 00 08 00 44 08 01 00 40   .ð.º.J.Â...D...@
 AE 52 42 A0 5E 83 05 B9 E9 19 81 07 27 50 09 D8   ®RB ^ƒ.¹é..'P.Ø
 94 67 EB 45 17 F0 38 24 C5 0A 63 F7 D0 9B 69 05   ”gëE.ð8$Å.c÷Ð›i.
 76 E3 1E CD A2 14 8F 74 2E 23 BE A3 EA F7 09 BF   vã.Í¢.t.#¾£ê÷.¿

000167: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.6396352 +0.0000226 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 06 09 00 06 20 3A 00 00 00 10 00            . .... :.....

000170: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.6435810 +0.0030055. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x16 bytes from the device
 06 B0 06 90 00 3A 39 7F 5A 78 78 22 A8 29 99 D8   .°..:9Zxx"¨)™Ø
 07 7C A6 9C 84 02                                 .|¦œ„.

000171: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.6435930 +0.0000120 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 06 09 00 06 20 4A 00 00 00 00 00            . .... J.....

000174: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:12.6475713 +0.0030048. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 06 00 4A 00                                 . ..J.

000176: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:12.6502141 +0.0026331 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x6 bytes to the device
 06 20 07 02 01 00                                 . ....

000178: Bulk or Interrupt Transfer (DOWN), 2020-07-20 11:23:24.4613402 +11.8087672 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x7ddd3c80 (Endpoint Address: 0x1)
Send 0x5 bytes to the device
 05 20 05 01 05                                    . ...

000180: Bulk or Interrupt Transfer (UP), 2020-07-20 11:23:24.4675713 +0.0029890. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x7d681c90 (Endpoint Address: 0x81)
Get 0x8 bytes from the device
 03 20 02 04 80 00 00 00                           . ..€...
```


## Handshake Data
* `2` bytes
* Noted working with WinUSB
* Handshake process appears to be:

  * Send `init` packet
  * Read from `0x81` end-points
  * Receive `30` byte button data packet
  * Read from `0x81` end-points
  * Receive `2` byte dummy data packet
  * Read from `0x81` end-points
  * Receive `30` byte button data packet
  * Read from `0x81` end-points
  * Receive `2` byte button data packet
  * Following this, heartbeat packets will be sent regularly if not buttons are pressed and the device will stay alive
  

```
01 00
```  
  
## Heartbeat Data
* `8` bytes
* Sent every 20 seconds or so, regardless of other data

```
000015: Bulk or Interrupt Transfer (UP), 2019-04-11 10:39:22.5578619 +20.0197652. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x8d11620 (Endpoint Address: 0x81)
Get 0x8 bytes from the device
 03 20 05 04 80 01 00 00                           . ..€...
```


## Init Controller Data
* `5` bytes
* Sent to device roughly every 1 to 2 seconds when no input is coming in from controller, although sometimes it can be up to a minute between sends

```
000017: Bulk or Interrupt Transfer (DOWN), 2019-04-11 10:39:41.6933866 +19.1354978 (1. Device: Razer Atrox Arcade Stick)
Pipe Handle: 0x16bce810 (Endpoint Address: 0x1)
Send 0x5 bytes to the device
 05 20 08 01 05                                    . ...
```


## Guide Button Data
* `6` byte packets

### Guide button:

#### Press:
```
000133: Bulk or Interrupt Transfer (UP), 2019-04-09 09:01:56.8257033 +2.4479648. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 07 20 01 02 01 5B                                 . ...[
```

#### Release:
```
000135: Bulk or Interrupt Transfer (UP), 2019-04-09 09:01:56.9016759 +0.0759190. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 07 20 02 02 00 5B                                 . ...[
```  
  
  
## Button Press Data
* `30` byte packets
* 2nd, 3rd and 4th bytes seem to be part of a packet sequence count
* 5th byte indicates button(s) pressed/released
  * `0x04` = Menu pressed
  * `0x08` = View pressed
  * `0x10` = A pressed
  * `0x20` = B pressed
  * `0x40` = X pressed
  * `0x80` = Y pressed
* 6th bytes indicates button(s) pressed/release and stick direction
  * `0x01` = Stick Up
  * `0x02` = Stick Down
  * `0x04` = Stick left
  * `0x08` = Stick right
  * `0x10` = RB pressed
  * `0x20` = LB pressed
* 23rd byte indicates whether buttons(pressed/release)
  * `0x01` = X pressed
  * `0x02` = Y pressed
  * `0x04` = RB pressed
  * `0x08` = LB pressed
  * `0x10` = A pressed
  * `0x20` = B pressed
  * `0x40` = RT pressed
  * `0x80` = LT pressed
* LT and RT presses don't seem to use the 5th and 6th bytes, only appear on the 23rd byte
  
### X button:

#### Press:
```
000031: Bulk or Interrupt Transfer (UP), 2019-04-08 20:56:36.7991292 +15.1359694. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 01 1A 40 00 00 00 00 00 00 00 00 00 00 00    ...@...........
 00 00 00 00 00 00 01 00 00 00 00 00 00 00         ..............
```
 
#### Release:
```
000033: Bulk or Interrupt Transfer (UP), 2019-04-08 20:56:36.8831218 +0.0839366. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 02 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### Y button:

#### Press:
```
000901: Bulk or Interrupt Transfer (UP), 2019-04-08 22:24:43.3309925 +1.3879435. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 03 1A 80 00 00 00 00 00 00 00 00 00 00 00    ...€...........
 00 00 00 00 00 00 02 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000903: Bulk or Interrupt Transfer (UP), 2019-04-08 22:24:43.4149620 +0.0839161. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 04 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### A button:

#### Press:
```
000921: Bulk or Interrupt Transfer (UP), 2019-04-08 22:26:10.7143943 +6.2080192. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 05 1A 10 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 10 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000923: Bulk or Interrupt Transfer (UP), 2019-04-08 22:26:10.7904048 +0.0759565. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 06 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### B button:

#### Press:
```
000937: Bulk or Interrupt Transfer (UP), 2019-04-08 22:27:10.1740063 +8.2760100. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 07 1A 20 00 00 00 00 00 00 00 00 00 00 00    ... ...........
 00 00 00 00 00 00 20 00 00 00 00 00 00 00         ...... .......
```

#### Release:
```
000939: Bulk or Interrupt Transfer (UP), 2019-04-08 22:27:10.2459758 +0.0719134. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x17d4e0e0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 08 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### RB button:

#### Press:
```
000013: Bulk or Interrupt Transfer (UP), 2019-04-09 08:55:18.1444254 +5.4679828. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 01 1A 00 10 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 04 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000015: Bulk or Interrupt Transfer (UP), 2019-04-09 08:55:18.2284468 +0.0839711. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 02 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### LB button:

#### Press:
```
000035: Bulk or Interrupt Transfer (UP), 2019-04-09 08:56:01.8841309 +3.3119139. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 05 1A 00 20 00 00 00 00 00 00 00 00 00 00    .... ..........
 00 00 00 00 00 00 08 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000037: Bulk or Interrupt Transfer (UP), 2019-04-09 08:56:01.9561214 +0.0719416. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 06 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### RT button:

#### Press:
```
000053: Bulk or Interrupt Transfer (UP), 2019-04-09 08:56:28.1879628 +5.2079978. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 07 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 40 00 00 00 00 00 00 00         ......@.......
```

#### Release:
```
000055: Bulk or Interrupt Transfer (UP), 2019-04-09 08:56:28.2519439 +0.0639403. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 08 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### LT button:

#### Press:
```
000057: Bulk or Interrupt Transfer (UP), 2019-04-09 08:56:29.2079421 +0.9559596. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 09 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 80 00 00 00 00 00 00 00         ......€.......
```

#### Release:
```
000059: Bulk or Interrupt Transfer (UP), 2019-04-09 08:56:29.2799605 +0.0719775. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0A 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### Menu button:

#### Press:
```
000125: Bulk or Interrupt Transfer (UP), 2019-04-09 09:01:53.2697641 +3.6839143. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0B 1A 04 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000127: Bulk or Interrupt Transfer (UP), 2019-04-09 09:01:53.3857563 +0.1159332. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0C 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### View button:

#### Press:
```
000129: Bulk or Interrupt Transfer (UP), 2019-04-09 09:01:54.2817150 +0.8959070. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0D 1A 08 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000131: Bulk or Interrupt Transfer (UP), 2019-04-09 09:01:54.3777115 +0.0959505. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0E 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### Stick right:

#### Press:
```
000181: Bulk or Interrupt Transfer (UP), 2019-04-09 09:04:56.3924713 +5.7919788. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0F 1A 00 08 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000183: Bulk or Interrupt Transfer (UP), 2019-04-09 09:04:56.4844736 +0.0919538. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 10 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### Stick down:

#### Press:
```
000195: Bulk or Interrupt Transfer (UP), 2019-04-09 09:05:34.7322278 +6.2039273. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 11 1A 00 02 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000197: Bulk or Interrupt Transfer (UP), 2019-04-09 09:05:34.8122100 +0.0799501. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 12 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### Stick left:

#### Press:
```
000209: Bulk or Interrupt Transfer (UP), 2019-04-09 09:05:57.7720654 +2.9399506. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 13 1A 00 04 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000211: Bulk or Interrupt Transfer (UP), 2019-04-09 09:05:57.8760724 +0.1038639. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 14 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


### Stick up:

#### Press:
```
000227: Bulk or Interrupt Transfer (UP), 2019-04-09 09:06:22.3479050 +3.1399673. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 17 1A 00 01 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

#### Release:
```
000229: Bulk or Interrupt Transfer (UP), 2019-04-09 09:06:22.5118943 +0.1639412. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Pipe Handle: 0x18cbacb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 18 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```




