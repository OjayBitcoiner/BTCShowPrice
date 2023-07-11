# BTCShowPrice

This is a free open-source project whose main function is to display the price of Bitcoin in fiat currencies (USD, BRL, EUR).

The main objective is to encourage you to create your own gadgets, awakening your maker spirit by using low-cost components and easy assembly.

![IMG_20230711_021422408_HDR](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/8bb5ebce-4a85-4dda-a6d3-82354a84ffa7)

## Requirements
* Esp32 Doit Devkit Com Esp32-wroom-32
* LCD Display 2004 20x4 with Backlight, I2C Module Soldered (Makes your life easier)
* 3xPush-Buttons
* 7cm x 5cm perfboard
* 3D BOX [Here](https://github.com/OjayBitcoiner/BTCShowPrice/tree/main/3D%20FILES "3d printed box")

### Project Description

The project is using an ESP32 DevKit as the main component. In addition to this component, we are also utilizing a 20x4 LCD display with an I2C module already soldered. Three navigation buttons are also being used. **The objective of this project is to utilize low-cost components easily found anywhere.**

The logic of this project involves fetching the price of Bitcoin from an API using an HTTP request. After that, it retrieves the time from another API using an HTTP request. In this project, it is possible to edit the Bitcoin price update interval.

The project includes a menu where you can change some settings such as choosing to view the Bitcoin price in USD, BRL, or EUR. It is also possible to change the update interval in this menu and toggle the backlight on or off.

## Build Tutorial
### Hardware requirements
* Esp32 Doit Devkit with Esp32-wroom-32
* LCD Display 2004 20x4 with Backlight, I2C Module Soldered (Makes your life easier)
* 3x Push-Buttons
* 7cm x 5cm perfboard
* 3D BOX

### Schematic
![esquematico](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/c8e45dce-5725-4332-8e26-a302b2c851b2)
**Important Note**
The 10µF capacitor connected to the "enable" pin serves to assist in the upload process of the .ino code in the Arduino IDE.
  
### Uploading Code Using Arduino IDE
The idea is to provide a greater immersion in your maker experience, so to upload the project code, you will need to follow these steps:

Download the Arduino IDE from the official website: [Arduino IDE](https://www.arduino.cc/en/software)

Install the Arduino IDE on your computer.

Open the Arduino IDE and go to **Sketch -> Include Library -> Manage Libraries.**

In the Library Manager, search for the following libraries:

* LiquidCrystal_I2C
* Arduino_JSON
* debounce

Click on each library and click the **Install** button.

Once the libraries are installed, you can proceed with uploading the code to your ESP32 Devkit.

Note: The other libraries used in the project are native to the Arduino IDE.

Now you're ready to upload the code and start working on your project!

![image](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/10906d81-be98-46b5-b4b8-bd2a9a9d84cb)
![image](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/2b5e4d86-2978-4f3f-82f4-f9a15f914424)
![image](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/869913f7-e1e2-4958-ac10-98383a4f2489)

### BTC Show Price Configuration
To configure the device, simply insert the Wi-Fi SSID and password in the Arduino code and upload the project.

There is a function called **escreverMemoria();** that, after the initial upload and when the device is powered on, you will need to comment out this line of code and upload again. This way, your preferred changes will be saved in the storage of the ESP32.

Please note that any future modifications to the configuration can be made by editing the code and repeating the upload process.

![image](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/0b1b8be1-6515-4c97-9ec7-459ebdc616be)
![image](https://github.com/OjayBitcoiner/BTCShowPrice/assets/139197132/5b70818d-8383-4bf3-a2a4-d7bd7a2cd024)

### Donations/Project contributions
If you would like to contribute and help dev team with this project you can send a donation to the following LN address ⚡tepidcrocus57@walletofsatoshi.com⚡

Enjoy






