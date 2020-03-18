# ESP32_RTC_RAM
How to use the ESP32 RTC RAM

The ESP32 has 8K of spare static RAM known as Real Time Clock Random Access Memory (Static RTC RAM), this can be used to save and retain variables during deep sleep.

For example, you can use the 8K of RAM to save up to 1000 readings from a sensor which could then be uploaded or retrieved later, the advantage of doing this is a reduction of power consumption as the ESP32 needs to wake, read the sensor and go back to sleep and it can do this usually in a few milli-seconds; typically 45mS, whereas uploading each reading to a server could take up to 2-Secs per reading or 45 times longer and that's for each reading uploaded!
