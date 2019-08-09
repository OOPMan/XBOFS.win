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




