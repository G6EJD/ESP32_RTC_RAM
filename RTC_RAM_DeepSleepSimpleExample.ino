RTC_DATA_ATTR int wakeupCnt = 0;

void setup(){ // At sleep wake-up programme starts from here!
  Serial.begin(115200);
  
  wakeupCnt = wakeupCnt + 1;
  
  Serial.println(wakeupCnt); // Note the value is preserved during sleep

  // Now go to sleep
  esp_sleep_enable_timer_wakeup(10 * 1000000);
  esp_deep_sleep_start();
}

void loop(){
  // This section will never run! 
}
