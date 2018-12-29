# CMPE443 Car Project
## R3S3RV3D
<p align="center">
    <img src="https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/R3S3RV3D.png" width="50%" height="auto" align="center">
</p>

### We were 1st place in the race.

#### Team Members
<p align="left">
    <img src="https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/team.jpg" width="50%" height="auto" align="center">
</p>

- [Enes ÇAKIR](https://www.github.com/EnesCakir)
- [Dilruba Reyyan Kılıç](https://www.github.com/abcdrk)
- [Bekir Burak Aslan](https://www.github.com/bekir16)
- [Yusuf Kalaycı](https://www.github.com/byklyci)

## Links
- [Interim Description](https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/Interim_Description.pdf) (given)
- [Interim Report](https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/Interim_Report.pdf)
- You can access our *Interim* project at [first-interim](https://github.com/EnesCakir/cmpe443-car-project/tree/first-interim) branch.
- [Final Description](https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/Final_Description.pdf) (given)
- [Final Report](https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/Final_Report.pdf)

## Description
<p align="center">
    <img src="https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/car.jpg" width="50%" height="auto" align="center">
</p>
<p align="center">
    <img src="https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/race.jpg" width="50%" height="auto" align="center">
</p>

We used 4-Wheel Robot Smart Car Chassis via LPC4088 Board and with various sensors and other components.

You can set parameters via `Parameters.c` file.

### WiFi
We could not develop WiFi successfully.
We did not use interrupt at LDR sensors.
While transmitting data via WiFi, all the other parts of the car is blocked. 
So polled LDR sensors and Joystick do not work.

### Circuit Schema
<p align="center">
    <img src="https://github.com/EnesCakir/cmpe443-car-project/raw/master/assets/circuit_schema.jpg" width="50%" height="auto" align="center">
</p>

### Pins
| LPC4088 pin | Connection | Function | Purpose |
|:-----------:|:----------:|:--------:|:-------:|
|P1.24|P5|GPIO|IN2 - Left Motors|
|P1.23|P6|GPIO|IN1 - Left Motors|
|P1.20|P7|PWM1[2]|LED Blinking|
|P0.21|P8|GPIO|FR LED|
|P0.0|P9|UART3 TX|WiFi RX|
|P0.1|P10|UART3 RX|WiFi TX|
|P0.9|P11|T2_MAT_3|Ultrasonic Trigger|
|P0.8|P12|GPIO|WiFi CH_PD|
|P0.7|P13|GPIO|WiFi RST|
|P0.23|P15|ADC0[0]|Trim Pot|
|P0.24|P16|T3_CAP_1|Ultrasonic Echo|
|P0.25|P17|ADC0[2]|LDR Right|
|P0.26|P18|ADC0[3]|LDR Left|
|P1.30|P19|GPIO|BL LED|
|P1.31|P20|GPIO|BR LED|
|P0.29|P23|EINT0|Push Button|
|P1.11|P25|PWM0[6]|ENB - Right Motors|
|P1.7|P26|PWM0[5]|ENA - Left Motors|
|P1.6|P27|GPIO|FL LED|
|P0.5|P33|GPIO|IN3 - Right Motors|
|P0.4|P34|GPIO|IN4 - Right Motors|

### License
CmpE443 R3S3RV3D Car Project is an open-sourced software licensed under the [MIT license](https://opensource.org/licenses/MIT).