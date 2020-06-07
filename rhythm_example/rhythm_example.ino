#define NUM 10
int volts[NUM] = {0};
int count = 0;
const int sampleWindow = 10;
unsigned int sample;

#define SOLENOID_PIN 13

void setup() {
  Serial.begin(115200);
  pinMode(SOLENOID_PIN,OUTPUT);
}

void loop() {
  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample > signalMax) signalMax = sample;
    else if (sample < signalMin)  signalMin = sample;
  }
  
  peakToPeak = signalMax - signalMin;
  volts[count] = peakToPeak;
  
  int volts_ave = 0;
  
  for(int i = 0; i < NUM; i++){
    volts_ave+=volts[i];
  }
  
  volts_ave = volts_ave / NUM;

  if(volts_ave > 100){
    if((volts[count]*0.7) > volts_ave)  digitalWrite(SOLENOID_PIN,HIGH);
    else  digitalWrite(SOLENOID_PIN,LOW);
  }else{
    digitalWrite(SOLENOID_PIN,LOW);
  }

  Serial.print(volts_ave);
  Serial.print(",");
  Serial.println(volts[count]*0.7);
  
  count++;
  count = count%NUM;
}
