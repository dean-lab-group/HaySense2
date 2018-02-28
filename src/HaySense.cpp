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

void HaySense::power_on_sensors(){
    Log.trace("Powering on sensors");
    // Turns on sensors (sensors are active-low)
    pinResetFast(SENSOR_POWER_PIN);
}

void HaySense::power_off_sensors(){
    pinSetFast(SENSOR_POWER_PIN); //turn off sensors
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

Converter::Converter(float *moist_constants, float *temp_constants){
    moisture_constants = moist_constants;
    temperature_constants = temp_constants;
}

float Converter::GetTemperature(float temp_hz){
    Log.trace("Converting temperature.");
    temperature_hz = temp_hz;
	return temperature_constants[0] * temp_hz + temperature_constants[1];
}

float Converter::GetMoisture(float temp_hz, float moist_hz){
    Log.trace("Converting moisture.");
    float temperature_hz = temp_hz;
	return moist_hz * slope_prime() + intercept_prime();
}

float Converter::intercept_prime(void){
    float ip = -slope_prime() * y_0();
    Log.trace("intercept_prime: %f", ip);
    return ip;
}

float Converter::slope_prime(void){
    float sp = -100/(y_0() - y_100());
    Log.trace("slope_prime: %f", sp);
    return sp;
}
float Converter::y_100(void){
	float y100 = moisture_constants[2] * temperature_hz + moisture_constants[3];
    Log.trace("y_100: %f", y100);
    return y100;
}

float Converter::y_0(void){
	float y0 = moisture_constants[0] * temperature_hz + moisture_constants[1];
    Log.trace("y_0: %f", y0);
    return y0;
}

/*
% Solution
y_0 (varies, see below)
y_100 (varies, see below)
temp (varies, see below)
slope_prime=(100/(y_0-y_100)) % will be negative
intercept_prime=-slope*(y_0)  % will be positive
y_prime= x_prime*slope_prime + intercept_prime
y_0 = k1*xx + k2
y_100 = k3*xx + k4

HB_01	 3d0026001751353335323536
HB_02	 3b0050000c51353431383737	0.0045	6.5077
HB_03	 370031000f47353235303035	0.0044	7.6176	-0.2744	17645	0.979	109.22
HB_04	 300026000f47333530373233	0.0047	7.4616
HB_05	 34004a000e51353338363333	0.0041	10.407	-0.22	17838	0.9861	46.437
HB_06	 17002f001947333530373233	0.0040	11.112	-0.603	19203	0.9816	78.208
HB_07	 210030001347353236343033   0.0048	6.1549	-1.3092	22099	0.9858	50.6
HB_08	 210021000b47343432313031
HB_09	 27002c001247353236343033
HB_10	 2d002c000b47353235303037
HB_11	 1c002a001247353236343033
HB_12	 1f0041001347353236343033

*/
