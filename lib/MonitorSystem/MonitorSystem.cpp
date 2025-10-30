/* ============================================================================
*                              Information
* =========================================================================== */
/* System Monitor source file.
*  Provides the implementation and private prototypes for the Monitor System module.
*  This module is responsible for monitoring temperature and controlling PWM outputs
*  for cooling fans based on defined temperature ranges and modes of operation.

/* ============================================================================
*                              Includes
* =========================================================================== */

#include <MonitorSystem.h>

/* ============================================================================
*                              Defines
* =========================================================================== */


/* ============================================================================
*                              Variables
* =========================================================================== */

monitor_system_mode_t monitor_system;



/* ============================================================================
*                              Prototypes
* =========================================================================== */



/* ============================================================================
*                              Definitions
* =========================================================================== */


uint8_t MonitorSystemInit(void)
{
    monitor_system.mode             = OutOfRange_M;
    monitor_system.pwm_value        = MIN_PWM_VALUE;
    monitor_system.temp             = DEFAULT_INIT_TEMP;
    monitor_system.hysteresis       = DEFAULT_HYSTERESIS;
    monitor_system.temp_range_min   = DEFAULT_TEMP_RANGE_MIN;
    monitor_system.temp_range_max   = DEFAULT_TEMP_RANGE_MAX;
    monitor_system.pwm_min          = LOW_PWM_VALUE;
    monitor_system.pwm_max          = HIGH_PWM_VALUE;
    return true;
}


