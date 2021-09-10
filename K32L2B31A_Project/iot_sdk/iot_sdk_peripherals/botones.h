/*! @file : botones.h
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para controlar los botones
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_BOTONES_H_
#define IOT_SDK_PERIPHERALS_BOTONES_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"
#include "fsl_gpio.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup botones
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
bool boton1LeerEstado(void);
bool boton2LeerEstado(void);
/** @} */ // end of botones group
/** @} */ // end of PERIPHERALS group

#endif /* IOT_SDK_PERIPHERALS_BOTONES_H_ */
