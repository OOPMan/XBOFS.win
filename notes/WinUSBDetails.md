# WinUSB Details

## Device
* VID: 1532
* PID_0A00
* bcdUsb 0200

## Endpoints
* Endpoint index: 0 Pipe type: Interrupt Pipe ID: 1. Polling Interval: 4
* Endpoint index: 1 Pipe type: Interrupt Pipe ID: 129. Polling Interval: 4

## Polling Interval

Device has PI of 4 for both end-points. Device is full-speed. This means interrupt polling is guaranteed to take 4ms at most.

## Packets

```
000022: PnP Event: Device Connected (UP), 2019-04-11 10:55:19.7898373 +0.3736438 (1. Device: Razer Atrox Arcade Stick)
The USB device has just been connected to the system.
```

```
000023: PnP Event: Query Interface (DOWN), 2019-04-11 10:55:19.7898439 +0.0000066 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {2AEB0243-6A6E-486B-82FC-D815F6B97006}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
000024: PnP Event: Query Interface (UP), 2019-04-11 10:55:19.7898471 +0.0000032 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {2AEB0243-6A6E-486B-82FC-D815F6B97006}
Interface Size: 0x28 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
000025: PnP Event: Query Interface (DOWN), 2019-04-11 10:55:19.7898948 +0.0000477 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {DEEE98EA-C0A1-42C3-9738-A04606C84E93}
Interface Size: 0xc8 bytes
Interface Version: 0x603
Status: 0xc00000bb
Information: 0x0
```

```
000026: PnP Event: Query Interface (UP), 2019-04-11 10:55:19.7899011 +0.0000063 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {DEEE98EA-C0A1-42C3-9738-A04606C84E93}
Interface Size: 0xc8 bytes
Interface Version: 0x603
Status: 0x00000000
Information: 0x0
```

```
000027: Get Descriptor Request (DOWN), 2019-04-11 10:55:19.7899036 +0.0000025 (1. Device: Razer Atrox Arcade Stick)
Descriptor Type: Device
Descriptor Index: 0x0
Transfer Buffer Size: 0x12 bytes
```

```
000028: Control Transfer (UP), 2019-04-11 10:55:19.7900004 +0.0000968. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
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
```

```
000029: Get Descriptor Request (DOWN), 2019-04-11 10:55:19.7900149 +0.0000145 (1. Device: Razer Atrox Arcade Stick)
Descriptor Type: Configuration
Descriptor Index: 0x0
Transfer Buffer Size: 0x9 bytes
```

```
000030: Control Transfer (UP), 2019-04-11 10:55:19.7900980 +0.0000831. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
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
000031: Get Descriptor Request (DOWN), 2019-04-11 10:55:19.7901117 +0.0000137 (1. Device: Razer Atrox Arcade Stick)
Descriptor Type: Configuration
Descriptor Index: 0x0
Transfer Buffer Size: 0x20 bytes
```

```
000032: Control Transfer (UP), 2019-04-11 10:55:19.7902364 +0.0001247. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
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
000033: Get Status Request (DOWN), 2019-04-11 10:55:19.7902503 +0.0000139 (1. Device: Razer Atrox Arcade Stick)
Get status from Device. Data length 0x2 bytes
 B6 D7                                             ¶×
``` 

```
 000034: Control Transfer (UP), 2019-04-11 10:55:19.7903319 +0.0000816. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
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
000035: PnP Event: Query Interface (DOWN), 2019-04-11 10:55:19.7903450 +0.0000131 (1. Device: Razer Atrox Arcade Stick)
Interface GUID: {B1A96A13-3DE0-4574-9B01-C08FEAB318D6}
Interface Size: 0x48 bytes
Interface Version: 0x1
Status: 0xc00000bb
Information: 0x0
```

```
00000036	2019-04-11 10:55:19.7903487	+0.0000037	UP		PnP: Query Interface
```

```
000037: Select Configuration (DOWN), 2019-04-11 10:55:19.7903664 +0.0000177 (1. Device: Razer Atrox Arcade Stick)
Configuration Index: 1
```

```
000038: Select Configuration (UP), 2019-04-11 10:55:19.7906382 +0.0000003. (1. Device: Razer Atrox Arcade Stick) Status: 0x00000000
Configuration Index: 1
Configuration Handle: 0xfdb63e30
```

```
00000020	2019-04-11 10:55:19.4156007	+4.4990191	UP		PnP: Device Surprise Removal
```

```
00000021	2019-04-11 10:55:19.4161935	+0.0005928	UP		PnP: Device Disconnected
```
