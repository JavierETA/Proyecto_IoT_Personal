/*! @file : leds.c
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    8/09/2021
 * @brief   Driver para controlar leds de tarjeta FRDM-K32L2B3
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "leds.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 void led_on_green(){
	 //encender led verde
	 GPIO_PinWrite(GPIOD,5,0);
 }
 
 void led_off_green(){
	 //apagar led verde
	 GPIO_PinWrite(GPIOD,5,1);
 }