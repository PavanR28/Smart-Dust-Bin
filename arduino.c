#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "***ARMY***"
#define WIFI_PASS "greatindia"
#define FB_HOST "evsproj-636ac.firebaseio.com"
#define FB_AUTH "TgF6QISwOn7o0YP4zRR1EtZ0wGsUKJBcLrUoSH5n"

const int D1_PIN = D1;
const int D2_PIN = D2;

void setup() {
  Serial.begin(9600);
  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, INPUT);

  connectToWiFi();

  Serial.println("Connected to:");
  Serial.print(WiFi.localIP());
  Firebase.begin(FB_HOST, FB_AUTH);
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting.");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("WiFi Connected!");
}

void loop() {
  digitalWrite(D1_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(D1_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(D1_PIN, LOW);

  long duration = pulseIn(D2_PIN, HIGH);
  long inches = microsecondsToInches(duration);
  long cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  Firebase.setInt("dust", inches);
  delay(100);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
