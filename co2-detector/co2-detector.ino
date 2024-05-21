/*
 * Interfacing MQ135 Gas Sensor with Arduino
 * Author: Ashish
 * Website: www.circuitdigest.com
 * Date: 11-11-2020
 */
#include "MQ135.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// The load resistance on the board
#define RLOAD 22.0

// OLED display width and height, in pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for SSD1306 display connected using I2C (SDA, SCL)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MQ135 gasSensor = MQ135(A0);
int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  // SSD1306 allocation
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  int val = analogRead(A0);
  Serial.print("raw = ");
  Serial.println(val);

  float ppm = gasSensor.getPPM();
  Serial.print("ppm: ");
  Serial.println(ppm);

  // Update display
  display.clearDisplay();
  
  // Draw a border
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  
  // Display title
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 5);
  display.println("CO2 Level Monitor");
  
  // Display CO2 label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 25);
  display.println("CO2:");

  // Display PPM value
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(50, 25); // Adjusted cursor position
  display.print(ppm, 1); // Display one decimal place

  // Display units
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 45);
  display.println("ppm");
  
  display.display();

  // Check if ppm exceeds 650 and flash warning
  if (ppm > 2000) {
    for (int i = 0; i < 3; i++) { // Flash 3 times
      display.clearDisplay();
      display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 25);
      display.println("CO2 HIGH!");
      
      // Adjusted cursor position for the "Open Window!" message
      display.setCursor(10, 40); 
      display.println("Open Window!");
      
      // Show PPM value even during warning
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(30, 5); // Adjusted cursor position
      display.print(ppm, 1); // Display one decimal place

      display.display();
      delay(500);
      
      display.clearDisplay();
      display.display();
      delay(500);
    }
  }

  delay(2000);
}
