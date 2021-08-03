# stewie-pinball
Stewie mini pinball machine as a WiFi connected stand-alone desktop toy. 

https://sternpinball.com/game/family-guy/

https://youtu.be/Mf2ijYRtEzU

https://youtu.be/dwQbJAziybQ 

https://youtu.be/de2w1HFm3PM

<table><tr>
<td><img src="docs/pxl_20201015_185411723.jpg"></td>
<td rowspan="2"><img src="docs/PXL_20210104_172839154.jpg"></td>
</tr>
<tr><td><img src="docs/PXL_20210104_172726868.jpg"></td></tr>
</table>

## Hardware
* Raspberry [Pi Zero W](https://www.raspberrypi.org/products/raspberry-pi-zero-w/)
* I2C MCP23017 [Adafruit GPIO Expander](https://learn.adafruit.com/gpio-expander-bonnet)
* I2C 17x7 LED matrix with PWM IS31FL3731 [PiMoroni ScrollPhatHD](https://shop.pimoroni.com/products/scroll-phat-hd)
* I2C 3W PCM DAC MAX98357 [Adafruit Stereo Speaker Bonnet](https://www.adafruit.com/product/3346)
* Solenoid and lamp MOSFETs [IRLB8721](https://cdn-shop.adafruit.com/datasheets/irlb8721pbf.pdf)
 
## Game operation
There are only 5 shots and each shot has a corresponding switch. The Peter and Brian shots share a loop so the sequence of the two opto switches triggering determines which shot is taken. Besides these switches, the only other input to game play is time. Outputs include all 22 playfield lamps and the LED display.

### Attract mode
All 22 playfield lamps are strobbed in various *attractive* sequences. 

### Start mode
When the game is first started each shot is lit in sequence. Which ever is hit selects the play mode.

### Peter mode

Regular Stewie pinball mode from Family Guy. 30 second timer to hit all 22 playfield lamps for big bonus and light show. Draining results in auto plunge only. Mode is ended at timer expiration.

### Meg mode

Shoot each family member (hit each column once). The mode ends when the ball drains.

### Lois mode

Flipper energy, inspired by King Pin. Collect every family member. Flipper power decreases with each shot. Draining results in auto plunger, mode is ended by zero flip power.

### Chris mode

Evil monkey song plays. Shoot the monkey. A whole column is randomly lit if it's hit double points are awarded. If a 5 second timeout is reached then a new column is chosen. The mode ends when the ball drains.

### Brian mode

Quick Draw, inspired by Cactus Canyon. Lights and flippers are out. Ball centers in trough. Old west song plays. A whole column is randomly lit, on the third lights on and "draw". Points are awarded if it's hit within 5 seconds. Otherwise back to start mode.




