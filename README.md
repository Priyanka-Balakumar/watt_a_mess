# ⚡ Watt-a-Mess

# *AI-Powered Predictive Protection System for Smart Power Grids*

> **“Don’t just monitor failures — predict and prevent them.”**

---

## 🌍 **What Problem Does It Solve?**

Traditional transformer monitoring systems react **after damage begins** — often too late to prevent:

* 🔥 Transformer explosions
* ⚡ Arc faults & insulation breakdown
* 🧯 Fire hazards & grid downtime
* 👷 Safety risks for maintenance teams

**Watt-a-Mess flips the approach** → from *reactive maintenance* to **predictive intelligence at the edge**.

---

## 🧠 **What Makes It Different?**

Instead of relying only on temperature or voltage thresholds, this system:

✅ *Listens* to transformer sounds
✅ *Understands* abnormal patterns using AI
✅ *Acts instantly* without cloud dependency

---

## 🏗️ **System Architecture**

```
[ Node-A: Sensor Unit ]  --->  RF Link  --->  [ Node-B: AI Processing Unit ]

   Arduino UNO                               ESP32 (Dual-Core)
   ├── Temperature (DHT11)                   ├── TinyML Model (Edge Impulse)
   ├── Vibration Sensor                      ├── FFT + Spectrogram Analysis
   └── RF Transmitter                        ├── Fault Detection Logic
                                             ├── Cooling + Protection System
                                             └── IoT + Data Logging
```

---

## 🔍 **How It Works**

### 1️⃣ **Data Acquisition (Scout Node)**

* Captures environmental + mechanical signals
* Sends data wirelessly via **433 MHz RF**
* Maintains **electrical isolation** (critical for HV safety)

---

### 2️⃣ **Edge Intelligence (Brain Node)**

* Converts sound → frequency domain using **FFT**
* Generates spectrograms
* Runs **TinyML model (Edge Impulse)**

📊 Detects:

* Arcing sounds
* Coil looseness
* Partial discharges
* Abnormal vibrations

---

### 3️⃣ **Autonomous Action System**

When a fault is detected:

* 🔴 Activates **Trip Mode (Protection)**
* 🌀 Turns ON **Cooling Fan (TIP122 Driver)**
* 📲 Sends alert to IoT dashboard
* 💾 Logs event to SD Card (Black Box)

---

## ⚙️ **Core Features**

### 🔹 Dual-Node Safety Architecture

* Wireless separation prevents high-voltage risks
* Reliable even in harsh substation environments

### 🔹 Edge AI (TinyML)

* Real-time inference (<1 sec latency)
* No internet dependency
* > 90% classification accuracy (tested prototype)

### 🔹 Self-Healing Mechanism

* Automatic cooling activation
* Prevents thermal runaway

### 🔹 Grid Protection Logic

| State  | Indicator | Action           |
| ------ | --------- | ---------------- |
| Normal | 🟢 Green  | Breaker ON       |
| Fault  | 🔴 Red    | Trip + Isolation |

### 🔹 Offline Resilience
* Works without WiFi
* Stores all critical events locally

---

## 🔧 **Hardware Stack**

* **Microcontrollers:** Arduino UNO, ESP32
* **Communication:** 433 MHz RF Tx/Rx
* **Sensors:**
  * DHT11 (Temperature)
  * CZN-15E (Microphone)
  * SW-420 (Vibration)
* **Actuation:**
  * TIP122 Transistor
  * DC Cooling Fan
* **Display & Storage:**
  * OLED Display
  * SD Card Module

---

## 🧪 **Results & Validation**

✔️ Successfully detected abnormal acoustic patterns
✔️ Achieved **>90% prediction confidence**
✔️ Real-time response demonstrated in live prototype
✔️ Fully functional without cloud connectivity

---

## 🚀 **Why This Project Stands Out**

💡 Combines **Core ECE + Embedded + AI**
⚡ Solves a **real industrial problem**
🧠 Implements **Edge AI (TinyML)** — not just IoT
🔒 Focuses on **safety-critical system design**
📡 Demonstrates **wireless industrial architecture**

---

## 📈 **Future Scope**

* ☁️ Cloud dashboard with analytics
* 🏭 Multi-transformer network scaling
* 📊 Predictive maintenance scheduling
* ⚡ Integration with smart grid systems
* 🤖 Advanced anomaly detection models

---

## 🎯 **Use Cases**

* Power Substations
* Industrial Transformers
* Smart Grid Infrastructure
* Energy Distribution Systems

---

## 🏁 **Project Status**

* ✅ Prototype Built
* ✅ AI Model Deployed
* ✅ Live Demo Completed
* 🔜 Scaling & Cloud Integration

---
