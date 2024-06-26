# V2 Upgrades:
Tested with [Arduino-cli](https://github.com/arduino/arduino-cli) 0.35.3 and 1.0.1.

## Programs changes:

(20240611): 
- fix bug: switch state detection
- random reaction case after 10 turns

## CAD: 
Origianl CAD in .step and .stl, new versions are mainly by Solidworks, FreeCAD, and OpenSCAD. 

Color printer uses Prusa XL.

## To do list...

lid:
- hide pins
- color text : 

fixed-lid: 
- snap fit for sensor
- pin hole for switch
- snap fit for servo
- text: open - close

box:
- left top hole support hinders servo body
- 4x top holes too big for 2.85mm pins
- lid joint too loose
- bottom servo base
- snap fit for chip 
- chip USB-C opening

## Purchashing parts (Poland local)
- 1X 18.02 PLN
[WEMOS D1 mini ESP8266 USB C](https://erli.pl/produkt/modul-wifi-wemos-d1-mini-esp8266-12f-arduino-iot,145459971)

- 1X 19.4 PLN
[APDS-9960 RGB, gesture and proximity sensor](https://erli.pl/produkt/czujnik-swiatla-rgb-i-wykrywacz-gestow-apds-9960,185037548)

- 2X 12.58 PLN
[Serwo SG-90 - micro - 180](https://erli.pl/produkt/serwo-modelarskie-9g-sg90-micro-180,187494326)

- 1X 4.73 PLN
[Przełącznik dźwigniowy pojedynczy (SPDT 3P)](https://erli.pl/produkt/przelacznik-dzwigniowy-pojedynczy-spdt-3p,170778687)

## PCB v2
![pcb v2 scheme](./wiring/pcb_v2_scheme.svg)
![pcb v2 raw material preparation](./wiring/pcb_v2_preparation.jpg)
![pcb v2 after soldering](./wiring/pcb_v2_soldering.jpg)
![pcb v2 prototype](./wiring/pcb_v2_prototype.jpg)
![pcb v2 wiring](./wiring/pcb_v2_wiring.jpg)

# ORIGINAL DOCUMENTATION OF [György Balássy](https://linkedin.com/in/balassy)
# Smart Useless Box with ESP8266 and Gesture Sensor

A useless box made smarter with an ESP8266 microcontroller on a Wemos D1 Mini board and an APDS-9960 proximity sensor to give more funny responses.

![Photo](./media/Useless-Box.jpg)

## YAUB (Yet Another Useless Box)?

Useless machines are not new, there are many versions available. You can create a simple one using a lever switch, however that will react always the same way. Using a programmable microcontroller you can create **funny, unexpected responses**, and by adding a proximity sensor you can surprise the user with **actions before she would even turn on the switch**!

This is a programmable useless box, so you have the option to implement **additional reactions** when you want to to further improve this funny little toy. What's more the used controller board has WiFi connectivity, so you can **connect it to other online services** (e.g. IFTTT) or **smart assistants** (Alexa, Cortana etc.).


## Smart Useless Box in Action

Click the image below to see this box in action:

[![Smart Useless Box in Action](./media/video-preview.png)](http://www.youtube.com/watch?v=x0kGetj1nt8 "Smart Useless Box in Action")


## Hardware

The following hardware components are required to build this project:

- 1 × [Wemos D1 Mini board](https://wiki.wemos.cc/products:d1:d1_mini)
- 1 × [APDS-9960 RGB, gesture and proximity sensor](https://www.sparkfun.com/products/12787) - there are multiple versions of this board, use one that follows the pinout of the SparkFun module to simplify wiring. I used [this](https://www.aliexpress.com/item/32768898229.html) cheap one from AliExpress.
- 2 × [SG90 servo motors](https://components101.com/servo-motor-basics-pinout-datasheet)
- 1 × Switch - you have to test this to ensure it flips easily and the servo is strong enough to flip it, so I bought mine in the nearest electronics hardware store.
- 1 × 1kΩ resistance
- Male pin headers:
  - 1 × 1x2 for the switch
  - 2 × 1x3 for the servo motors
  - 1 × 1x5 for the sensor
- Prototype board or PCB - to create a shield for the Wemos D1 Mini.
- Pin headers - to connect the shield to the Wemos D1 Mini.
- Dupont cables or wires with connectors.
- BluTack - to mount the wires and the controller board.
- M3 screws - to mount the lids.


## Wiring

The wiring is designed to create a custom shield for the Wemos D1 Mini ESP8266 microcontroller-based board, instead of soldering the cables directly to the board. In this way you can easily assemble the parts or even reuse them in the future.

### Schematics

![Schematic](./wiring/Useless-Box-Shield-v1-Schematic.png)

### PCB

![PCB](./wiring/Useless-Box-Shield-v1-PCB.png)

The PCB was designed with [Fritzing](https://fritzing.org), and you can [download the source file](./wiring/Useless-Box-Shield-v1.fzz) to further customize it to your needs.

You can also [download the Gerber files](./wiring/Useless-Box-Shield-v1-PCB-Gerber.zip) which you can use to order the PCB from your preferred PCB manufacturer. (Note: I've created my prototype manually then documented it in Fritzing, so I have not tested this PCB yet.)


## Software

The source code in this repo is created with [Visual Studio Code](https://code.visualstudio.com) using the [Arduino plugin from Microsoft](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino), but it should work with the [Arduino IDE](https://www.arduino.cc/en/main/software) as well.

The code in this repository is preconfigured with the pin layout shown in the wiring diagram above, but if you decide to connect the parts to different pins, you have to update the values in the `config.h` file.

After finalizing the pin configuration (or using the default one) just upload the code to the Wemos D1 Mini board.

The responses of the box are implemented in the `useless-box.ino` file, and the `run()` function is responsible for selecting and executing the reaction to a flip of the switch or to a signal from the sensor. Feel free to add new logic or remove any existing reaction you don't like in this function.


## The Box

I designed a custom box for this project which can be 3D printed or even further customized. You can download the model from [Thingiverse](https://www.thingiverse.com/thing:3856965) or [MyMiniFactory](https://www.myminifactory.com/object/3d-print-100944).

Happy Printing! :)


## About the author

This project is maintained by [György Balássy](https://linkedin.com/in/balassy).
