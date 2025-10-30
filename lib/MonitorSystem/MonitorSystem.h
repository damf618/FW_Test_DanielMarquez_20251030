/* ============================================================================
*                              Information
* =========================================================================== */
/* System Monitor header file.
*  Provides definitions and prototypes for the Monitor System module. This module
*  is responsible for monitoring temperature and controlling PWM outputs for cooling
*  fans based on defined temperature ranges and modes of operation.
*/


 //#pragma once
#ifndef MONITOR_SYSTEM_H_
#define MONITOR_SYSTEM_H_
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

#define MAX_PWM_VALUE           100
#define MIN_PWM_VALUE           0
#define DEFAULT_TEMP_RANGE_MIN  20  // degrees Celsius
#define DEFAULT_TEMP_RANGE_MAX  45  // degrees Celsius
#define DEFAULT_HYSTERESIS      5   // Grados Celsius
#define DEFAULT_INIT_TEMP       0   // Grados Celsius
#define HIGH_PWM_VALUE          80  // MAX Output PWM when in control range
#define LOW_PWM_VALUE           20  // MIN Output PWM when in control range

/* ============================================================================
*                              Data Types
* =========================================================================== */

typedef enum monitor_system_mode {
	OutOfRange_M=0,
	ControlRange_M,
    Manual_M,
	kDIO_NumberOfTypes
} monitor_system_mode_e;

typedef struct monitor_system_control {
	monitor_system_mode_e mode;
    uint8_t pwm_value;
    int16_t temp;
    uint8_t hysteresis;
    uint8_t temp_range_min;
    uint8_t temp_range_max;
    uint8_t pwm_min;
    uint8_t pwm_max;
} monitor_system_mode_t;


/* ============================================================================
*                              Prototypes
* =========================================================================== */

/***
 * \brief Inits the monitor system structure and related hardware.
 * \return 0 if OK, other value if error.
 */
uint8_t MonitorSystemInit(void);


 // Si se compila como C++
#ifdef __cplusplus
} // fin de extern "C"
#endif

#endif /* MONITOR_SYSTEM_H_ */