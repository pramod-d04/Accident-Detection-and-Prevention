#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LDR_PIN A0
#define RELAY_PIN 9
#define TRIGER_PIN 8

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin configurations for accelerometer
const int accelerometerXPin = A1; // Analog pin for X-axis accelerometer
const int accelerometerYPin = A2; // Analog pin for Y-axis accelerometer
const int accelerometerZPin = A3; // Analog pin for Z-axis accelerometer

// Initial values for the accelerometer readings
const int initialXValue = 366;
const int initialYValue = 363;
const int initialZValue = 440;

// Threshold value for accident detection
const int sensorThreshold = 50;

bool anomalyDetected = false; // Flag to track anomaly detection

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode( TRIGER_PIN, INPUT);
  digitalWrite(RELAY_PIN, LOW); // Make sure the relay is initially off
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  int val = analogRead(LDR_PIN);
  int val2 = digitalRead(TRIGER_PIN);
  int accelerometerXValue = analogRead(accelerometerXPin) - initialXValue;
  int accelerometerYValue = analogRead(accelerometerYPin) - initialYValue;
  int accelerometerZValue = analogRead(accelerometerZPin) - initialZValue;

  // Display LDR and accelerometer values on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LDR Value: ");
  lcd.print(val);

  // Print absolute values of accelerometer readings to Serial monitor
  Serial.print("LDR: ");
  Serial.print(val);
  Serial.print(" X:");
  Serial.print(abs(accelerometerXValue));
  Serial.print(" Y:");
  Serial.print(abs(accelerometerYValue));
  Serial.print(" Z:");
  Serial.print(abs(accelerometerZValue));
  Serial.print(" T:");
  Serial.println(val2);


  // Check for alcohol presence using LDR
  if (val > 600) {
    lcd.setCursor(0, 1);
    lcd.print("Alcohol Detected");
    anomalyDetected = true;
  } else {
    // Example threshold check for accident detection
    if (abs(accelerometerXValue) > sensorThreshold || abs(accelerometerYValue) > sensorThreshold || abs(accelerometerZValue) > sensorThreshold) {
      lcd.setCursor(0, 1);
      lcd.print("Collision");
      anomalyDetected = true;
    }else if(val2 == HIGH){
      lcd.setCursor(0, 1);
      lcd.print("Collision");
      anomalyDetected = true;
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("Monitoring");
      anomalyDetected = false;
    }
  }

  // Control the relay (and thus the DC motor) based on anomaly detection
  if (!anomalyDetected) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay (which turns on the motor)
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay (which turns off the motor)
  }

  delay(1000);
}
