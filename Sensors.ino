// Include necessary libraries
#include "MQ135.h"
#include "DHT.h"

// Sensor pins
#define pinA A4         // MQ135 pin connected to A4
#define DHTPIN 2        // AM2302 (DHT22) data pin connected to digital pin 2
#define DHTTYPE DHT22   // Defining the sensor type as DHT22

// Initialization of the MQ135 sensor
MQ135 sensorMQ = MQ135(pinA);

// Initialization of the AM2302 (DHT22) sensor
DHT dht(DHTPIN, DHTTYPE);

// Variable to track the LED state
bool ledOn = false;
const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  digitalWrite(13, LOW); // Ensure LED is off initially

  // Start communication over the serial link at 9600 baud
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Reading gas concentration in ppm from MQ135 sensor
  float ppm = sensorMQ.getPPM();

  // Reading temperature and humidity from AM2302 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any readings failed and print appropriate error messages
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from AM2302 sensor!");
  } else {
    // Print measured values to serial monitor
    Serial.print("Gaz: ");
    Serial.print(ppm);
    Serial.println(" ppm");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

  if (temperature > 16.0 && temperature < 24.0) { 
    digitalWrite(ledPin1, LOW);
  } else {
    digitalWrite(ledPin1, HIGH);
  }

  if (humidity > 35.0 && humidity <60.0) { 
    digitalWrite(ledPin2, LOW);
  } else {
    digitalWrite(ledPin2, HIGH);
  }

  if (ppm < 800.0) { 

    digitalWrite(ledPin3, LOW);
  } else {
    digitalWrite(ledPin3, HIGH);
  }
  }

  // Add a delay to avoid too frequent updates (3 seconds)
  delay(3000);
}
