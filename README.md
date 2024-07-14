# ESP32-HC-SR04-LED-WebServer

## Description
This project demonstrates the use of an ESP32 microcontroller in combination with an HC-SR04 ultrasonic sensor and an LED. The system detects objects within a 30 cm range and provides visual feedback via the LED. Additionally, it hosts a web server using the WiFiManager library, allowing remote monitoring of the detection status. When an object is detected, a warning message is displayed on the web interface.

## Key Features
- **Object Detection**: Utilizes HC-SR04 ultrasonic sensor to detect objects within a 30 cm range.
- **Visual Feedback**: LED lights up when an object is detected.
- **Web Interface**: Provides real-time monitoring of the detection status through a web server.
- **WiFi Connectivity**: Automatically connects to WiFi using the WiFiManager library.

## Components
- ESP32
- HC-SR04 Ultrasonic Sensor
- LED
- WiFiManager Library

## How to Use
1. **Hardware Setup**:
    - Connect the HC-SR04 sensor and LED to the ESP32 as per the pin configurations in the code.
    - `trigPin` (HC-SR04 Trigger) to GPIO 13
    - `echoPin` (HC-SR04 Echo) to GPIO 27
    - `ledPin` (LED) to GPIO 25

2. **Software Setup**:
    - Install the required libraries in the Arduino IDE: `WiFi` and `WiFiManager`.
    - Upload the provided code to the ESP32.

3. **WiFi Configuration**:
    - Connect to the ESP32 access point named `ESP32_AP`.
    - Open a web browser and go to `192.168.4.1`.
    - Follow the prompts to configure and connect the ESP32 to your WiFi network.

4. **Accessing the Web Server**:
    - After successful WiFi configuration, the ESP32 will print its IP address to the serial monitor.
    - Open a web browser and enter the IP address to access the web interface.
    - The web interface will display the detection status and show a warning message if an object is detected.

## Code Explanation
### Setup
- Initializes serial communication, pin modes, and starts the WiFi manager and web server.

### Loop
- Continuously sends a trigger signal to the HC-SR04 sensor and calculates the distance to an object.
- Lights up the LED if an object is detected within 30 cm and maintains the state for one second.
- Handles incoming web client requests and updates the web interface with the current detection status.

## Example Output
When an object is detected within 30 cm:
- The LED lights up.
- The web interface shows a warning message.

## Future Improvements
- Implement additional sensor data visualization on the web interface.
- Add support for multiple sensors.
- Enhance the web interface with more interactive elements and controls.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
