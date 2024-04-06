#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int stepCount = 0;
float threshold = 20.5; // Adjust this threshold according to your need

void setup(void) {
  Serial.begin(9600);
  Serial.println("Accelerometer Test");

  if (!accel.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop(void) {
  sensors_event_t event;
  accel.getEvent(&event);
  
  float acceleration = sqrt(event.acceleration.x * event.acceleration.x + 
                             event.acceleration.y * event.acceleration.y +
                             event.acceleration.z * event.acceleration.z);
                             
  Serial.print("Acceleration: "); Serial.println(acceleration);
  
  if (acceleration > threshold) {
    stepCount++;
    Serial.print("Steps: "); Serial.println(stepCount);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("STEPS: ");
    display.println(stepCount*2);
    display.setTextSize(1);
     display.println("                    ");
     display.println("                    ");
     display.println("  THIS TO WILL PASS ");
    display.display();
    delay(300); // Add delay to avoid counting multiple steps for a single motion
  }
}
