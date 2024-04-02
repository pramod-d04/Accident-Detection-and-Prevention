#define BLYNK_TEMPLATE_ID "TMPL3IJo2LR6z"
#define BLYNK_TEMPLATE_NAME "Alcohol Detection"
#define BLYNK_AUTH_TOKEN "ZGgQ7CBhW4Ng62GINfgpWD1a6CNwxuC9"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi credentials
const char* ssid = "Vnord";
const char* password = "Vignu1010";

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

// Pin configurations
const int ledPin = LED_BUILTIN; // Built-in LED pin

// Blynk virtual pin
const int accelerometerVirtualPinX = V1; // Virtual pin for X-axis accelerometer value
const int accelerometerVirtualPinY = V2; // Virtual pin for Y-axis accelerometer value
const int accelerometerVirtualPinZ = V3; // Virtual pin for Z-axis accelerometer value
const int alcoholValueVirtualPin = V0;
const int trigerValueVirtualPin = V4;

BlynkTimer timer;

void sendSensor() {
  if (Serial.available() > 0) {
    String s = Serial.readStringUntil('\n'); // Read the input line
    // Serial.println(s);

    int spaceIndex = s.indexOf(' ');
    String ldrPart = s.substring(spaceIndex + 1);
    
    // Extract LDR value
    int ldrIndex = s.indexOf("LDR: ") + 5;
    int ldr = s.substring(ldrIndex, s.indexOf(" X: ", ldrIndex)).toInt();
    
    // Extract X value
    int xIndex = ldrPart.indexOf("X:");
    int x = ldrPart.substring(xIndex + 2, ldrPart.indexOf(' ', xIndex)).toInt();
    
    // Extract Y value
    int yIndex = ldrPart.indexOf("Y:");
    int y = ldrPart.substring(yIndex + 2, ldrPart.indexOf(' ', yIndex)).toInt();
    
    // Extract Z value
    int zIndex = ldrPart.indexOf("Z:");
    int z = ldrPart.substring(zIndex + 2, ldrPart.indexOf(' ', zIndex)).toInt();

    int tIndex = ldrPart.indexOf("T:");
    int t = ldrPart.substring(tIndex + 2).toInt();
    
    // Print the extracted values
    Serial.print("LDR: ");
    Serial.print(ldr);
    Serial.print(" X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.print(z);
    Serial.print(" T: ");
    Serial.println(t);

    // // Extract LDR and accelerometer values from input
    // int ldrIndex = input.indexOf("LDR: ") + 5;
    // int xIndex = input.indexOf("X: ") + 3;
    // int yIndex = input.indexOf("Y: ") + 3;
    // int zIndex = input.indexOf("Z: ") + 3;

    // int ldrValue = input.substring(ldrIndex, input.indexOf(" X: ", ldrIndex)).toInt();
    // int accelerometerXValue = input.substring(xIndex, input.indexOf(" Y: ", xIndex)).toInt();
    // int accelerometerYValue = input.substring(yIndex, input.indexOf(" Z: ", yIndex)).toInt();
    // int accelerometerZValue = input.substring(zIndex).toInt();
    
    // Serial.print("LDR: ");
    // Serial.print(ldrValue);
    // Serial.print(", X: ");
    // Serial.print(accelerometerXValue);
    // Serial.print(", Y: ");
    // Serial.print(accelerometerYValue);
    // Serial.print(", Z: ");
    // Serial.println(accelerometerZValue);

    // Send values to Blynk
    Blynk.virtualWrite(accelerometerVirtualPinX, x);
    Blynk.virtualWrite(accelerometerVirtualPinY, y);
    Blynk.virtualWrite(accelerometerVirtualPinZ, z);
    Blynk.virtualWrite(alcoholValueVirtualPin, ldr);
    Blynk.virtualWrite(trigerValueVirtualPin, t);

    // Example threshold check (you may adjust this according to your needs)
    if (ldr > 630) {
      digitalWrite(ledPin, HIGH); // Turn off LED
      Blynk.logEvent("alcohol_detected", "Alcohol Detected");
    } else if (abs(x) > 50 || abs(y) > 50 || abs(z) > 50 || t == 1) {
      digitalWrite(ledPin, HIGH); // Turn off LED
      Blynk.logEvent("accident_alert", "Accident Occurred");
    } else {
      digitalWrite(ledPin, LOW); // Turn on LED
    }
  }
}

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Blynk.begin(auth, ssid, password); // Connect to Blynk
  timer.setInterval(1000L, sendSensor); // Setup Blynk timer
}

void loop() {
  Blynk.run(); // Run Blynk
  timer.run(); // Run Blynk timer
}
