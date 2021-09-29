# EmbeddedSabryHub
This is Sabry's embedded systems repo

<div dir="rtl">
  
#### أحمد شوقي : 
> دقات قلب المرء قائلةً له: إن الحياةَ دقائقٌ وثواني، 
فارفع لنفسك بعد موتك ذِكرها، الذِكرُ للإنسان .. عُمرٌ ثاني !

</div>


### The Static Design Architecture 
![Presentation1](https://user-images.githubusercontent.com/82292548/134666422-4ddb3824-1ba4-408d-adae-df4132e63b75.png)

#### The Microcontroller Abstraction Layer
This layer has two main parts one for memory mapping to map the registers and the vector table into macros <br>
![pptCFD1 pptm  Autosaved](https://user-images.githubusercontent.com/82292548/134762612-b09d78d5-d38d-4986-8f3f-f8ee6c7ebf48.jpg)

The higher one is to make drivers for The main Peripherals of the MCU
- [X] :tada: GPIO
- [X] :tada: External Interrupts
- [X] :tada: Timers
- [X] :tada: ADC
- [X] :tada: EEPROM
- [X] :tada: UART
- [X] :tada: SPI
- [ ]  I2C

#### The Available MCAL now in the repo 
- [X] :tada: AVR
- [ ] ARM

#### The Hardware Abstraction Layer  
This layer for exteranl hardware componenets that will be connected with the microcontroller Like LCDs and Buttons ..etc
<br>
<br>
- [X] :tada: LCD 
- [X] :tada: Button
- [X] :tada: LM35
- [X] :tada: Keypad
- [ ] Seven Segments
- [ ] Graphical LCD
- [ ] IR
- [ ] Servo Motor
- [ ] Bluetooth
- [ ] Ultrasonic

#### The Services Layer 
This Layer used to simplify the use of the main peripherals like Generating PWM and Serial Communications


#### The Application Layer

The Layer where the application is build 
