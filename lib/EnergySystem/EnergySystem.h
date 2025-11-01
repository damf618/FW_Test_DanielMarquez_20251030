/* ============================================================================
*                              Information
* =========================================================================== */



 //#pragma once
#ifndef ENERGY_SYSTEM_H_
#define ENERGY_SYSTEM_H_
/* ============================================================================
*                              Includes
* =========================================================================== */

#include <stdint.h>



// Si se compila como C++
#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
*                              Defines
* =========================================================================== */

#define DEFAULT_ENERGY_MODE          Low_Energy_E
#define DEFAULT_ENERGY_SLEEP_MODE    LOW_ENERGY_SLEEP_TIME

#define LOW_ENERGY_SLEEP_TIME        2000
#define REG_ENERGY_SLEEP_TIME        1000
#define HIGH_ENERGY_SLEEP_TIME       500


/* ============================================================================
*                              Data Types
* =========================================================================== */

typedef enum energy_system_mode {
	Low_Energy_E=0,
	Regular_Energy_E,
    High_Energy_E,
	kNumberOfEnergyModes
} energy_system_mode_e;

typedef struct energy_system_control_s {
	energy_system_mode_e mode;
    uint16_t  sleep_time;
} energy_system_control_t;


/* ============================================================================
*                              Prototypes
* =========================================================================== */

/**
 * @brief  Inits the energy management system.
 */
uint8_t EnergySystemInit(void);

/**
 * @brief   Set the energy management system mode.
 */
uint8_t EnergySystemSetMode(energy_system_mode_e mode);

/**
 * @brief   Update the energy management system.
 */
void EnergySystemUpdate(void);

 // Si se compila como C++
#ifdef __cplusplus
} // fin de extern "C"
#endif

#endif /* ENERGY_SYSTEM_H_ */