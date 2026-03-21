#define MQ135_PIN 34
#define RL_VALUE 10000    
#define R0 20000          
#define VCC 3.3           

void setup() {
  Serial.begin(115200);
}

void loop() {
  int adcValue = analogRead(MQ135_PIN);
  float vOut = (adcValue / 4095.0) * VCC;  
  
  // Calculate Rs
  float Rs = RL_VALUE * ((VCC - vOut) / vOut);
  
  // Ratio Rs/R0
  float ratio = Rs / R0;
  
  // CO2 ppm estimation using datasheet curve
  float ppm = pow(10, (-0.42 * log10(ratio) + 1.92));
  
  // Simple AQI mapping (illustrative)
  String aqiStatus;
  if (ppm < 600) aqiStatus = "Good";
  else if (ppm < 1000) aqiStatus = "Moderate";
  else if (ppm < 2000) aqiStatus = "Poor";
  else aqiStatus = "Hazardous";
  

  Serial.print("CO2 ppm: "); Serial.println(ppm);
  Serial.print("AQI Status: "); Serial.println(aqiStatus);
  
  delay(10000);
}
