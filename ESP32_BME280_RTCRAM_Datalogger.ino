#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

RTC_DATA_ATTR int readingCnt = 0;

typedef struct {
  float Temp;
  int   Humi;
  float Pres;
} sensorReadings;

#define maximumReadings 290 // The maximum number of readings that can be stored in the available space
#define sleeptimeSecs   600 // Every 10-mins of sleep 10 x 60-secs

RTC_DATA_ATTR sensorReadings Readings[maximumReadings];

Adafruit_BME280 bme; // Assumes I2C connection, so connect BME280 Vcc to 3.3v, Gnd to Gnd, SDA to SDA, SCL to SCL

void setup() { // At sleep wake-up programme starts from here!
  Serial.begin(115200);
  Serial.println(SDA);
  Serial.println(SCL);
  // default settings
  bool status = true; //bme.begin();
  // You can also pass in a Wire library object like &Wire2, like this status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
  }
  Serial.println(readingCnt); // To show ESP32 is awake!
  Readings[readingCnt].Temp = bme.readTemperature();       // Units °C
  Readings[readingCnt].Humi = bme.readHumidity();          // Units % RH
  Readings[readingCnt].Pres = bme.readPressure() / 100.0F; // Units hPa
  readingCnt = readingCnt + 1;
  if (readingCnt >= maximumReadings) {
    for (int r = 0; r < maximumReadings; r++){
      // Now output readings in CSV format to the serial port
      Serial.println(String(r)+","+String(Readings[r].Temp)+","+String(Readings[r].Humi)+","+String(Readings[r].Pres));
    }
    readingCnt = 0; // Reset counter
  }
  // Now go to sleep
  esp_sleep_enable_timer_wakeup(sleeptimeSecs * 1000000);
  esp_deep_sleep_start();
}

void loop() {

}

/* Example output after 10-readings
0,20.50,50,1001.10
1,20.50,50,1001.10
2,20.70,51,1001.20
3,20.80,50,1001.20
4,20.70,51,1001.30
5,20.70,51,1001.30
6,20.70,51,1001.30
7,20.80,51,1001.40
8,20.80,51,1001.40
9,20.90,51,1001.40
*/
