---

# Interfacing MQ135 Gas Sensor with Arduino

## Description
This project demonstrates how to interface the MQ135 Gas Sensor with Arduino to measure CO2 levels in parts per million (ppm). When the CO2 level exceeds a threshold (650 ppm), the display will flash a warning message prompting the user to open a window for ventilation.

## Components Used
- Arduino Nano
- MQ135 Gas Sensor
- 128x64 OLED Display (SSD1306)
- Jumper Wires

## Pinout
- **OLED Display**:
  - VCC to 5V
  - GND to GND
  - SDA to A4 (SDA on Arduino Nano)
  - SCL to A5 (SCL on Arduino Nano)

- **MQ-135 Sensor**:
  - VCC to 5V
  - GND to GND
  - A0 to A0 on Arduino Nano

![Pinout](https://github.com/bassslapper3390/Measuring-Concentration--Of-CO2-in-Air-using-Arduino-nano-and-MQ-135-Sensor/assets/75876257/a8241749-35c6-43bd-8a16-4e8729917369)
If you are wondering why the pinouts are different in the photo its because the photo uses diffent display, i have used 4 pin oled display and have given the pinouts accordingly, refer those.

## Calculating the Ro Value of MQ135 Sensor
To calculate the Ro values in clean air, follow these steps:
1. Download the [MQ-135 Library](https://github.com/GeorgK/MQ135) and preheat the sensor for 24 hours before reading the Ro values.
2. Use the following code to read the Ro values:

```cpp
#include "MQ135.h"
void setup (){
Serial.begin (9600);
}
void loop() {
MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
float rzero = gasSensor.getRZero();
Serial.println (rzero);
delay(1000);
}
```

3. Once you have obtained the Ro values, navigate to `Documents > Arduino > libraries > MQ135-master` folder and open the `MQ135.h` file.
4. Change the `RLOAD` and `RZERO` values in the file:

```cpp
/// The load resistance on the board
#define RLOAD 22.0
/// Calibration resistance at atmospheric CO2 level
#define RZERO 5804.99
```

5. Scroll down and replace the `ATMOCO2` value with the current Atmospheric CO2 level (e.g., 411.29):

```cpp
/// Atmospheric CO2 level for calibration purposes
#define ATMOCO2 397.13
```

## Installation
1. Connect the components according to the pinout provided.
2. Install the required libraries:
   - **Adafruit GFX Library**: [Download from Adafruit](https://github.com/adafruit/Adafruit-GFX-Library)
   - **Adafruit SSD1306 Library**: [Download from Adafruit](https://github.com/adafruit/Adafruit_SSD1306)
   - **MQ135 Library**: [Download from Arduino Library Manager](https://www.arduinolibraries.info/libraries/mq135)
3. Upload the provided [Arduino code](/code/co2-detector.ino) to your Arduino Nano board.
4. Open the serial monitor or connect display to view the CO2 readings and warnings when CO2 levels are high.

![OLED Display](https://github.com/bassslapper3390/Measuring-Concentration--Of-CO2-in-Air-using-Arduino-nano-and-MQ-135-Sensor/assets/75876257/7ba68326-7083-43fa-a41d-b6000bd8105f)
![MQ135 Sensor](https://github.com/bassslapper3390/Measuring-Concentration--Of-CO2-in-Air-using-Arduino-nano-and-MQ-135-Sensor/assets/75876257/96512712-d351-4bb9-87fc-824502ee6978)


## Future Scope
Integrate the system with home automation platforms like Home Assistant to monitor CO2 levels in closed rooms. Automatically trigger actions such as opening windows or activating ventilation systems when CO2 levels exceed a predefined threshold. (Will probably use an ESP32)

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the [LICENSE](/LICENSE) file for details.

---
