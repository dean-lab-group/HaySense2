#pragma once
/*
HaySense library by Markus Kreitzer
*/

// This will load the definition for common Particle variable types.
#include "Particle.h"
#include "FreqPeriodCounter.h"

// All my defs
#define BATTERY_PIN A5  //Power from HaySense feather.
#define MOISTURE_PIN D4 //Pin on feather where moisture frequency is read.
#define TEMPERATURE_PIN D5 // Pin on feather where temperature frequency is read.
#define SENSOR_POWER_PIN D6  //Power line for actual sensors
#define POWER_ON_DELAY 10 // Delay before sensors are powered on.
#define TIMER_PERIOD 1000 // One second in milis

// This is your main class that users will import into their application
class HaySense
{
public:
  HaySense();
  // Eventually these "freq" methods will be private and the actual temp and
  // moisture readings will be the only thing that is public.
  float get_temperature_freq(void);
  float get_moisture_freq(void);
  void power_on_sensors(void);
  void power_off_sensors(void);
  void counterISR();

private:
  void detect_pulse(void);
  float get_battery_voltage(void);
  float convert_moisture(float temp_hz, float moist_hz, float calibration_values[4]);
  float convert_temperature(float temp_hz, float calibration_values[2]);
};
