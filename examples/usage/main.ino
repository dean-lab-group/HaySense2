#include "Particle.h"
#include "HaySense.h"

#define SERIAL_DELAY 10
SerialLogHandler logHandler(115200, LOG_LEVEL_ALL);
HaySense hs;
float moisture_calibration[] = {-0.2744, 17645, 0.979, 109.22};
float temperature_calibration[] = {0.0044, 7.6176};
Converter conv(moisture_calibration, temperature_calibration);

void setup(void){
    Serial.begin(115200);
    // Need this here so the Particle can initialize itself properly. But not
    // neccesary.
    delay(SERIAL_DELAY);
    Serial.println("Serial Activated");
    // Turn power on to sensor's ocillator circuit. May need a delay after this
    // to wait for the oscillator to stabilize.
    // hs.power_on_sensors();
}

void loop(void){
    Log.trace("Entering loop");
    // Get stuff. I need to move the stuff below to a class...
    float temp_freq = hs.get_temperature_freq();
    float moist_freq = hs.get_moisture_freq();
    float temperature = conv.GetTemperature(temp_freq);
    float moisture = conv.GetMoisture(temp_freq, moist_freq);
    Log.trace(String(moisture));

    // Print info to serial.
    Serial.println("{temperature_c: " + String(temperature) + ", temperature_hz: " + String(temp_freq) + "}");
    Serial.println("{moisture_perc: " + String(moisture) + ", moisture_hz: " + String(moist_freq) + "}");
    //Serial.println(moisture);
    delay(1000);
}
