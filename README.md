# DIY Optical Power Meter (ESP32 + Photodiode + MATLAB)

A low-cost optical power meter built using a silicon photodiode and a low-noise transimpedance amplifier, with data acquisition via ESP32 and calibration/analysis performed in MATLAB.  
This project focuses on **optical measurement accuracy**, **analog front-end design**, and **hardware–software integration**.

---

## Motivation

Commercial optical power meters are expensive and often opaque in how measurements are performed.  
This project explores how accurately optical power can be measured using off-the-shelf components while maintaining good engineering practice in analog design, calibration, and data analysis.

Key goals:
- Understand photodiode-based optical power measurement
- Design and debug a low-noise transimpedance amplifier (TIA)
- Calibrate raw voltage measurements to optical power
- Document the full system clearly and reproducibly

---

## System Overview

**Signal Chain**
- Optical power is converted to photocurrent by the photodiode  
- Photocurrent is converted to voltage using a precision TIA  
- Voltage is digitized by an external 16-bit ADC (ADS1115)
- ESP32 reads the digitized data over I²C and streams it to MATLAB
- MATLAB applies calibration curves and analyzes accuracy

---

## Hardware

### Major Components
- **Photodiode**: FDS100 (Si photodiode)
- **Amplifier**: OPA381 (low-noise transimpedance amplifier)
- **ADC**: ADS1115 (16-bit delta-sigma ADC)
- **Microcontroller**: ESP32 development board
- **Passive Components**: Precision feedback resistor, compensation capacitor, decoupling capacitors

### Breadboard Implementation
All hardware is implemented on a solderless breadboard. See [photos](#hardware/wiring).

[Additional wiring notes](#harware/wiring/wiring_notes.md).

---

## Firmware (ESP32)

The ESP32 firmware performs:
- ADC configuration
- Periodic sampling of the TIA output
- Serial transmission of raw ADC values

[Location](#firmware/esp32/)

---

## MATLAB Software

MATLAB is used for:
- Serial data acquisition
- Calibration curve fitting
- Plotting and error analysis

[Location](#matlab/)

---

## Calibration & Measurement Approach

Rather than relying solely on theoretical photodiode responsivity and
component tolerances, this system uses **empirical calibration**.

Key concepts:
- A dark measurement is taken to capture ambient light and offset
- Dark readings are subtracted from illuminated readings
- Calibration maps ADC output to optical power using known sources

This approach allows reliable low-power measurements under normal indoor
lighting without requiring a fully dark room.

---

## Repository Structure
[`hardware/`](hardware/)    → wiring photos, BOM

['firmaware/'](firmware/)    → ESP32 code

['matlab/'](matlab/)      → calibration and analysis scripts

---