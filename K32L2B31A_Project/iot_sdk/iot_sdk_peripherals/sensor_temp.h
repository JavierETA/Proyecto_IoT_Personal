/*! @file : sensor_temp.h
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para sensor de temperatura
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_SENSOR_TEMP_H_
#define IOT_SDK_PERIPHERALS_SENSOR_TEMP_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup periferico
 * @{
 */
/*!
 * @addtogroup sensor de temperatura
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define SenTemp_ADC16_BASE          ADC0
#define SenTemp_ADC16_CHANNEL_GROUP 0U
#define SenTemp_ADC16_USER_CHANNEL  26U
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
 //Returna el resultado ADC del sensor de temperatura
 float SenTempObtenerDatoCenti(void);
/** @} */ // end of sensor de temperatura group
/** @} */ // end of periferico group

#endif /* IOT_SDK_PERIPHERALS_SENSOR_TEMP_H_ */
