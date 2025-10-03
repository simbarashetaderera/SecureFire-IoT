# SecureFire-IoT
## Overview
SecureFire-IoT is an Internet of Things (IoT) based Smart Fire Detection and Suppression System with an integrated Alarm and Water Sprinkler Unit. The system improves traditional fire safety measures through increased automation, real-time responsiveness, and robust cybersecurity features.

## Features
- Flame and gas sensors networked to a NodeMCU ESP8266 microcontroller
- Immediate countermeasures:
  - Visual and auditory alarms
  - Automated water sprinkler activation
  - Remote notifications via Blynk, Telegram, and Thingsboard
- 95% detection accuracy with ~2 second average response time
- Data encryption using TLS and secure MQTT communication
- Optimized shielding and network settings for sensor interference and connectivity issues

- ## Cybersecurity & Forensic Readiness
- Encrypted communication ensures data integrity and confidentiality
- Secure MQTT protocol prevents unauthorized access
- Logging and remote monitoring enable forensic investigation in case of incidents

- ## System Architecture
- NodeMCU ESP8266 as the central controller
- Flame and gas sensors
- Water sprinkler control system
- Cloud-based notification and monitoring

- ## Hardware Architecture
- <img width="500" height="300" alt="Screenshot 2025-04-21 130801" src="https://github.com/user-attachments/assets/55c1b5d7-a0f0-4ebe-b2e5-f34291df47cd" />

- ## Circut Board
- <img src="https://github.com/user-attachments/assets/725523f5-a967-4b9d-bbe8-cb5b218d8989" width="500" height="300" />

- ## Software Architecture
- <img width="500" height="300" alt="Screenshot 2025-04-25 225131" src="https://github.com/user-attachments/assets/e4c455b6-5428-4c65-ab01-a13f2332caa2" />

- ## Flowchart Design
- <img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/2ca0e6d9-334e-42c6-918c-6d6a3721d88b" />

- ## Installations
- 1. Clone the repository: ...bash
- 2. git clone https://github.com/simbarashetaderera/SecureFire-IoT.git
- 3. Install required libraries (ESP8266WiFi, Blynk, WiFiManager, PubSubClient
- 4. Upload code to NodeMCU ESP8266

- ## System Configurations

- ## Tools used    
 
- ## Implementation Results
- <img width="500" height="300" alt="image" src="https://github.com/user-attachments/assets/2733142b-023d-4143-85f1-d7caa7c273eb" />
- This system uses a NodeMCU ESP8266 microcontroller connected to an MQ-2 gas sensor to detect smoke and flammable gases. A relay module is included to trigger alarms or fire extinguishers, and a green     LED provides a local status indicator for normal operation.

- ## System Monitoring
- <img width="600" height="300" alt="image" src="https://github.com/user-attachments/assets/74365e80-2d3d-4aa4-8bcc-76208e47727d" />
- During the one-minute monitoring interval, the ThingsBoard dashboard indicated a non-critical situation with no fire detected. The flame sensor remained inactive throughout the period, and gas levels     decreased from 170 ppm to just over 100 ppm, remaining well below the established danger threshold. The system assessed the environment as stable and determined that no corrective action was required.
  The monitoring results confirm that the environment was safe and stable during the observation period, with no immediate risk of fire or hazardous gas accumulation. The system functioned correctly in     detecting and reporting the non-critical status.

- ## System logging
- <img width="600" height="300" alt="image" src="https://github.com/user-attachments/assets/06906565-913f-4e19-a0f8-9c5b7cb266b4" />
- The system recorded a brief fire alert lasting 10 seconds triggered by a high gas concentration of approximately 642 ppm, while the flame sensor remained stable, confirming no actual fire. Gas levels     steadily decreased to 259 ppm, indicating a transient gas leak rather than a fire. This record is important for forensic investigation as it provides an accurate timeline, confirms the system’s correct   response, identifies a potential hazard source, supports compliance and accountability, and offers insights for improving safety measures.

- ## System Notification (Telegram)
- <img width="600" height="400" alt="image" src="https://github.com/user-attachments/assets/ad51c977-e1d1-4a7e-8f04-9aa57588602c" />
- Figure shows 30 minutes of fire and gas monitoring via Telegram, starting at 22:43 with an “All normal” status. Multiple fire and gas alerts occurred, with gas levels fluctuating between 120 and 642      ppm, peaking at 608–628 ppm around 22:56. Alerts were cleared quickly, often within a minute, suggesting either a highly responsive system or potential sensor sensitivity issues. In conclusion, the       system effectively detected and responded to hazardous gas levels, maintaining safety, though further assessment of sensor accuracy may be warranted.

- ## Vulnerability Assessment and its Mitigation
-  ### Wi-Fi Hacking
   <img width="600" height="300" alt="image" src="https://github.com/user-attachments/assets/9329e78c-355c-497d-a7da-16e79558d0a5" />
-  Figure above illustrates a WiFi deauthentication attack on the NodeMCU, forcing it to disconnect from its network by exploiting a WiFi protocol flaw. This disruption halted data transmission and          remote control, severely affecting IoT operations such as smart fire detection, where notifications, sensor readings, and automated responses became unreliable. To mitigate such attacks, upgrading to     WPA3 is recommended, as it secures deauthentication frames and strengthens overall network protection.

-  ### Unsecure Data Transimission
   <img width="500" height="300" alt="image" src="https://github.com/user-attachments/assets/7c4773ea-1479-4b07-999d-7877604554e1" />
-  Figure above depicts data communications without encryption which is vulnerable to data breaches. Furthermore, if data transmission between IoT devices and central monitoring systems is not properly      secured, data breaches may occur. Therefore, end-to-end encryption techniques ensure that data remains private and only accessible to approved parties. Regular security audits and updates improve data    security by swiftly identifying and resolving concerns. This issue was resolved by introducing the transport layer protocol, which encrypts data in transmission to prevent data breaches.

-  ### Secure Data Transimission
   <img width="500" height="300" alt="image" src="https://github.com/user-attachments/assets/5f0a13fd-97c1-4d8a-8aae-c82a418958cb" />
-  Figure 16 shows network traffic from a NodeMCU-based fire detection system. The device (IP 192.168.97.150) securely sends encrypted data via TLSv1.2 to a remote ThingsBoard server (IP 35.174.127.31)      on port 443, ensuring sensitive telemetry is protected. It also publishes MQTT messages to a local broker (IP 192.168.97.52) on the v1/devices/me/telemetry topic, indicating both secure remote and        local data transmission. In conclusion, the system demonstrates proper use of encryption and secure protocols, ensuring the confidentiality and integrity of critical fire detection and telemetry data.

- ## Future Improvements
-  AI-driven predictive analytics for early fire detection
-  Energy-efficient design optimizations
-  Expansion of forensic logging capabilities    

     








    
 


  


