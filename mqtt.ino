  #include <WiFi.h>
#include <PubSubClient.h>

// === WIFI CONFIG ===
#define WIFI_SSID "TrongHuy"                // SSID
#define WIFI_PASS "0984417423@"             // Password

// === MQTT CONFIG ===
#define MQTT_BROKER "broker.mqtt-dashboard.com"   // Địa chỉ MQTT broker
#define MQTT_PORT   1883                          // Port của MQTT
#define SUB_TOPIC   "esp32/sub/topic"       // Topic để nhận dữ liệu
#define PUB_TOPIC   "esp32/pub/topic"         // Topic để gửi dữ liệu


WiFiClient espClient;           // Client WiFi để kết nối mạng
PubSubClient client(espClient); // Client MQTT sử dụng WiFiClient


void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';  // Kết thúc chuỗi

  Serial.printf("Nội dung: %s\n", message);
}

// Hàm gửi dữ liệu JSON lên MQTT (test)
void publishExampleJson() {
 String data = "ESP32: " + String(millis() / 1000) + "s";
  
  Serial.print("Đang gửi: ");
  Serial.println(data);

  if (client.publish(PUB_TOPIC, data.c_str())) {
    Serial.println("Gửi thành công!");
  } else {
    Serial.println("Gửi thất bại!");
  }
}

// Hàm kết nối WiFi
void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi connecting...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nWiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// Hàm kết nối MQTT
void connectMQTT() {
  while (!client.connected()) {
    Serial.print("MQTT Broker connecting...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("MQTT Broker Connected!");
      
      // Subcribe topic
      if (client.subscribe(SUB_TOPIC)) {
        Serial.printf("Topic subcribed: %s\n", SUB_TOPIC);
      } else {
        Serial.println("Faild to subcribe topic!");
      }
    } else {
      Serial.print("Fail to connect broker, error code: ");         // Error code cực kỳ quan trọng, dễ tra ra lỗi 
      Serial.print(client.state());
      delay(5000); 
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  connectWiFi();

  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);  // Gán hàm xử lý khi nhận tin
  connectMQTT();

  //publishExampleJson(); // Test gửi tin đầu tiền
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  // Gửi dữ liệu định kỳ mỗi 10 giây
  static unsigned long lastTime = 0;
  if (millis() - lastTime >= 10000) {
    publishExampleJson(); // Hàm gửi tin nhắn
    lastTime = millis();
  }
}
