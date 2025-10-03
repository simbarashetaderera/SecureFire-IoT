# SecureFire-IoT

## Overview
SecureFire-IoT is an Internet of Things (IoT) based Smart Fire Detection and Suppression System featuring integrated alarm and water sprinkler units. The system modernizes fire safety by providing real-time detection, rapid response, remote notifications, and enhanced cybersecurity.

## Table of Contents
- [Features](#features)
- [Cybersecurity & Forensic Readiness](#cybersecurity--forensic-readiness)
- [System Architecture](#system-architecture)
- [Hardware Architecture](#hardware-architecture)
- [Circuit Board](#circuit-board)
- [Software Architecture](#software-architecture)
- [Flowchart Design](#flowchart-design)
- [Installation](#installation)
- [System Configuration](#system-configuration)
- [Tools Used](#tools-used)
- [Implementation Results](#implementation-results)
- [System Monitoring](#system-monitoring)
- [System Logging](#system-logging)
- [Notifications](#notifications)
- [Vulnerability Assessment](#vulnerability-assessment-and-mitigation)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features
- Flame and gas sensors networked to a NodeMCU ESP8266 microcontroller
- Immediate countermeasures:
  - Visual and auditory alarms
  - Automated water sprinkler activation
  - Remote notifications via Blynk, Telegram, and Thingsboard platforms
- 95% detection accuracy with ~2 second average response time
- Data encryption using TLS and secure MQTT communication
- Robust shielding and optimized network settings for sensor interference and connectivity issues

## Cybersecurity & Forensic Readiness
- All communications are encrypted, ensuring data integrity and confidentiality
- Secure MQTT protocol prevents unauthorized access
- Comprehensive logging and remote monitoring for forensic investigation during incidents

## System Architecture
- NodeMCU ESP8266 as the central controller
- Flame and gas sensors
- Water sprinkler control system
- Cloud-based notification and monitoring

## Hardware Architecture
<img src="https://github.com/user-attachments/assets/55c1b5d7-a0f0-4ebe-b2e5-f34291df47cd" alt="Hardware Architecture" width="500" height="300"/>

## Circuit Board
<img src="https://github.com/user-attachments/assets/725523f5-a967-4b9d-bbe8-cb5b218d8989" alt="Circuit Board" width="500" height="300"/>

## Software Architecture
<img src="https://github.com/user-attachments/assets/e4c455b6-5428-4c65-ab01-a13f2332caa2" alt="Software Architecture" width="500" height="300"/>

## Flowchart Design
<img src="https://github.com/user-attachments/assets/2ca0e6d9-334e-42c6-918c-6d6a3721d88b" alt="System Flowchart" width="500" height="400"/>

## Installation

### Prerequisites
- NodeMCU ESP8266 microcontroller
- MQ-2/MQ-5 gas sensor, flame sensor, relay module, water pump/sprinkler
- Arduino IDE 
- Internet connection 

### Steps
1. Clone the repository:
    ```bash
    git clone https://github.com/simbarashetaderera/SecureFire-IoT.git
    ```
2. Install required libraries in your Arduino IDE:
    - ESP8266WiFi
    - Blynk
    - WiFiManager
    - PubSubClient
    - ThingsBoard
3. Wire up the hardware according to the circuit diagram.
4. Edit the configuration file (see below) and add your WiFi credentials and cloud service tokens.
5. Upload the code to your NodeMCU ESP8266.

## System Configuration

Customize the following parameters in`config.h` (or relevant config file):

```cpp
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define BLYNK_TOKEN "your_blynk_token"
#define MQTT_SERVER "Enter your sever"
#define MQTT_PORT 8883
```

## Tools Used
- **Hardware:** NodeMCU ESP8266, MQ-2 gas sensor, flame sensor, relay, water pump, green LED light and red LED light
- **Software:** Arduino IDE, Blynk, Telegram API, ThingsBoard 
- **Protocols:** MQTT, TLS/SSL

## Implementation Results
<img src="https://github.com/user-attachments/assets/2733142b-023d-4143-85f1-d7caa7c273eb" alt="Implementation Results" width="500" height="300" />

The system uses NodeMCU ESP8266 to read sensor data, trigger alarms/sprinkler, and send alerts to the cloud and messaging platforms.

## System Monitoring
<img src="https://github.com/user-attachments/assets/74365e80-2d3d-4aa4-8bcc-76208e47727d" alt="System Monitoring" width="500" height="300"/>

ThingsBoard dashboard provides real-time analytics and historical logs for all sensor data and alerts.

## System Logging
<img src="https://github.com/user-attachments/assets/06906565-913f-4e19-a0f8-9c5b7cb266b4" alt="System Logging" width="500" height="300"/>

The system records all incidents, sensor readings, and actions taken for auditing and analysis.

## Notifications
### Telegram Alerts
<img src="https://github.com/user-attachments/assets/ad51c977-e1d1-4a7e-8f04-9aa57588602c" alt="Telegram Notification" width="500" height="500" />

Receive real-time alerts on your mobile device via Telegram.

### Email/SMS Integration *(Optional)*
You can extend notifications to email or SMS using services like Blynk.

## Vulnerability Assessment and Mitigation

### Wi-Fi Hacking
<img src="https://github.com/user-attachments/assets/9329e78c-355c-497d-a7da-16e79558d0a5" alt="Wi-Fi Attack" width="500" height="300"/>

WiFi deauthentication attacks are mitigated using encrypted protocols and frequent reconnection logic.

### Unsecure Data Transmission
<img src="https://github.com/user-attachments/assets/7c4773ea-1479-4b07-999d-7877604554e1" alt="Unsecure Transmission" width="500" height="300"/>

Avoid sending data without encryption. Always use TLS/SSL for MQTT and HTTP communications.

### Secure Data Transmission
<img src="https://github.com/user-attachments/assets/5f0a13fd-97c1-4d8a-8aae-c82a418958cb" alt="Secure Transmission" width="500" height="300"/>

TLS v1.2 encryption ensures all data sent to the cloud is secure and private.

## Future Improvements
- AI-driven predictive analytics for early fire detection
- Energy-efficient design optimizations
- Expansion of forensic logging capabilities
- Integration with smart home platforms (Home Assistant, Google Home)
- Battery backup and solar power options

## Contributing

We welcome contributions! Please follow these steps:
1. Fork the repository
2. Create a new branch (`git checkout -b feature-name`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature-name`)
5. Open a pull request

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions, suggestions, or commercial inquiries:

- **GitHub Issues:** [simbarashetaderera/SecureFire-IoT/issues](https://github.com/simbarashetaderera/SecureFire-IoT/issues)
- **Email:** simbarashetaderera@gmail.com
- **Telegram:** @simbarashetaderera

---








    
 


  


