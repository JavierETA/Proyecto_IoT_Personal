/*! @file : irq_lpuart0.h
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    16/09/2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_IRQ_IRQ_LPUART0_H_
#define IOT_SDK_IRQ_IRQ_LPUART0_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup irq
 * @{
 */
/*!
 * @addtogroup lpuart0
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define RX_RING_BUFFER_SIZE 40
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
uint8_t sacarByteBuffCir();
uint32_t numerodebytedisponiblesenbuffer();
/** @} */ // end of lpuart0 group
/** @} */ // end of irq group

#endif /* IOT_SDK_IRQ_IRQ_LPUART0_H_ */