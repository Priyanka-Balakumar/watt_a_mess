// ================= USER CONFIGURATION =================
#define BLYNK_TEMPLATE_ID "xxxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxx"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN_HERE"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASS";


#include <Grid-Guardian_inferencing.h> 

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <RH_ASK.h>
#include <SPI.h>


#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// --- PIN DEFINITIONS ---
#define RF_RX_PIN 4      
#define SOUND_PIN 35     
#define VIB_PIN 34       
#define FAN_PIN 13       
#define LED_SAFE 27      
#define LED_DANGER 26    

// --- OBJECTS ---
RH_ASK driver(2000, RF_RX_PIN, 12); 

struct DataPackage {
  float temperature;
};
DataPackage remoteData;

static float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

void setup() {
 
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 


  Serial.begin(115200);
  
  // 1. Init Pins
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_SAFE, OUTPUT);
  pinMode(LED_DANGER, OUTPUT);
  pinMode(VIB_PIN, INPUT);
  
  // Default State
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(LED_SAFE, HIGH); 
  digitalWrite(LED_DANGER, LOW);
  
  // 2. Init Hardware
  if(!driver.init()) Serial.println(F("RF Init Failed"));

  // 3. Init Blynk
 
  delay(1000); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("System Online (Stable Mode)");
}

void loop() {
  Blynk.run(); 

  // --- STEP 1: RECEIVE WIRELESS DATA ---
  uint8_t buf[sizeof(remoteData)];
  uint8_t buflen = sizeof(remoteData);
  
  if (driver.recv(buf, &buflen)) {
    memcpy(&remoteData, buf, sizeof(remoteData));
    Serial.print("RX Received: Temp = ");
    Serial.println(remoteData.temperature);
    Blynk.virtualWrite(V0, remoteData.temperature);
  }

  // --- STEP 2: COLLECT AUDIO ---
  for (size_t i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++) {
      features[i] = analogRead(SOUND_PIN);
      delayMicroseconds((int)(1000000 / EI_CLASSIFIER_FREQUENCY)); 
      
      // --- FIX 2: FEED THE WATCHDOG ---
    
      if (i % 100 == 0) {
         yield(); 
      }
  }

  // --- STEP 3: RUN AI ---
  signal_t signal;
  int err = numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  ei_impulse_result_t result = { 0 };
  err = run_classifier(&signal, &result, false);
  
  float fault_score = result.classification[0].value; 

  // --- STEP 4: LOGIC ---

  
  // A. ACTIVE COOLING
  String coolingStatus = "IDLE";
  if (remoteData.temperature > 30.0) {
    digitalWrite(FAN_PIN, HIGH); 
    coolingStatus = "ACTIVE";
  } else {
    digitalWrite(FAN_PIN, LOW);
  }
  Blynk.virtualWrite(V4, coolingStatus);

  // B. GRID PROTECTION
  String systemStatus = "SAFE";
  int vibration = digitalRead(VIB_PIN);

  if (fault_score > 0.95 || vibration == 1) {
    digitalWrite(LED_SAFE, LOW);    
    digitalWrite(LED_DANGER, HIGH); 
    systemStatus = "TRIPPED";
    Blynk.logEvent("critical_fault", "Grid Isolated!");
    Serial.println("!!! CRITICAL FAULT DETECTED !!!");
  } else {
    digitalWrite(LED_SAFE, HIGH);
    digitalWrite(LED_DANGER, LOW);
  }

  Blynk.virtualWrite(V1, systemStatus);
  Blynk.virtualWrite(V2, (int)(fault_score * 100));
}
