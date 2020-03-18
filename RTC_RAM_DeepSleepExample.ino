
RTC_DATA_ATTR int    integerExample = -1;
RTC_DATA_ATTR float  floatExample   = 2.141592654;
RTC_DATA_ATTR char   alphabet [26]  = "                         "; 
typedef struct{
    float Temp = 20;
    float Humi = 50;
    float Pres = 1000;
} sensorReadings;

RTC_DATA_ATTR sensorReadings Readings[50];

void setup(){ // At sleep wake-up programme starts from here!
  Serial.begin(115200);
  integerExample = integerExample + 1;
  floatExample++;
  alphabet[integerExample%26] = char(integerExample%26+65);
  Readings[0].Temp = Readings[0].Temp + 0.1;
  Readings[0].Humi = Readings[0].Humi + 0.1;
  Readings[0].Pres = Readings[0].Pres + 0.1;
  Readings[1].Temp = Readings[1].Temp + 0.2;
  Readings[1].Humi = Readings[1].Humi + 0.2;
  Readings[1].Pres = Readings[1].Pres + 0.2;

  Serial.println(integerExample);
  Serial.println(floatExample);
  Serial.println(alphabet);
  Serial.print(Readings[0].Temp);  Serial.print("\t");  Serial.println(Readings[1].Temp);
  Serial.print(Readings[0].Humi);  Serial.print("\t");  Serial.println(Readings[1].Humi);
  Serial.print(Readings[0].Pres);  Serial.print("\t");  Serial.println(Readings[1].Pres);

  // Now go to sleep
  esp_sleep_enable_timer_wakeup(10 * 1000000);
  esp_deep_sleep_start();
}

void loop(){
  
}
