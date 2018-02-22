#include "Particle.h"
#include "HaySense.h"
#define SERIAL_DELAY 10
// SYSTEM_MODE(SEMI_AUTOMATIC); //disable automatic particle cloud connection
// SYSTEM_MODE(MANUAL); //disable automatic particle cloud connection
// SYSTEM_THREAD(ENABLED);
HaySense hs;
SerialLogHandler logHandler(115200, LOG_LEVEL_ERROR);

void setup(void){
    Serial.begin(115200);
    delay(SERIAL_DELAY);
    Serial.println("Serial Activated");
    hs.power_on_sensors();
}

void loop(void){
    Log.trace("Entering loop");
    // Get stuff. I need to move the stuff below to a class...
    float temperature_frequency = hs.get_temperature_freq();
    Log.trace(String(temperature_frequency));
    float moisture_frequency = hs.get_moisture_freq();
    Log.trace(String(moisture_frequency));

    // Print info to serial.
    Serial.print(temperature_frequency);
    Serial.print(", ");
    Serial.println(moisture_frequency);
    delay(500);
}
