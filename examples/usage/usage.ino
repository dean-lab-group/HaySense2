// Example usage for HaySense library by Markus Kreitzer.

#include "HaySense.h"

// Initialize objects from the lib
HaySense haySense;

void setup() {
    // Call functions on initialized library objects that require hardware
    haySense.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    haySense.process();
}
