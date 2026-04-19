#include <RH_ASK.h> 
#include <SPI.h>
#include <DHT.h>    

// --- PINS ---
#define DHTPIN 4        // DHT11 Data Pin
#define DHTTYPE DHT11   // Sensor Type
#define TX_PIN 12       // RF Transmitter Data Pin

// --- OBJECTS ---
// Speed=2000, Rx=11(unused), Tx=12
RH_ASK driver(2000, 11, TX_PIN); 
DHT dht(DHTPIN, DHTTYPE);


struct DataPackage {
  float temperature;
};
DataPackage data;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  if (!driver.init()) {
    Serial.println("RF Init Failed - Check Wiring");
  } else {
    Serial.println("RF Transmitter Ready");
  }
}

void loop() {
 
  float t = dht.readTemperature();

  // Error Handling
  
  if (isnan(t)) {
    data.temperature = 0.0; 
    Serial.println("Error: DHT Sensor failed!");
  } else {
    data.temperature = t;
  }

  // 2. Transmit Data
  
  driver.send((uint8_t *)&data, sizeof(data));
  driver.waitPacketSent(); // Wait for transmission to finish
  
 
  Serial.print("Sent Temp: ");
  Serial.println(data.temperature);

  delay(1000); // 
}
