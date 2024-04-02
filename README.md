# Accident-Detection-and-Prevention

Description:

This project implements an alcohol detection system integrated with anomaly detection for enhanced safety and monitoring. The system utilizes an ESP8266 microcontroller and an Arduino board to detect alcohol presence using an LDR sensor and to monitor anomalies through an accelerometer. An LCD display provides real-time feedback, and a relay controls the activation of an external device, such as a motor, based on anomaly detection.
Components:

    ESP8266 Microcontroller: Handles communication with the Blynk server and sensor data processing.
    Arduino Board: Manages sensor input and relay control.
    LDR Sensor: Detects alcohol presence by measuring light intensity.
    Accelerometer: Detects anomalies by measuring acceleration in three axes.
    Relay: Controls the activation of an external device based on anomaly detection.
    LCD Display: Provides real-time feedback on sensor readings and system status.

Setup Instructions:

    Hardware Setup:
        Connect the LDR sensor to analog pin A0 and the accelerometer to analog pins A1, A2, and A3.
        Connect the relay to digital pin 9 and the triger pin to digital pin 8.
        Connect the LCD display to the I2C interface (SDA, SCL) and supply power.

    Software Setup:
        Upload the provided code files to the ESP8266 microcontroller and the Arduino board.
        Ensure the required libraries (e.g., Blynk, LiquidCrystal_I2C) are installed in the Arduino IDE.
        Configure the Wi-Fi credentials and Blynk authentication token in the ESP8266 code.

    Blynk Setup:
        Create a new Blynk project with the template ID TMPL3IJo2LR6z.
        Add the necessary widgets (e.g., Value Display, Graph) to visualize sensor data and control the system remotely.

Operation:

    Alcohol Detection:
        The LDR sensor detects alcohol presence based on changes in light intensity.
        If the alcohol concentration exceeds a predefined threshold, an alert is triggered.

    Anomaly Detection:
        The accelerometer monitors acceleration in three axes (X, Y, Z) to detect anomalies.
        Anomalies such as collisions or sudden movements trigger an alert.

    System Control:
        The relay controls the activation of an external device, such as a motor, based on anomaly detection.
        When an anomaly is detected, the relay switches off, deactivating the external device.

Project Contributors:

    Pramod Krishnaa D
    Vignaraj D
    Tharun Kailash K
    Prabhu P
    Samson Roch

License:

This project is licensed under the MIT License. Feel free to use and modify the code for your own projects. Contributions are welcome.

For detailed instructions on configuring and operating the system, please refer to the project documentation and code comments. If you encounter any issues or have questions, feel free to reach out to the project contributors.
ChatGPT can make mistakes. Consider chec
