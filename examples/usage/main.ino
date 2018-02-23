#include "Particle.h"
#include "HaySense.h"

#define SERIAL_DELAY 10
HaySense hs;
SerialLogHandler logHandler(115200, LOG_LEVEL_ERROR);

void setup(void){
    Serial.begin(115200);
    // Need this here so the Particle can initialize itself properly. But not
    // neccesary.
    delay(SERIAL_DELAY);
    Serial.println("Serial Activated");
    // Turn power on to sensor's ocillator circuit. May need a delay after this
    // to wait for the oscillator to stabilize.
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
