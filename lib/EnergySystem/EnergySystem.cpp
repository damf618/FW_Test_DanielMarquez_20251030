/* ============================================================================
*                              Information
* =========================================================================== */
/* Energy Monitor source file.
*  Provides the implementation and private prototypes for the Energy System module.
*  This module is responsible for monitoring temperature and controlling PWM outputs
*  for cooling fans based on defined temperature ranges and modes of operation.

/* ============================================================================
*                              Includes
* =========================================================================== */

#include <EnergySystem.h>

/* ============================================================================
*                              Defines
* =========================================================================== */


/* ============================================================================
*                              Variables
* =========================================================================== */

energy_system_control_t energy_system;

/* ============================================================================
*                              Prototypes
* =========================================================================== */

/* ============================================================================
*                              Private Definitions
* =========================================================================== */

/* ============================================================================
*                              Public Definitions
* =========================================================================== */

uint8_t EnergySystemInit(void)
{
    energy_system.mode          = DEFAULT_ENERGY_MODE;
    energy_system.sleep_time    = DEFAULT_ENERGY_SLEEP_MODE;
    //TODO: We could verify here the initialization of related hardware components (adc, power modules, etc.)
    return true;
}

uint8_t EnergySystemSetMode(energy_system_mode_e mode)
{
    energy_system.mode = mode;
    switch(mode)
    {
        case Low_Energy_E:
            energy_system.sleep_time = LOW_ENERGY_SLEEP_TIME;
            break;
        case Regular_Energy_E:
            energy_system.sleep_time = REG_ENERGY_SLEEP_TIME;
            break;
        case High_Energy_E:
            energy_system.sleep_time = HIGH_ENERGY_SLEEP_TIME;
            break;
        default:
            return false; // Invalid mode
    }
    return true;
}

void EnergySystemUpdate(void)
{
    
}