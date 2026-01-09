# Measurement Theory

This document describes the theoretical basis for the optical power
measurement system implemented in this project. The goal is to explain
how incident optical power is converted into a calibrated digital
measurement, as well as the assumptions and limitations inherent to
this approach.

---

## Photodiode Operation

A silicon photodiode generates a photocurrent when photons are absorbed
in its active region. For a given wavelength, the generated photocurrent
is approximately proportional to the incident optical power.

The proportionality constant is the photodiode responsivity, typically
expressed in amperes per watt (A/W). Responsivity depends on wavelength
and material properties, and is provided by the manufacturer.

In this system, the photodiode is operated in reverse bias mode to:
- Improve linearity
- Reduce junction capacitance
- Increase response speed

The resulting output is a small current proportional to optical power.

---

## Transimpedance Amplifier (TIA)

Because the photodiode produces a current rather than a voltage, a
transimpedance amplifier (TIA) is used to convert photocurrent into a
measurable voltage.

The ideal transimpedance relationship is:

V_out = -I_photo × R_f

where:
- I_photo is the photodiode current
- R_f is the feedback resistor

A small feedback capacitor is placed in parallel with the resistor to
ensure amplifier stability and to limit bandwidth. This tradeoff
reduces high-frequency noise while maintaining adequate response for
steady-state power measurements.

---

## Analog-to-Digital Conversion (ADS1115)

The output of the TIA is digitized using an external 16-bit delta-sigma
ADC (ADS1115). An external ADC is used instead of the ESP32’s internal
ADC to achieve improved resolution, linearity, and measurement
repeatability.

Key characteristics of the ADS1115 include:
- 16-bit resolution
- Programmable gain amplifier (PGA)
- Differential and single-ended input options
- I²C digital interface

The ADC converts the analog voltage into a digital representation that
is read by the ESP32 and transmitted to a host computer.

---

## Signal Chain Relationship

The overall measurement chain can be summarized as:

Optical Power → Photocurrent → Voltage → ADC Counts

Because photodiode responsivity and analog component tolerances vary,
the system does not rely solely on theoretical constants. Instead,
calibration is used to empirically map ADC counts to optical power.

---

## Ambient Light and Dark Subtraction

Photodiodes are sensitive to all incident light within their spectral
response range, including ambient room lighting. To mitigate this, a
dark measurement is taken with the laser blocked or turned off.

This dark reading captures ambient light, amplifier offsets, and ADC
offsets. Subtracting the dark reading from the illuminated measurement
isolates the contribution due to the laser alone.

This approach enables reliable low-power measurements without requiring
a fully dark environment.

---

## Scope and Limitations

This measurement approach is intended for relative and comparative
optical power verification. It is not a substitute for calibrated
laboratory-grade optical power meters, but provides meaningful insight
into whether low-cost lasers operate within expected power ranges.