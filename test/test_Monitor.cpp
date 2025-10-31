/*
 **===== Casos de Prueba ---¡COMPLETADAS!---=====
 *  -- El sistema debe activar el modo de control de la temperatura en un rango determinado, para ahorrar bateria. [OK]

 **===== Casos de Prueba ---¡PENDIENTES!---=====
 *  -- El sistema en caso de estar por debajo del rango determinado, debe:
 *     - Apagar el ventilador por completo.
 *     - Tener la posibilidad de entrar en modo de bajo consumo.
 *  -- El sistema debe indicar mediante el puerto serie mensajes que permitan identificar:
 *     - El modo de trabajo según la temperatura.
 *     - La temperatura medida.
 *     - El Duty Cycle aplicado al ventilador.
 *  -- El sistema debe tener la posibilidad de configurar:
 *     - Valor minimo de PWM para el ventilador, una vez que la temperatura se encuentra en el rango de control.
 *     - Valor maximo de PWM para el ventilador, una vez que la temperatura se encuentra en el rango de control.
 *     - Rango de temperatura para el control del ventilador.
 *     - Histeresis para evitar oscilaciones continuas del ventilador.
 *     - Intervalo de tiempo para la lectura de la temperatura y actualizacion del PWM.
 *     - Modo de control: Manual o Automatico.
 *  -- El sistema al sobrepasar el rango de temperatura debe:
 *     - Activar el ventilador al 100% de su capacidad.
 *  -- El sistema debe indicar mediante un LED el valor de PWM aplicado al ventilador.
 *
*/
/* ============================================================================
*                              Includes
* =========================================================================== */
#include <Arduino.h>
#include "unity.h"
#include <MonitorSystem.h>

/* ============================================================================
*                              Data Types
* =========================================================================== */
typedef struct ControlModeTestCases_s
{
  int16_t temp;                             // Temperature to set for the test case
  monitor_system_mode_e expected_mode;      // Mode expected after setting the temperature
}ControlModeTestCases_t;

ControlModeTestCases_t control_mode_testcases[] =
{
  { -50,  OutOfRange_M   },   // Below minimum temperature
  {  80,  OutOfRange_M   },   // Above maximum temperature
  //{  20,  ControlRange_M },   // Low Limit temperature
  //{  45,  OutOfRange_M   },   // High Limit temperature
  {  30,  ControlRange_M },   // Regular temperature
};

/* ============================================================================
*                              Variables
* =========================================================================== */
extern monitor_system_mode_t monitor_system;

/* ============================================================================
*                              Testing Functions
* =========================================================================== */
void setUp(void)
{
  MonitorSystemInit();
}

void tearDown(void)
{
}

// Test para modos de control del sistema de ventilacion
void test_MonitorInit(void)
{
    TEST_ASSERT_EQUAL_MESSAGE(true, MonitorSystemInit(),                               "Monitor System Init Failed");
    TEST_ASSERT_EQUAL_MESSAGE(OutOfRange_M,             monitor_system.mode,           "Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(MIN_PWM_VALUE,            monitor_system.pwm_value ,     "Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(DEFAULT_INIT_TEMP,        monitor_system.temp ,          "Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(DEFAULT_HYSTERESIS,       monitor_system.hysteresis ,    "Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(DEFAULT_TEMP_RANGE_MIN,   monitor_system.temp_range_min ,"Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(DEFAULT_TEMP_RANGE_MAX,   monitor_system.temp_range_max ,"Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(LOW_PWM_VALUE,            monitor_system.pwm_min ,       "Initial Mode parameter incorrect");
    TEST_ASSERT_EQUAL_MESSAGE(HIGH_PWM_VALUE,           monitor_system.pwm_max ,       "Initial Mode parameter incorrect");
}


// Test para modos de control del sistema de ventilacion
void test_ControlModes(void)
{
    uint8_t n_cases = sizeof(control_mode_testcases)/sizeof(control_mode_testcases[0]);
    char Text_ID[50];

    for(uint8_t i=0;i<n_cases;i++)
    {
      sprintf(Text_ID,"Error en caso de Prueba Nro: %d",i);
      TEST_ASSERT_EQUAL_MESSAGE(true,setMonitorSystemTemp(control_mode_testcases[i].temp),"Temp Out of Range");
      MonitorSystemUpdate();
      TEST_ASSERT_EQUAL_MESSAGE(control_mode_testcases[i].expected_mode, monitor_system.mode, Text_ID);
    }
}

// Test para validar el modo manual
void test_ManualMode(void)
{
  // Set Manual Mode to set PWM at MAX Value
  setMonitorSystemManualMode();
  MonitorSystemUpdate();
  TEST_ASSERT_EQUAL_MESSAGE(MAX_PWM_VALUE, monitor_system.pwm_value, "PWM Value not at MAX in Manual Mode");

  // Clear Manual Mode
  clearMonitorSystemManualMode();
  TEST_ASSERT_EQUAL_MESSAGE(true,setMonitorSystemTemp(0),"Temp Out of Range");
  MonitorSystemUpdate();
  TEST_ASSERT_EQUAL_MESSAGE(MIN_PWM_VALUE, monitor_system.pwm_value, "PWM Value at MAX in Manual Mode");
}

// Test para el apagado del ventilador en caso de baja temperatura
void test_HighTemperature(void)
{
  // Set Temp High to set PWM in a value different than 0
  TEST_ASSERT_EQUAL_MESSAGE(true,setMonitorSystemTemp(DEFAULT_TEMP_RANGE_MAX),"Temp Out of Range");
  MonitorSystemUpdate();
  TEST_ASSERT_EQUAL_MESSAGE(MAX_PWM_VALUE, monitor_system.pwm_value, "PWM Value at MAX in Manual Mode");
}

// Test para el apagado del ventilador en caso de baja temperatura
void test_LowTemperature(void)
{
  // Set Temp High to set PWM in a value different than 0
  TEST_ASSERT_EQUAL_MESSAGE(true,setMonitorSystemTemp(DEFAULT_TEMP_RANGE_MAX+5),"Temp Out of Range");
  MonitorSystemUpdate();
  TEST_ASSERT_EQUAL_MESSAGE(MAX_PWM_VALUE, monitor_system.pwm_value, "PWM Value at MAX in Manual Mode");

  TEST_ASSERT_EQUAL_MESSAGE(true,setMonitorSystemTemp(DEFAULT_TEMP_RANGE_MIN-10),"Temperature Out of Range");
  MonitorSystemUpdate();
  TEST_ASSERT_EQUAL_MESSAGE(MIN_PWM_VALUE, monitor_system.pwm_value, "PWM Value incorrect for Low Temp");
}

/* ============================================================================
*                              Test Hardware Execution
* =========================================================================== */
int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_MonitorInit);
  RUN_TEST(test_ControlModes);
  RUN_TEST(test_ManualMode);
  RUN_TEST(test_HighTemperature);
  RUN_TEST(test_LowTemperature);
  return UNITY_END();
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}