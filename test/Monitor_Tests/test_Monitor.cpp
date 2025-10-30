/*
 **===== Casos de Prueba ---¡COMPLETADAS!---=====
 *
 **===== Casos de Prueba ---¡PENDIENTES!---=====
 *  -- El sistema debe activar el modo de control de la temperatura en un rango determinado, para ahorrar bateria.
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

#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// Test para modos de control del sistema de ventilacion
void test_ControlModes(void)
{
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_ControlModes);
  return UNITY_END();
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}