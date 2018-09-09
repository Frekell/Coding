#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define DHTPIN 12
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  sensor_t sensor;
  delay(500);
  Serial.println("Setting up.");
  delay(1);
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop()
{
  sensors_event_t event;
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature))
    Serial.println("temp+" + String(event.temperature));
  digitalWrite(BUILTIN_LED, LOW);
  delay(1000);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  dht.humidity().getEvent(&event);

  if (!isnan(event.relative_humidity))
    Serial.println("hum: " + String(event.relative_humidity));
  digitalWrite(BUILTIN_LED, LOW);
  delay(1000);
  delay(5000);
}
