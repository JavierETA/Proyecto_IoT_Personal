/*! @file : sensor_luz.h
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_SENSOR_LUZ_H_
#define IOT_SDK_PERIPHERALS_SENSOR_LUZ_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup sensor de luz
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define SenLuz_ADC16_BASE          ADC0
#define SenLuz_ADC16_CHANNEL_GROUP 0U
#define SenLuz_ADC16_USER_CHANNEL  3U /* PTE30, ADC0_SE23 */
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
//-----------------------------------------------------------------------------
 //Returna el resultado ADC del sensor de luz
 float SenLuzObtenerDatoLux(void);

/** @} */ // end of sensor de luz group
/** @} */ // end of PERIPHERALS group

#endif /* IOT_SDK_PERIPHERALS_SENSOR_LUZ_H_ */
