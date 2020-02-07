#ifndef STUSB4500_H
#define STUSB4500_H

#include <stdbool.h>

// User adjustable parameters
#define PDO_CURRENT_MIN 3000  // mA, 25mA increments
#define PDO_VOLTAGE_MIN 5000  // mV, 50mV increments
#define PDO_VOLTAGE_MAX 12000 // mV, 50mV increments

bool stusb_negotiate(void);

#endif // STUSB4500_H