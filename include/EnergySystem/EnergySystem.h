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

#define MSA_ON		0xFF
#define MSA_OFF		0x00



/* ============================================================================
*                              Data Types
* =========================================================================== */

typedef enum _msa_dio_type {
	kDIO_Input,
	kDIO_Output,
	kDIO_Version,
	kDIO_NumberOfTypes
} msa_dio_type_e;

typedef struct Version_Callback_Set_s{
    uint8_t var;
} Version_Callback_Set_t;





/* ============================================================================
*                              Prototypes
* =========================================================================== */




 // Si se compila como C++
#ifdef __cplusplus
} // fin de extern "C"
#endif

#endif /* ENERGY_SYSTEM_H_ */