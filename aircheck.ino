#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHT_PINO 14
#define DHTTYPE DHT11

const int MQ2_PINO = 13;

DHT dht(DHT_PINO, DHTTYPE);

unsigned long previousMillis = 0;    // Tracks the last sensor reading time
const unsigned long interval = 500;  // Read sensors every 2 seconds

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(MQ2_PINO, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();  // Get current time

  // Check if it's time to read sensors
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the previous time

    JsonDocument doc;

    // Read sensors
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int smokeLevel = analogRead(MQ2_PINO);

    // Validate DHT readings
    if (!isnan(humidity) || !isnan(temperature)) {
      doc["humidade"] = humidity;
      doc["temperatura"] = temperature;
    }

    doc["fumaca"] = smokeLevel;

    doc.shrinkToFit();

    serializeJson(doc, Serial);
    Serial.println();
  }
}