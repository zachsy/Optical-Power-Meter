# Wiring Notes

---

## Power and Grounding
- All components (ESP32, ADS1115, OPA381, photodiode) share a **single common ground**.
- The ADS1115 and OPA381 are powered from the ESP32 **3.3 V rail**.
- USB power introduces low-level noise; this is mitigated through averaging and digital filtering rather than additional analog regulation.

---

## I²C Wiring (ADS1115)
- SDA → ESP32 GPIO **21**
- SCL → ESP32 GPIO **22**
- ADS1115 I²C address detected at **0x48** (default address)
- Pull-up resistors are provided on the ADS1115 breakout board

I²C communication was stable once SDA and SCL wires were kept short and firmly seated.

---

## Analog Signal Path
- The photodiode (FDS100) is connected to an OPA381 configured as a transimpedance amplifier (TIA).
- The OPA381 output is routed directly to **ADS1115 A0** in single-ended mode.
- ADS1115 channels A1–A3 are unused and may float; only A0 should be interpreted.

- Long jumper wires significantly increased noise and apparent drift, so it is best to use shorter wires for this connection.

---

## Transimpedance Amplifier Configuration
- Feedback resistor (Rf): **100 kΩ**
- Feedback capacitor (Cf): **4.7 pF**

---

## Op-Amp Supply Decoupling
- A **0.1 µF ceramic capacitor** is placed directly across the OPA381 supply pins (V+ to GND).
- Local decoupling near the op-amp was critical for stability. Breadboard layouts without close decoupling exhibited slow drift and occasional instability.

