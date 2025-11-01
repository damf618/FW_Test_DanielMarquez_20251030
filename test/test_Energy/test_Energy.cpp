/*
 **===== Casos de Prueba ---¡COMPLETADAS!---=====
 * -- El sistema debe inicializar el sistema de energía en modo Low Energy.                                      [OK]
 **===== Casos de Prueba ---¡PENDIENTES!---=====
 * -- El sistema debe conmtar condiferentes tiempos de sleep en base a los niveles de energía disponibles.       [PENDING]
*/

/* ============================================================================
*                              Includes
* =========================================================================== */
#include <Arduino.h>
#include "unity.h"
#include <EnergySystem.h>

/* ============================================================================
*                              Data Types
* =========================================================================== */

/* ============================================================================
*                              Variables
* =========================================================================== */

extern energy_system_control_t energy_system;

/* ============================================================================
*                              Testing Functions
* =========================================================================== */

void setUp(void)
{
  EnergySystemInit();
}

void tearDown(void)
{
}

// Test para modos de control del sistema de ventilacion
void test_EnergyInit(void)
{
  EnergySystemInit();
  TEST_ASSERT_EQUAL_MESSAGE(Low_Energy_E,           energy_system.mode,         "Energy System Initial Mode Failed" );
  TEST_ASSERT_EQUAL_MESSAGE(LOW_ENERGY_SLEEP_TIME,  energy_system.sleep_time,   "Energy System Initial Sleep Time Failed");
  TEST_ASSERT_EQUAL_MESSAGE(true,                   EnergySystemInit(),         "Energy System Init Failed");
}

// Test para modos de control del sistema de ventilacion
void test_SleepConfig(void)
{
  TEST_ASSERT_EQUAL_MESSAGE(true, EnergySystemSetMode(Low_Energy_E), "Energy System Set Mode Failed for Low Energy Mode");
  EnergySystemUpdate();
  TEST_ASSERT_EQUAL_MESSAGE(LOW_ENERGY_SLEEP_TIME,  energy_system.sleep_time,   "Energy System Sleep Time Failed for Low Energy Mode");

  energy_system.mode = Regular_Energy_E;
  EnergySystemInit();
  TEST_ASSERT_EQUAL_MESSAGE(REG_ENERGY_SLEEP_TIME,  energy_system.sleep_time,   "Energy System Sleep Time Failed for Regular Energy Mode");

  energy_system.mode = High_Energy_E;
  EnergySystemInit();
  TEST_ASSERT_EQUAL_MESSAGE(HIGH_ENERGY_SLEEP_TIME,  energy_system.sleep_time,   "Energy System Sleep Time Failed for High Energy Mode");
}


/* ============================================================================
*                              Test Hardware Execution
* =========================================================================== */
int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_EnergyInit);
  RUN_TESTS(test_SleepConfig);
  return UNITY_END();
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}