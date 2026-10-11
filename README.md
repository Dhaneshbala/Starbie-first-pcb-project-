#  Starbie- A tamagotchi and study agent
<img width="1583" height="677" alt="Screenshot 2569-10-12 at 9 14 22 AM" src="https://github.com/user-attachments/assets/3de0cebb-f330-4e4f-8fd4-dbc5d4e46b27" />


A small PCB project done with the help of the [SharKingStudios/Starbie](https://github.com) tutorial.

##  What is it?

**Starbie** is a tiny, motion-controlled digital pet. It is basically a desktop Tamagotchi with minimal gameplay buttons.It is also a mini study agent with 
features like Study timer Pomodoro 
 OLED dashboard
 Environment monitor |
Light monitor
 RGB status LED 
 Buzzer alerts
 Tilt controls
 Session tracking 


## Project Details
- **Custom Hardware:** A compact custom PCB designed for the Starbie digital pet.
- **Microcontroller:** Seeed Studio XIAO ESP32-C3.
- **Display:** A small display used to show Starbie's face, menus, and pet information.
- **Motion Control:** The board uses movement and tilting to interact with Starbie.
- **Sensors:** Sensors are used to detect movement and environmental information.
- **Interaction:** Starbie responds to tilting and shaking, with a tilt-controlled radial menu and different pet behaviours.
- **Firmware:** Arduino firmware runs on the XIAO ESP32-C3 and controls the display, sensors, and interactions.
- **PCB Design:** The project includes the KiCad schematic and PCB layout files.
- **Manufacturing:** The original project includes PCB fabrication files and a bill of materials.




### Hardware
- **Microcontroller:** Seeed Studio XIAO ESP32-C3
* **Display:** SSD1306 0.96" I2C OLED *
* **Motion/Tilt:** MPU6050 / GY-521 6-Axis IMU*
* **Climate:** DHT11 Temperature & Humidity Sensor
* **Light:** LDR (Light Dependent Resistor) + 10k pull-down resistor
* **Status Indicator:** RGB LED (Common Cathode) + inline resistors (220/ 100 / 100)
* **Audio Alerts:** Passive Buzzer driven by an NPN transistor & flyback protection diode
* **Buttons:** 2 Tactile Buttons
* **Note on 3D Renders:** The SSD1306 OLED and MPU6050 IMU are external plug-in sub-modules. They will not be visible on standard 3D PCB fabrication renders.
