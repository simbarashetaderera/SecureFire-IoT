// ---------- Hardware Configuration ----------
const int LED1 = D2;
const int LED2 = D3;
const int RELAY = D0;
const int Flame_sensor = D1;
const int mq2Sensor = A0;

// ---------- Global Variables ----------
bool fireAlertSent = false;
int gasThreshold = 700;
int Flame_detected = 4;

// ---------- WiFi ----------
const char* ssid = ""; //Enter SSID
const char* password = ""; //Enter your Password

// ---------- Blynk ----------
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "" //Enter Blynk ID
#define BLYNK_TEMPLATE_NAME ""  // Enter your template name
#define BLYNK_AUTH_TOKEN "" //Enter Blynk auth token

// ---------- Telegram ----------
#define BOT_TOKEN "" //Enter BOT Token
#define CHAT_ID "" //Enter your Telegram ID

// ---------- ThingsBoard ----------
#define THINGSBOARD_SERVER "" //Enter your server IP
#define THINGSBOARD_PORT  // Enter thingsboard port
#define THINGSBOARD_TOKEN "" //Enter Thingsboard token

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <UniversalTelegramBot.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WebServer.h>

// ---------- MQTT Configuration ----------
const char* mqtt_server = THINGSBOARD_SERVER;
const int mqtt_port = THINGSBOARD_PORT;
const char* mqtt_username = THINGSBOARD_TOKEN;
const char* mqtt_password = "";

// ---------- Global Clients ----------
WiFiClient espClient;
PubSubClient client(espClient);
WiFiClientSecure telegramClient;
UniversalTelegramBot bot(BOT_TOKEN, telegramClient);
BlynkTimer timer;
ESP8266WebServer server(80);

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  pinMode(Flame_sensor, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH); // Relay OFF initially

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected! IP: " + WiFi.localIP().toString());

  telegramClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);

  reconnectMQTT();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  timer.setInterval(2000L, checkSensors);

  // ---------- Web Interface ----------
  server.on("/", []() {
    server.send(200, "text/html", generateHTMLPage());
  });
  server.begin();
  Serial.println("🌐 Web interface started at: http://" + WiFi.localIP().toString());
}

// ---------- MQTT Callback ----------
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println("MQTT Message [" + String(topic) + "]: " + message);

  if (String(topic).startsWith("v1/devices/me/rpc/request/")) {
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");

    if (message.indexOf("\"method\":\"activateSprinkler\",\"params\":true") >= 0) {
      activateSprinkler(true);
      client.publish(responseTopic.c_str(), "{\"success\":true}");
    } else if (message.indexOf("\"method\":\"activateSprinkler\",\"params\":false") >= 0) {
      activateSprinkler(false);
      client.publish(responseTopic.c_str(), "{\"success\":true}");
    }
  } else if (message == "ON") {
    activateSprinkler(true);
  } else if (message == "OFF") {
    activateSprinkler(false);
  }
}

// ---------- MQTT Connection ----------
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT... ");
    if (client.connect("ESP8266_FireSystem", mqtt_username, mqtt_password)) {
      Serial.println("✅ Connected to MQTT!");
      client.subscribe("v1/devices/me/rpc/request/+");
      client.subscribe("fire/control");
    } else {
      Serial.print("❌ Failed, code: ");
      Serial.print(client.state());
      Serial.println(". Retrying in 5s...");
      delay(5000);
    }
  }
}

// ---------- Sensor Check ----------
void checkSensors() {
  Flame_detected = digitalRead(Flame_sensor);
  int gasValue = analogRead(mq2Sensor);
  bool gasDetected = gasValue > gasThreshold;
  bool fireDetected = (Flame_detected == 0 || gasDetected);

  Serial.print("Flame: ");
  Serial.print(Flame_detected);
  Serial.print(" | Gas: ");
  Serial.print(gasValue);
  Serial.print(" | Fire Detected: ");
  Serial.println(fireDetected);

  sendSensorData(fireDetected, gasValue);
  handleAlerts(fireDetected, gasValue);
}

// ---------- Send Data ----------
void sendSensorData(bool fireDetected, int gasValue) {
  String telemetry = "{\"flame\":" + String(Flame_detected) +
                     ",\"gas\":" + String(gasValue) +
                     ",\"fire_alert\":" + String(fireDetected ? 1 : 0) + "}";
  client.publish("v1/devices/me/telemetry", telemetry.c_str());

  Blynk.virtualWrite(V0, fireDetected ? 1 : 0);
  Blynk.virtualWrite(V1, gasValue);
  Blynk.virtualWrite(V2, Flame_detected);
}

// ---------- Handle Alerts ----------
void handleAlerts(bool fireDetected, int gasValue) {
  if (fireDetected) {
    activateSprinkler(true);
    digitalWrite(LED1, LOW); delay(70);
    digitalWrite(LED1, HIGH); delay(70);
    digitalWrite(LED2, HIGH);

    Blynk.logEvent("fire_detection", "🔥 Fire or Gas Detected! Gas Level: " + String(gasValue));
    Serial.println("🚨 Fire or Gas detected! Sprinkler ON");

    if (!fireAlertSent) {
      bot.sendMessage(CHAT_ID, "🔥 Fire or Gas Detected!\nGas Level: " + String(gasValue), "");
      fireAlertSent = true;
    }
  } else {
    activateSprinkler(false);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    Serial.println("✅ No Fire or Gas Detected");

    if (fireAlertSent) {
      bot.sendMessage(CHAT_ID, "✅ Fire/Gas is cleared. All normal.", "");
      fireAlertSent = false;
    }
  }
}

// ---------- Sprinkler Control ----------
void activateSprinkler(bool activate) {
  digitalWrite(RELAY, activate ? LOW : HIGH); // LOW = ON
  Serial.println(activate ? "🚨 Sprinkler ON" : "✅ Sprinkler OFF");
}

// ---------- Web Page HTML ----------
String generateHTMLPage() {
  String flameStatus = (Flame_detected == 0) ? " DETECTED" : "✅ None";
  String sprinklerStatus = (digitalRead(RELAY) == LOW) ? "💦 ON" : "OFF";
  String ipAddress = WiFi.localIP().toString();

  String html = R"=====(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Fire Detection Dashboard</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta http-equiv="refresh" content="3">
      <style>
        body {
          font-family: Arial, sans-serif;
          background-color: #f5f7fa;
          color: #333;
          margin: 0;
          padding: 0;
        }
        .container {
          max-width: 500px;
          margin: 40px auto;
          background: #fff;
          padding: 30px;
          border-radius: 12px;
          box-shadow: 0 4px 10px rgba(0,0,0,0.1);
        }
        h2 {
          text-align: center;
          color: #444;
        }
        .card {
          background: #f0f0f0;
          padding: 20px;
          margin: 15px 0;
          border-radius: 8px;
          font-size: 18px;
        }
        .status {
          font-weight: bold;
          color: #000;
        }
        .footer {
          text-align: center;
          font-size: 14px;
          margin-top: 20px;
          color: #aaa;
        }
      </style>
    </head>
    <body>
      <div class="container">
        <h2> Fire Detection System</h2>
        <div class="card">Flame Status: <span class="status">)=====" + flameStatus + R"=====(
        </span></div>
        <div class="card">Gas Level: <span class="status">)=====" + String(analogRead(mq2Sensor)) + R"=====(
        </span></div>
        <div class="card">Sprinkler: <span class="status">)=====" + sprinklerStatus + R"=====(
        </span></div>
        <div class="card">Device IP: <span class="status">)=====" + ipAddress + R"=====(
        </span></div>
        <div class="footer">Last update: )=====" + String(millis() / 1000) + R"=====(s</div>
      </div>
    </body>
    </html>
  )=====";

  return html;
}

// ---------- Main Loop ----------
void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
  Blynk.run();
  timer.run();
  server.handleClient(); // Handle web requests
}
