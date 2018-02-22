/* HaySense library by Markus Kreitzer
 */

#include "HaySense.h"

/**
 * Constructor.
 */
HaySense::HaySense()
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
}

/**
 * Example method.
 */
void HaySense::begin()
{
    // initialize hardware
    Serial.println("called begin");
}

/**
 * Example method.
 */
void HaySense::process()
{
    // do something useful
    Serial.println("called process");
    doit();
}

/**
* Example private method
*/
void HaySense::doit()
{
    Serial.println("called doit");
}
