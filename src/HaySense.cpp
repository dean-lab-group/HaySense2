/* HaySense library by Markus Kreitzer
 */

#include "HaySense.h"
#include "Particle.h"

FreqPeriodCounter mycounter(MOISTURE_PIN, micros, 0);

HaySense::HaySense()
{
    pinMode(MOISTURE_PIN, INPUT_PULLDOWN);
    pinMode(TEMPERATURE_PIN, INPUT_PULLDOWN);
    pinMode(SENSOR_POWER_PIN, OUTPUT);
    attachInterrupt(MOISTURE_PIN, &HaySense::counterISR, this, CHANGE);
    power_on_sensors();
    // be sure not to call anything that requires hardware be initialized here,
    // put those in begin()
}

// Public
float HaySense::get_temperature(){
    Log.trace("Getting temperature.");
    // Dummy calibration values for now.
    float calibration_values[2] = {123.0, 321.1};
    return convert_temperature(get_temperature_freq(), calibration_values);
}

float HaySense::get_moisture(void){
    Log.trace("Getting moisture.");
    // Dummy calibration values for now.
    float calibration_values[4] = {123.0, 321.1, 432.1, 1235.1};
    return convert_moisture(get_temperature_freq(), get_moisture_freq(), calibration_values);
}

void HaySense::power_on_sensors(){
    Log.trace("Powering on sensors");
    // Turns on sensors (sensors are active-low)
    pinResetFast(SENSOR_POWER_PIN);
}

void HaySense::power_off_sensors(){
    pinSetFast(SENSOR_POWER_PIN); //turn off sensors
}

// Private
float HaySense::get_temperature_freq(void){
    Log.trace("Getting temperature frequency.");
    unsigned long temp_period_low = pulseIn(TEMPERATURE_PIN, LOW);
    unsigned long temp_period_high = pulseIn(TEMPERATURE_PIN, HIGH);
    return (1000000.0 * (1.0/(float)(temp_period_low + temp_period_high)));
}

float HaySense::get_moisture_freq(void){
    while(!mycounter.ready());
    return mycounter.hertz();
}

float HaySense::get_battery_voltage(void){
    Log.trace("Getting battery voltage.");
    // Funky math Andrew M. worked out to convert the analogRead value to the
    // proper battery voltage value.
    return (float)analogRead(BATTERY_PIN) * ((3.3*2.0)/(4095.0*0.914));
}

void HaySense::counterISR(){
	mycounter.poll();
}

float HaySense::convert_moisture(float temp_hz, float moist_hz, float calibration_values[4]){
    Log.trace("Converting moisture.");
	float y_0 = calibration_values[0]*temp_hz+calibration_values[1];
	float y_100 = calibration_values[2]*temp_hz + calibration_values[3];
	float slope_prime = (100/(y_0-y_100));
	float intercept_prime=-slope_prime*(y_0);
	return moist_hz*slope_prime + intercept_prime;
}

float HaySense::convert_temperature(float temp_hz, float calibration_values[2]){
    Log.trace("Converting temperature.");
	return calibration_values[0] * temp_hz + calibration_values[1];
}
