# weather-monitoring-system

This project aims at finding the different weather parameters using ARUDINO UNO microcontroller.The data logging system enables to save the data temporarily in the server after every 30 seconds and we can see the final graph on any portable device. The apparatus includes 4 fans each for a particular direction- North, South, East and West. The fans are connected to a motor and display a voltage change on the LCD when wind passes. The temperature sensor (LM35) and the humidity sensor (DHT11) constantly measure their respective parameters. The data is then sent to the server using the Wi-Fi module (ESP8266-12E). A level shifter (LM1117) enables the Wi-fi module to connect to the microcontroller as the operating voltage of the Wi-fi module is 3.3v while the microcontroller operates at 5v.

Arduino IDE is used for coding
