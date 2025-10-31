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

// Temperature range check functions
static uint8_t isTempOutofRange(int16_t temp);
static uint8_t isTempLow(int16_t temp);
static uint8_t isTempHigh(int16_t temp);
static void setControlModeByTemp(int16_t temp);

/* ============================================================================
*                              Private Definitions
* =========================================================================== */

static uint8_t isTempOutofRange(int16_t temp)
{
    uint8_t rtn = false;

    if(temp < monitor_system.temp_range_min || temp >= monitor_system.temp_range_max)
    {
        rtn = true;
    }
    return rtn;
}

static uint8_t isTempLow(int16_t temp)
{
    uint8_t rtn = false;

    if(temp < monitor_system.temp_range_min)
    {
        rtn = true;
    }
    return rtn;
}

static uint8_t isTempHigh(int16_t temp)
{
    uint8_t rtn = false;

    if(temp >= monitor_system.temp_range_max)
    {
        rtn = true;
    }
    return rtn;
}

static void setControlModeByTemp(int16_t temp)
{
    if(isTempOutofRange(temp))
    {
        monitor_system.mode = OutOfRange_M;
    }
    else
    {
        monitor_system.mode = ControlRange_M;
    }
}

/* ============================================================================
*                              Public Definitions
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
    monitor_system.timer_goal       = UPDATE_EVENT_TIMER_GOAL;
    monitor_system.timer_counter    = 0;
    return true;
}

uint8_t setMonitorSystemTemp(int16_t temp)
{
    uint8_t rtn = false;
    if(temp > MIN_TEMP_VALUE || temp < MAX_TEMP_VALUE)
    {
        monitor_system.temp = temp;
        rtn =true;
    }
    return rtn;
}

void MonitorSystemUpdate(void)
{
    if(monitor_system.mode != Manual_M)
    {
        setControlModeByTemp(monitor_system.temp);
    }

    switch(monitor_system.mode)
    {
        case OutOfRange_M:
            //Execute out of range actions
            if(isTempLow(monitor_system.temp))
            {
                monitor_system.pwm_value = MIN_PWM_VALUE;
                //TODO: Set Energy Mode as High Consumption
            }
            else if(isTempHigh(monitor_system.temp))
            {
                monitor_system.pwm_value = MAX_PWM_VALUE;
                //TODO: Set Energy Mode as High Consumption
            }
            break;
        case ControlRange_M:
            // Simple linear control between min and max PWM based on temperature
            //TODO: Set Energy Mode as Regular Consumption
            break;
        case Manual_M:
            // In manual mode, PWM value is set to MAX value
            monitor_system.pwm_value = MAX_PWM_VALUE;
            //TODO: Set Energy Mode as High Consumption
            break;
        default:
            // Unknown mode, set PWM to minimum as a safe fallback
            monitor_system.pwm_value = MIN_PWM_VALUE;
            monitor_system.mode = OutOfRange_M;
            break;
    }
    //TODO: Update PWM output here based on monitor_system.pwm_value throuh HAL APIs
}

void clearMonitorSystemManualMode(void)
{
    monitor_system.mode = OutOfRange_M;
}

void setMonitorSystemManualMode(void)
{
    monitor_system.mode = Manual_M;
}
