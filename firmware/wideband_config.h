#pragma once

// Fundamental board constants
#define VCC_VOLTS (3.3f)
#define HALF_VCC (VCC_VOLTS / 2)
#define ADC_MAX_COUNT (4095)
#define ADC_OVERSAMPLE 16

// *******************************
//    Nernst voltage & ESR sense
// *******************************
#define NERNST_INPUT_GAIN (1 / 2.7f)

// Nernst AC injection resistor value
#define ESR_SUPPLY_R (22000)

// *******************************
//       Pump current sense
// *******************************

#define PUMP_CURRENT_SENSE_GAIN (10)

// LSU sense resistor - 61.9 ohms
#define LSU_SENSE_R (61.9f)

// *******************************
//          Pump driver
// *******************************

// todo
