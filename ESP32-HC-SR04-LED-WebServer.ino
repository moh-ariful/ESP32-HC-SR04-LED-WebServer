#include <WiFi.h>
#include <WiFiManager.h> // Library WiFiManager

const int trigPin = 13;
const int echoPin = 27;
const int ledPin = 25;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
bool objectDetected = false;
unsigned long detectionStartTime = 0;

WiFiServer server(80);

String header;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Mulai Konfigurasi");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP32_AP");

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Memulai Server");
}

void loop() {
  // Sensor HC-SR04 code
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  
  if (distanceCm < 30) { // Deteksi objek dalam jarak 30 cm
    if (!objectDetected) {
      objectDetected = true;
      detectionStartTime = millis();
      digitalWrite(ledPin, HIGH);
    }
  } else {
    objectDetected = false;
    digitalWrite(ledPin, LOW);
  }
  
  if (objectDetected && millis() - detectionStartTime > 1000) {
    digitalWrite(ledPin, LOW);
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client Baru");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            Serial.println();

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html; charset=UTF-8");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta http-equiv=\"refresh\" content=\"1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; padding-top: 10px;}");
            client.println("body { margin-top: 0.5cm; }");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println(".header-text { color: #00008B; }");
            client.println(".esp-text { color: #D10069; }");
            client.println(".data-text { font-size: 2em; margin: 10px 0; }");
            client.println(".alert-box { background-color: red; color: white; padding: 20px; font-size: 24px; margin: 20px auto; max-width: 300px; display: none; animation: blink 1s infinite; }");
            client.println("@keyframes blink { 0% { opacity: 1; } 50% { opacity: 0; } 100% { opacity: 1; } }</style>");
            client.println("<script>");
            client.println("function showAlert() { document.getElementById('alertBox').style.display = 'block'; }");
            client.println("function hideAlert() { document.getElementById('alertBox').style.display = 'none'; }");
            client.println("</script></head>");

            client.println("<body><h1 class='header-text'>Next Koding Enterprise</h1>");
            client.println("<h1 class='esp-text'>ESP32 Web Server</h1>");
            
            client.println("<div id='alertBox' class='alert-box'>Ada obyek terdeteksi</div>");
            
            if (objectDetected) {
              client.println("<script>showAlert(); setTimeout(hideAlert, 2000);</script>");
            }
            
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client Terputus");
    header = "";
  }
}
