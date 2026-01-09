#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

// Your hardware
const float Rf = 100000.0f;                 // 100k feedback resistor
const float LSB_V = 0.0000078125f;          // V/count at GAIN_SIXTEEN

// Conditioning
int32_t dark_raw = 0;
float dRaw_filt = 0;
const float alpha = 0.15f;                  // smoothing
const int deadband = 5;                     // counts to ignore as "zero"

int32_t readAvgRaw(uint8_t ch, int N=64) {
  int32_t sum = 0;
  for (int i=0; i<N; i++) { sum += ads.readADC_SingleEnded(ch); delay(2); }
  return sum / N;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Wire.begin(21, 22);

  if (!ads.begin(0x48)) { Serial.println("ADS1115 not found"); while (1) delay(1000); }
  ads.setGain(GAIN_SIXTEEN);

  dark_raw = readAvgRaw(0);
  dRaw_filt = 0;

  Serial.println("Cover diode, type 'z' + Enter to zero.");
  Serial.println("rawAvg\tdRaw\tfiltCnt\tdV_uV\tdI_nA");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'z' || c == 'Z') {
      dark_raw = readAvgRaw(0);
      dRaw_filt = 0;
      Serial.print("Zeroed dark_raw="); Serial.println(dark_raw);
    }
  }

  int32_t raw = readAvgRaw(0);
  int32_t dRaw = raw - dark_raw;

  if (abs(dRaw) <= deadband) dRaw = 0;     // kill tiny drift

  dRaw_filt = (1 - alpha) * dRaw_filt + alpha * (float)dRaw;

  float dV_uV = dRaw_filt * (LSB_V * 1e6f);      // microvolts
  float dI_nA = (dRaw_filt * LSB_V / Rf) * 1e9f; // nanoamps

  Serial.print(raw);        Serial.print("\t");
  Serial.print(dRaw);       Serial.print("\t");
  Serial.print(dRaw_filt,2);Serial.print("\t");
  Serial.print(dV_uV, 2);   Serial.print("\t");
  Serial.println(dI_nA, 3);

  delay(200);
}