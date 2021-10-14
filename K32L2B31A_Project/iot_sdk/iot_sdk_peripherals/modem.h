/*! @file : modem.h
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    12/10/2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_MODEM_H_
#define IOT_SDK_PERIPHERALS_MODEM_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/


/*!
 * @addtogroup X
 * @{
 */
/*!
 * @addtogroup X
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define TIME_WAIT_RTA_CMD 2 //[=] Segundos que espera una Respuesta del Modem
//despues de enviar un comando

#define Modem_Send_Cmd(comandoStr) printf(comandoStr)
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
// Incicializa variables y estado inicial del Modem
// configura y inicia proceso de enviar un primer mensaje
void Modem_Init(void);

// Funcion de estado estable
void Modem_Task_Run(void);


/** @} */ // end of X group
/** @} */ // end of X group

#endif /* IOT_SDK_PERIPHERALS_MODEM_H_ */
