# Madcatz TE2 XBO USB Packets Referennce

## Notes

## Differences from Razer Atrox XBO Packets
* TE2 has much more involved handshake than Razer Atrox XBO

## Handshake Data
* Following packet list in sent/received in order
* DOWN indicates message to device
* UP indicates data from device

```
000007: PnP Event: Device Connected (UP), 2020-07-20 09:00:27.5666222 +5.5471521 (1. Device: FIGHTSTICK)
The USB device has just been connected to the system.
```

```
000008: PnP Event: Query Interface (DOWN), 2020-07-20 09:00:27.5666314 +0.0000092 (1. Device: FIGHTSTICK)
Interface GUID: {2AEB0243-6A6E-486B-82FC-D815F6B97006}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
000009: PnP Event: Query Interface (UP), 2020-07-20 09:00:27.5666421 +0.0000107 (1. Device: FIGHTSTICK)
Interface GUID: {2AEB0243-6A6E-486B-82FC-D815F6B97006}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
000010: PnP Event: Query Interface (DOWN), 2020-07-20 09:00:27.5666442 +0.0000021 (1. Device: FIGHTSTICK)
Interface GUID: {DC7A8E51-49B3-4A3A-9E81-625205E7D729}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
000011: PnP Event: Query Interface (UP), 2020-07-20 09:00:27.5666453 +0.0000011 (1. Device: FIGHTSTICK)
Interface GUID: {DC7A8E51-49B3-4A3A-9E81-625205E7D729}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0x00000000
Information: 0x0
```

```
000012: PnP Event: Query Interface (DOWN), 2020-07-20 09:00:27.5666808 +0.0000355 (1. Device: FIGHTSTICK)
Interface GUID: {DEEE98EA-C0A1-42C3-9738-A04606C84E93}
Interface Size: 0xc8 bytes
Interface Version: 0x603
Status: 0xc00000bb
Information: 0x0
```

```
000013: PnP Event: Query Interface (UP), 2020-07-20 09:00:27.5666851 +0.0000043 (1. Device: FIGHTSTICK)
Interface GUID: {DEEE98EA-C0A1-42C3-9738-A04606C84E93}
Interface Size: 0xc8 bytes
Interface Version: 0x603
Status: 0x00000000
Information: 0x0
```

```
000014: Get Descriptor Request (DOWN), 2020-07-20 09:00:27.5666868 +0.0000017 (1. Device: FIGHTSTICK)
Descriptor Type: Device
Descriptor Index: 0x0
Transfer Buffer Size: 0x12 bytes
```

```
000015: Control Transfer (UP), 2020-07-20 09:00:27.5674319 +0.0007451. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: Control Pipe
 12 01 00 02 FF FF FF 40 38 07 01 4A 34 00 01 02   ....ÿÿÿ@8..J4...
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
```

```
000016: Get Descriptor Request (DOWN), 2020-07-20 09:00:27.5674497 +0.0000178 (1. Device: FIGHTSTICK)
Descriptor Type: Configuration
Descriptor Index: 0x0
Transfer Buffer Size: 0x9 bytes
```

```
000017: Control Transfer (UP), 2020-07-20 09:00:27.5694499 +0.0020002. (1. Device: FIGHTSTICK) Status: 0x00000000
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
```

```
000018: Get Descriptor Request (DOWN), 2020-07-20 09:00:27.5694701 +0.0000202 (1. Device: FIGHTSTICK)
Descriptor Type: Configuration
Descriptor Index: 0x0
Transfer Buffer Size: 0x20 bytes
```

```
000019: Control Transfer (UP), 2020-07-20 09:00:27.5714285 +0.0019584. (1. Device: FIGHTSTICK) Status: 0x00000000
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
```

```
000020: Get Status Request (DOWN), 2020-07-20 09:00:27.5714484 +0.0000199 (1. Device: FIGHTSTICK)
Get status from Device. Data length 0x2 bytes
 B0 88                                             °ˆ
```

```
000021: Control Transfer (UP), 2020-07-20 09:00:27.5733602 +0.0019118. (1. Device: FIGHTSTICK) Status: 0x00000000
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
```

```
000022: PnP Event: Query Interface (DOWN), 2020-07-20 09:00:27.5733703 +0.0000101 (1. Device: FIGHTSTICK)
Interface GUID: {B1A96A13-3DE0-4574-9B01-C08FEAB318D6}
Interface Size: 0x48 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
000023: PnP Event: Query Interface (UP), 2020-07-20 09:00:27.5733736 +0.0000033 (1. Device: FIGHTSTICK)
Interface GUID: {B1A96A13-3DE0-4574-9B01-C08FEAB318D6}
Interface Size: 0x48 bytes
Interface Version: 0x1
Status: 0x00000000
Information: 0x0
```

```
000024: Select Configuration (DOWN), 2020-07-20 09:00:27.5733860 +0.0000124 (1. Device: FIGHTSTICK)
Configuration Index: 1
```

```
000025: Select Configuration (UP), 2020-07-20 09:00:27.5783636 +0.0000003. (1. Device: FIGHTSTICK) Status: 0x00000000
Configuration Index: 1
Configuration Handle: 0x14e02f40
```

```
000030: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.5833814 +0.8169823. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x20 bytes from the device
 02 20 02 1C 87 A1 95 FB F7 65 00 00 38 07 01 4A   . ..‡¡•û÷e..8..J
 01 00 00 00 66 00 34 00 00 03 01 00 01 00 01 00   ....f.4.........
```

```
000032: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.5989082 +0.0154990 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x4 bytes to the device
 04 20 01 00                                       . ..
```

```
000034: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6034007 +0.0030408. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 F0 01 3A E3 02 10 00 01 00 00 00 00 00 00 00   .ð.:ã...........
 00 00 00 00 63 01 C8 00 16 00 1B 00 1C 00 24 00   ....c.È.......$.
 2B 00 97 00 00 00 00 00 00 00 00 00 01 01 00 00   +.—.............
 00 00 07 01 02 03 04 06 07 1F 06 01 04 05 06 0A   ................
```

```
000035: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.6034108 +0.0000101 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 04 20 3A 00 00 00 29 01            . .... :...).
```

```
000038: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6154008 +0.0110356. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A AE 01 D5 41 A3 4A A6 A6 71 1E C4 B3   . .:®.ÕA£J¦¦q.Ä³
 E7 1F F3 B8 86 73 E9 40 A9 F8 2F 21 26 3A CF B7   ç.ó¸†sé@©ø/!&:Ï·
 56 FF 76 97 FD 9B 81 45 AD 45 B6 45 BB A5 26 D6   Vÿv—ý›E­E¶E»¥&Ö
 06 17 00 1D 0F 00 01 00 10 00 00 00 00 00 00 00   ................
```

```
000040: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6193988 +0.0039767. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A E8 01 00 00 00 00 00 00 00 00 17 00   . .:è...........
 1E 12 00 01 00 10 00 00 00 00 00 00 00 00 00 00   ................
 00 00 00 00 00 17 00 1F 12 00 01 00 10 00 00 00   ................
 00 00 00 00 00 00 00 00 00 00 00 00 17 00 20 1A   .............. .
```

```
000042: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6273993 +0.0079960. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A A2 02 00 01 00 10 00 00 00 00 00 00   . .:¢...........
 00 00 00 00 00 00 00 00 00 17 00 0A 03 00 01 00   ................
 08 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00   ................
 17 00 0B 28 00 01 00 08 00 00 00 00 00 00 00 00   ...(............
```

```
000044: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6313652 +0.0039521. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 04 B0 01 07 DC 02 00 00 00 00 00 00 00            .°..Ü........
```

```
000045: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.6313723 +0.0000071 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 04 20 3A 00 00 00 29 01            . .... :...).
```

```
000048: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6353988 +0.0030342. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 BA 00 3A 1F 03 20 00 4D 69 63 72 6F 73   . .º.:.. .Micros
 6F 66 74 2E 58 62 6F 78 2E 49 6E 70 75 74 2E 41   oft.Xbox.Input.A
 72 63 61 64 65 53 74 69 63 6B 1E 00 57 69 6E 64   rcadeStick..Wind
 6F 77 73 2E 58 62 6F 78 2E 49 6E 70 75 74 2E 41   ows.Xbox.Input.A
```

```
000050: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6393987 +0.0039952. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 BA 00 74 72 63 61 64 65 53 74 69 63 6B   . .º.trcadeStick
 27 00 57 69 6E 64 6F 77 73 2E 58 62 6F 78 2E 49   '.Windows.Xbox.I
 6E 70 75 74 2E 4E 61 76 69 67 61 74 69 6F 6E 43   nput.NavigationC
 6F 6E 74 72 6F 6C 6C 65 72 03 CC 54 20 33 4B A3   ontroller.ÌT 3K£
```

```
000052: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6433986 +0.0039954. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A AE 01 D5 41 A3 4A A6 A6 71 1E C4 B3   . .:®.ÕA£J¦¦q.Ä³
 E7 1F F3 B8 86 73 E9 40 A9 F8 2F 21 26 3A CF B7   ç.ó¸†sé@©ø/!&:Ï·
 56 FF 76 97 FD 9B 81 45 AD 45 B6 45 BB A5 26 D6   Vÿv—ý›E­E¶E»¥&Ö
 06 17 00 1D 0F 00 01 00 10 00 00 00 00 00 00 00   ................
```

```
000054: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6514011 +0.0079954. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A E8 01 00 00 00 00 00 00 00 00 17 00   . .:è...........
 1E 12 00 01 00 10 00 00 00 00 00 00 00 00 00 00   ................
 00 00 00 00 00 17 00 1F 12 00 01 00 10 00 00 00   ................
 00 00 00 00 00 00 00 00 00 00 00 00 17 00 20 1A   .............. .
```

```
000056: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6554002 +0.0039912. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 04 A0 01 3A A2 02 00 01 00 10 00 00 00 00 00 00   . .:¢...........
 00 00 00 00 00 00 00 00 00 17 00 0A 03 00 01 00   ................
 08 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00   ................
 17 00 0B 28 00 01 00 08 00 00 00 00 00 00 00 00   ...(............
```

```
000058: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6633653 +0.0079579. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 04 B0 01 07 DC 02 00 00 00 00 00 00 00            .°..Ü........
```

```
000059: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.6633738 +0.0000085 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 04 20 63 01 00 00 00 00            . .... c.....
```

```
000062: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6673620 +0.0029970. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 04 A0 01 00 E3 02                                 . ..ã.
```

```
000064: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.6789042 +0.0115281 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x13 bytes to the device
 05 20 02 0F 06 00 00 00 00 00 00 55 53 00 00 00   . .........US...
 00 00 00                                          ...
```

```
000066: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.6803718 +0.0000026 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x5 bytes to the device
 05 20 03 01 00                                    . ...
```
* This is the first send of the init packet

```
000068: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.6843623 +0.0000024 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x7 bytes to the device
 0A 20 04 03 00 01 14                              . .....
```

```
000069: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.6873601 +0.0029978. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x5 bytes from the device
 03 20 01 01 80                                    . ..€
```

```
000072: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.7268990 +0.0385382 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x3e bytes to the device
 06 30 01 3A 00 41 00 01 00 2C 01 01 00 28 A7 BB   .0.:.A...,...(§»
 35 BD DC FE F3 A0 97 D2 1B 7C ED 2B 6B 94 50 01   5½Üþó —Ò.|í+k”P.
 BC FE 81 9B 24 8F 4D 83 F4 75 90 2C 05 51 00 00   ¼þ›$Mƒôu,.Q..
 00 00 45 7B AF E9 00 00 00 00 00 00 00 00         ..E{¯é........
```

```
000074: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.7353675 +0.0069689. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 01 09 00 06 30 3A 00 00 00 3A 00            . ....0:...:.
```

```
000076: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.7433630 +0.0079843. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xa bytes from the device
 06 30 01 06 00 C1 00 01 00 00                     .0...Á....
```

```
000077: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.7433709 +0.0000079 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 01 09 00 06 20 06 00 00 00 00 00            . .... ......
```

```
000080: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.7473605 +0.0029957. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 01 00 06 00                                 . ....
```

```
000082: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.7669070 +0.0195405 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x12 bytes to the device
 06 30 02 0E 00 42 00 02 00 54 00 00 00 00 00 00   .0...B...T......
 00 00                                             ..
```

```
000084: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.7713681 +0.0029979. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 02 09 00 06 30 0E 00 00 00 0E 00            . ....0......
```

```
000086: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.8038279 +0.0324501. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 F0 02 3A DA 00 00 C2 00 02 00 54 02 01 00 50   .ð.:Ú..Â...T...P
 D0 98 80 BE 01 3F 53 BB D5 65 C0 96 E1 5D 7B 27   Ð˜€¾.?S»ÕeÀ–á]{'
 86 06 84 96 38 0F 10 66 64 3D C8 C5 4F B4 DE C4   †.„–8..fd=ÈÅO´ÞÄ
 71 A0 7B A2 00 00 03 E9 00 41 02 03 72 DD 00 04   q {¢...é.A..rÝ..
```

```
000087: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.8038419 +0.0000140 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 02 09 00 06 20 3A 00 00 00 20 00            . .... :... .
```

```
000090: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.8073948 +0.0030148. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x26 bytes from the device
 06 B0 02 A0 00 3A 00 1A 00 0C F5 66 95 F3 03 00   .°. .:....õf•ó..
 01 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00   .€..............
 00 00 00 00 00 00                                 ......
```

```
000091: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.8074044 +0.0000096 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 02 09 00 06 20 5A 00 00 00 00 00            . .... Z.....
```

```
000094: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.8113735 +0.0029961. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 02 00 5A 00                                 . ..Z.
```

```
000096: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.8309061 +0.0195229 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x12 bytes to the device
 06 30 03 0E 00 42 00 03 04 04 00 00 00 00 00 00   .0...B..........
 00 00                                             ..
```

```
000098: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.8360752 +0.0036910. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 03 09 00 06 30 0E 00 00 00 0E 00            . ....0......
```

```
000100: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:28.9994154 +0.1633281. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 F0 03 3A B9 06 04 C2 00 03 03 33 03 01 03 2F   .ð.:¹..Â...3.../
 30 82 03 2B 30 82 02 13 A0 03 02 01 02 02 04 25   0‚.+0‚.. ......%
 D2 88 8E 30 0D 06 09 2A 86 48 86 F7 0D 01 01 0B   ÒˆŽ0...*†H†÷....
 05 00 30 76 31 0B 30 09 06 03 55 04 06 13 02 44   ..0v1.0...U....D
```

```
000101: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:28.9994416 +0.0000262 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 3A 00 00 00 FF 02            . .... :...ÿ.
```

```
000104: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.0034130 +0.0030345. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 BA 00 3A 45 31 0F 30 0D 06 03 55 04 08   . .º.:E1.0...U..
 13 06 53 61 78 6F 6E 79 31 16 30 14 06 03 55 04   ..Saxony1.0...U.
 0A 13 0D 53 75 62 63 6C 61 73 73 20 30 30 30 31   ...Subclass 0001
 31 11 30 0F 06 03 55 04 0B 13 08 43 6C 61 73 73   1.0...U....Class
```

```
000106: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.1029490 +0.0995270 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 74 00 00 00 C5 02            . .... t...Å.
```

```
000108: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.1074124 +0.0030316. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 BA 00 74 20 30 33 31 2B 30 29 06 03 55   . .º.t 031+0)..U
 04 03 13 22 58 62 6F 78 20 41 63 63 65 73 73 6F   ..."Xbox Accesso
 72 69 65 73 20 43 6C 61 73 73 20 50 72 6F 64 20   ries Class Prod 
 43 41 20 30 30 31 30 1E 17 0D 31 33 30 37 30 32   CA 0010...130702
```

```
000110: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.2069589 +0.0995349 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 AE 00 00 00 8B 02            . .... ®...‹.
```

```
000112: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.2114123 +0.0030343. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A AE 01 30 37 30 31 32 38 5A 17 0D 34   . .:®.070128Z..4
 33 30 32 32 32 32 33 35 39 35 39 5A 30 00 30 82   30222235959Z0.0‚
 01 22 30 0D 06 09 2A 86 48 86 F7 0D 01 01 01 05   ."0...*†H†÷.....
 00 03 82 01 0F 00 30 82 01 0A 02 82 01 01 00 86   ..‚...0‚...‚...†
```

```
000114: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.3114958 +0.1000722 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 E8 00 00 00 51 02            . .... è...Q.
```

```
000116: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.3154126 +0.0030341. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x3a bytes from the device
 06 B0 03 34 E8 01 AA 86 48 5B FE A9 3F 22 A7 6A   .°.4è.ª†H[þ©?"§j
 EE 24 50 46 D7 64 87 3A E8 E0 E4 8A 8E 27 6C 6F   î$PF×d‡:èàäŠŽ'lo
 EE AD AE 3C ED B0 A0 B7 AC 42 56 8A F0 DD AB 2D   î­®<í° ·¬BVŠðÝ«-
 94 1C BA 5F A5 75 63 DC E6 45                     ”.º_¥ucÜæE
```

```
000117: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.3154283 +0.0000157 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 1C 01 00 00 1D 02            . .... ......
```

```
000120: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.3194140 +0.0030340. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A 9C 02 0B 2D AF 65 9F 0C DA 33 72 9A   . .:œ..-¯eŸ.Ú3rš
 DA 57 13 4F 7F A4 42 00 6C FA 49 07 22 0F A1 B0   ÚW.O¤B.lúI.".¡°
 61 A0 31 5D 2C 54 1C D0 28 D8 D6 DD 31 F4 81 39   a 1],T.Ð(ØÖÝ1ô9
 09 E8 CF 95 68 60 4E 73 8D E8 B8 58 70 3B 94 B1   .èÏ•h`Nsè¸Xp;”±
```

```
000122: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.4155041 +0.0960779 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 56 01 00 00 E3 01            . .... V...ã.
```

```
000124: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.4194151 +0.0030342. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A D6 02 C3 92 4A A4 CA 38 7E 09 67 E6   . .:Ö.Ã’J¤Ê8~.gæ
 29 CA 40 8B D6 1A 70 6A 31 E8 BB E4 AD 67 01 22   )Ê@‹Ö.pj1è»ä­g."
 21 28 A3 CE A0 D3 F8 85 CB 02 16 8D EF F3 5C 07   !(£Î Óø…Ë..ïó\.
 68 15 71 7C 75 A7 11 00 29 3C 97 1D 59 B8 0D D5   h.q|u§..)<—.Y¸.Õ
```

```
000126: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.5195106 +0.1000734 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 90 01 00 00 A9 01            . .... ...©.
```

```
000128: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.5234167 +0.0030384. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A 90 03 EE 91 25 FF BE 22 C5 1A 91 1A   . .:.î‘%ÿ¾"Å.‘.
 EA C4 CD 3B A9 0A B9 D7 39 77 AD 16 90 AE AF BF   êÄÍ;©.¹×9w­.®¯¿
 13 16 EC 87 8F D9 9E C1 8C A8 54 DF 2A 0C 14 8C   ..ì‡ÙžÁŒ¨Tß*..Œ
 B2 AD 54 EA 6C 54 13 31 22 EA A2 75 46 39 29 6D   ²­TêlT.1"ê¢uF9)m
```

```
000130: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.6235906 +0.1001323 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 CA 01 00 00 6F 01            . .... Ê...o.
```

```
000132: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.6274149 +0.0030345. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A CA 03 C9 47 AD E2 36 88 E2 B3 E3 97   . .:Ê.ÉG­â6ˆâ³ã—
 30 BA A6 BA 46 42 79 1C AB 2B D3 9C 0E 01 A0 E2   0º¦ºFBy.«+Óœ.. â
 28 2B 2D 02 03 01 00 01 A3 37 30 35 30 0E 06 03   (+-.....£7050...
 55 1D 0F 01 01 FF 04 04 03 02 00 B0 30 0C 06 03   U....ÿ.....°0...
```

```
000134: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.7276052 +0.1001771 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 04 02 00 00 35 01            . .... ....5.
```

```
000136: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.7314084 +0.0030301. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x3a bytes from the device
 06 B0 03 34 84 04 55 1D 13 01 01 FF 04 02 30 00   .°.4„.U....ÿ..0.
 30 15 06 03 55 1D 25 04 0E 30 0C 06 0A 2B 06 01   0...U.%..0...+..
 04 01 82 37 78 03 01 30 0D 06 09 2A 86 48 86 F7   ..‚7x..0...*†H†÷
 0D 01 01 0B 05 00 03 82 01 01                     .......‚..
```

```
000137: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.7314201 +0.0000117 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 38 02 00 00 01 01            . .... 8.....
```

```
000140: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.7354116 +0.0030343. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A B8 04 00 48 F1 79 55 2A 26 EA E3 96   . .:¸..HñyU*&êã–
 E4 61 4B A9 71 D4 BB 93 50 9D B9 22 79 14 C0 61   äaK©qÔ»“P¹"y.Àa
 24 FC A2 00 2A 70 32 B4 AB 18 45 1A 64 E3 1C 8F   $ü¢.*p2´«.E.dã.
 CC 8B 84 22 A4 10 3B 95 5C A9 F1 0E 28 18 18 2D   Ì‹„"¤.;•\©ñ.(..-
```

```
000142: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.8316121 +0.0961914 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 72 02 00 00 C7 00            . .... r...Ç.
```

```
000144: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.8358251 +0.0030060. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A F2 04 9F 80 F6 10 83 BC 3A 8D 06 3C   . .:ò.Ÿ€ö.ƒ¼:.<
 3D 14 D8 25 C8 D6 0A 58 5A 3D FB FE 8F C8 62 FC   =.Ø%ÈÖ.XZ=ûþÈbü
 71 F9 01 E7 9B BE 49 5C 2E 05 D0 5C 2D FD A2 CC   qù.ç›¾I\..Ð\-ý¢Ì
 B1 45 D5 DA 72 7A FE 5D A9 F7 93 A1 6D 31 58 80   ±EÕÚrzþ]©÷“¡m1X€
```

```
000146: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:29.9356153 +0.0997758 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 AC 02 00 00 8D 00            . .... ¬....
```

```
000148: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:29.9394150 +0.0030342. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A AC 05 0B EB F9 9B A6 BF A7 F4 D7 75   . .:¬..ëù›¦¿§ô×u
 46 36 7F 4B 54 78 61 16 64 C7 21 0C 95 E0 73 1B   F6KTxa.dÇ!.•às.
 44 53 B5 37 B4 5B F1 79 F8 DB 41 1E 12 DC 82 B6   DSµ7´[ñyøÛA..Ü‚¶
 3F AB 5C A2 F2 C1 BF C3 46 2D 0B A9 30 CF A7 3F   ?«\¢òÁ¿ÃF-.©0Ï§?
```

```
000150: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.0396149 +0.1001861 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 E6 02 00 00 53 00            . .... æ...S.
```

```
000152: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.0434147 +0.0030368. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 A0 03 3A E6 05 FD B3 88 58 B7 AA 23 1E F5 64   . .:æ.ý³ˆX·ª#.õd
 66 B4 A0 A7 54 0D 64 04 2B 7A D5 9D 16 CD 9E 72   f´ §T.d.+zÕ.Ížr
 F6 D5 5D 87 10 EC A1 23 30 B9 F6 9B BF 14 E3 FA   öÕ]‡.ì¡#0¹ö›¿.ãú
 CA AF 8D C9 B0 1D 58 92 50 E0 55 55 B0 9D 63 80   Ê¯É°.X’PàUU°c€
```

```
000154: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1436234 +0.1001960 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 20 03 00 00 19 00            . ....  .....
```

```
000156: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.1473795 +0.0030119. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1f bytes from the device
 06 B0 03 19 A0 06 A5 17 73 03 D6 FD D9 16 E0 66   .°.. .¥.s.ÖýÙ.àf
 85 6A B6 EC 99 6E D2 3B F2 7F B2 B2 9B B8 11      …j¶ì™nÒ;ò²²›¸.
```

```
000157: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1473908 +0.0000113 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 03 09 00 06 20 39 03 00 00 00 00            . .... 9.....
```

```
000160: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.1513601 +0.0029953. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 03 00 B9 06                                 . ..¹.
```

```
000162: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1676147 +0.0162496 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 F0 04 3A 92 02 00 41 00 05 01 04 05 01 01 00   .ð.:’..A........
 59 06 C3 B5 F4 25 6C 6C C1 C7 CA 31 8E 6F 07 F9   Y.Ãµô%llÁÇÊ1Žo.ù
 5C 03 5D AF F7 7D 28 3B 2B 0F DE 87 AC 19 79 26   \.]¯÷}(;+.Þ‡¬.y&
 91 A9 BF 76 3F 10 51 95 7A 05 88 97 08 FE F2 01   ‘©¿v?.Q•z.ˆ—.þò.
```

```
000164: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.1713653 +0.0029638. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 04 09 00 06 F0 3A 00 00 00 D8 00            . ....ð:...Ø.
```

```
000166: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1756151 +0.0042427 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 A0 04 BA 00 3A 43 21 37 96 A3 15 A7 5C 87 0A   . .º.:C!7–£.§\‡.
 E6 D8 D6 C5 9A 58 EE 84 08 E4 99 EE 55 A4 B9 50   æØÖÅšXî„.ä™îU¤¹P
 50 D2 DF EF F9 87 89 5E B0 1A B1 5F 34 E4 32 5B   PÒßïù‡‰^°.±_4ä2[
 D9 76 0E 46 53 1F 51 D4 5D 3D A2 3D F9 92 AE 60   Ùv.FS.QÔ]=¢=ù’®`
```

```
000168: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1764048 +0.0000032 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 A0 04 BA 00 74 24 F2 41 05 2B C3 59 FC CB 0F   . .º.t$òA.+ÃYüË.
 8D D2 A1 6E CB C8 F4 FC 9A 58 44 E5 9D AA C9 27   Ò¡nËÈôüšXDåªÉ'
 9A A7 02 15 6C 2E 77 AD 84 8A 29 88 29 83 E2 AA   š§..l.w­„Š)ˆ)ƒâª
 76 B7 D2 89 F9 30 37 74 1E AE A3 43 CC D2 6A 1D   v·Ò‰ù07t.®£CÌÒj.
```

```
000170: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1804013 +0.0000022 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x40 bytes to the device
 06 A0 04 3A AE 01 71 B8 7A 8F 45 19 29 3B CF 0E   . .:®.q¸zE.);Ï.
 5C F8 56 CC 75 0D 40 0F F2 E1 B8 B6 DB E9 37 42   \øVÌu.@.òá¸¶Ûé7B
 3B 65 C7 DF 4B CA CA 96 31 5B B7 C0 38 7D 4C BF   ;eÇßKÊÊ–1[·À8}L¿
 02 F5 29 EB 29 1E 90 9A 4C 1D 16 67 BE BE 2D CC   .õ)ë).šL..g¾¾-Ì
```

```
000172: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.1844016 +0.0000026 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x30 bytes to the device
 06 B0 04 2A E8 01 69 D4 61 9D 6B 62 6E 02 5F E3   .°.*è.iÔakbn._ã
 45 89 2E 71 58 F8 D9 B1 D2 86 3E 7F 8C E7 BC 25   E‰.qXøÙ±Ò†>Œç¼%
 55 20 6A 10 CF 33 17 91 00 00 00 00 00 00 00 00   U j.Ï3.‘........
```

```
000174: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.2193677 +0.0309796. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 04 09 00 06 B0 12 01 00 00 00 00            . ....°......
```

```
000176: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.2236189 +0.0042372 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x6 bytes to the device
 06 A0 04 00 92 02                                 . ..’.
```

```
000178: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.8513660 +0.6270052. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xa bytes from the device
 06 30 04 06 00 C1 00 01 00 00                     .0...Á....
```

```
000179: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.8513953 +0.0000293 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 04 09 00 06 20 06 00 00 00 00 00            . .... ......
```

```
000182: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.8553605 +0.0029952. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 04 00 06 00                                 . ....
```

```
000184: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:30.8718078 +0.0164410 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x36 bytes to the device
 06 30 05 32 00 41 00 07 00 24 07 01 00 20 1A 28   .0.2.A...$... .(
 3D CB 3E 58 8B 8B C7 10 3E 01 80 C8 30 71 89 BF   =Ë>X‹‹Ç.>.€È0q‰¿
 42 A0 7B BA 01 44 6F 61 50 E2 5F FB 8F 30 00 00   B {º.DoaPâ_û0..
 00 00 00 00 00 00                                 ......
```

```
000186: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:30.8793665 +0.0069603. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 05 09 00 06 30 32 00 00 00 32 00            . ....02...2.
```

```
000188: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:31.0033786 +0.1240004. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xa bytes from the device
 06 30 05 06 00 C1 00 01 00 00                     .0...Á....
```

```
000189: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:31.0033940 +0.0000154 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 05 09 00 06 20 06 00 00 00 00 00            . .... ......
```

```
000192: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:31.0073751 +0.0029953. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 05 00 06 00                                 . ....
```

```
000194: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:31.0238124 +0.0164268 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x12 bytes to the device
 06 30 06 0E 00 42 00 08 00 44 00 00 00 00 00 00   .0...B...D......
 00 00                                             ..
```

```
000196: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:31.0273776 +0.0029967. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0xd bytes from the device
 01 20 06 09 00 06 30 0E 00 00 00 0E 00            . ....0......
```

```
000198: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:31.1754172 +0.1480288. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x40 bytes from the device
 06 F0 06 3A CA 00 00 C2 00 08 00 44 08 01 00 40   .ð.:Ê..Â...D...@
 16 9D 98 C6 52 88 40 1E A7 D6 1C 75 41 61 AB AE   .˜ÆRˆ@.§Ö.uAa«®
 8A 25 7E 2B 35 97 54 BA 34 D8 59 97 DD 34 07 66   Š%~+5—Tº4ØY—Ý4.f
 1C BF E6 7D 34 DA BC 00 C1 C4 14 14 0E 38 09 DF   .¿æ}4Ú¼.ÁÄ...8.ß
```

```
000202: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:31.1793754 +0.0029970. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x16 bytes from the device
 06 B0 06 90 00 3A 5E BC 89 F7 19 F7 52 AE 96 1E   .°..:^¼‰÷.÷R®–.
 5D E2 ED 4A 44 FB                                 ]âíJDû
```

```
000203: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:31.1793858 +0.0000104 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0xd bytes to the device
 01 20 06 09 00 06 20 4A 00 00 00 00 00            . .... J.....
```

```
000206: Bulk or Interrupt Transfer (UP), 2020-07-20 09:00:31.1833771 +0.0029998. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 06 A0 06 00 4A 00                                 . ..J.
```

```
000208: Bulk or Interrupt Transfer (DOWN), 2020-07-20 09:00:31.1834835 +0.0000954 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x6 bytes to the device
 06 20 07 02 01 00                                 . ....
```

## Init/Ping Controller Data
* `5` bytes
* 3rd byte is a rolling value that should increase each time the packet is sent
* Lowest observed value for 3rd byte is 0x05
* Send rate varies dramatically, anywhere from 1 second to 3000 seconds!
* Sent before entering polling loop for input from controller

```
000306: Bulk or Interrupt Transfer (DOWN), 2020-07-20 10:23:02.7956487 +11.2078551 (1. Device: FIGHTSTICK)
Pipe Handle: 0x49b9cb0 (Endpoint Address: 0x1)
Send 0x5 bytes to the device
 05 20 05 01 05                                    . 5..
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

### Guide Button
#### Press
```
000488: Bulk or Interrupt Transfer (UP), 2020-07-20 10:35:44.9866968 +10.3679610. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 07 20 01 02 01 5B                                 . ...[
```
#### Release
```
000490: Bulk or Interrupt Transfer (UP), 2020-07-20 10:35:45.0826984 +0.0959767. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x6 bytes from the device
 07 20 02 02 00 5B                                 . ...[
```

### X Button
```
000362: Bulk or Interrupt Transfer (UP), 2020-07-20 10:30:26.4547700 +3.1310287. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 01 1A 40 00 00 00 00 00 00 00 00 00 00 00    ...@...........
 00 00 00 00 00 00 01 00 00 00 00 00 00 00         ..............
```

### Y Button
```
000370: Bulk or Interrupt Transfer (UP), 2020-07-20 10:31:02.2147576 +2.3390195. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 03 1A 80 00 00 00 00 00 00 00 00 00 00 00    ...€...........
 00 00 00 00 00 00 02 00 00 00 00 00 00 00         ..............
```

### A Button
```
000378: Bulk or Interrupt Transfer (UP), 2020-07-20 10:31:19.2347495 +1.9590150. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 05 1A 10 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 10 00 00 00 00 00 00 00         ..............
```

### B Button
```
000386: Bulk or Interrupt Transfer (UP), 2020-07-20 10:31:33.5227451 +2.9150152. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 07 1A 20 00 00 00 00 00 00 00 00 00 00 00    ... ...........
 00 00 00 00 00 00 20 00 00 00 00 00 00 00         ...... .......
```

### RB Button
```
000394: Bulk or Interrupt Transfer (UP), 2020-07-20 10:32:07.6827419 +2.0230163. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 09 1A 00 10 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 04 00 00 00 00 00 00 00         ..............
```

### LB Button
```
000406: Bulk or Interrupt Transfer (UP), 2020-07-20 10:32:35.6027389 +1.7350160. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0B 1A 00 20 00 00 00 00 00 00 00 00 00 00    .... ..........
 00 00 00 00 00 00 08 00 00 00 00 00 00 00         ..............
```

### RT Button
```
000414: Bulk or Interrupt Transfer (UP), 2020-07-20 10:32:47.0867369 +1.5230116. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0D 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 40 00 00 00 00 00 00 00         ......@.......
```

### LT Button
```
000422: Bulk or Interrupt Transfer (UP), 2020-07-20 10:32:55.8227350 +1.7670164. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 0F 1A 00 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 80 00 00 00 00 00 00 00         ......€.......
```

### Menu Button
```
000430: Bulk or Interrupt Transfer (UP), 2020-07-20 10:33:24.7187296 +2.6150100. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 11 1A 04 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

### View Button
```
000438: Bulk or Interrupt Transfer (UP), 2020-07-20 10:33:35.9827301 +2.2870137. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 13 1A 08 00 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

### Stick right
```
000446: Bulk or Interrupt Transfer (UP), 2020-07-20 10:34:02.9907238 +2.6510136. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 15 1A 00 08 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

### Stick down
```
000454: Bulk or Interrupt Transfer (UP), 2020-07-20 10:34:12.9427246 +2.0270099. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 17 1A 00 02 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

### Stick left
```
000462: Bulk or Interrupt Transfer (UP), 2020-07-20 10:34:28.5587285 +1.9910152. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 19 1A 00 04 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```

### Stick up
```
000470: Bulk or Interrupt Transfer (UP), 2020-07-20 10:34:40.7467230 +1.9030167. (1. Device: FIGHTSTICK) Status: 0x00000000
Pipe Handle: 0x1251ccb0 (Endpoint Address: 0x81)
Get 0x1e bytes from the device
 20 00 1B 1A 00 01 00 00 00 00 00 00 00 00 00 00    ...............
 00 00 00 00 00 00 00 00 00 00 00 00 00 00         ..............
```


