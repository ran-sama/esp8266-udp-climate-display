# esp8266-udp-climate-display
Drive a 7-segment display with the esp8266 and just interrupts to receive data over UDP.

Talk to it with this from terminal, or let another device send a datagram:
```
echo -n "7562" >/dev/udp/10.0.0.20/8888
```

![alt text](https://raw.githubusercontent.com/ran-sama/udp_climate_display/master/display_photo.jpg)

## License
Licensed under the WTFPL license.
