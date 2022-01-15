/*******************************************************************************
* File Name: Motor_High.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Motor_High_ALIASES_H) /* Pins Motor_High_ALIASES_H */
#define CY_PINS_Motor_High_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Motor_High_0			(Motor_High__0__PC)
#define Motor_High_0_PS		(Motor_High__0__PS)
#define Motor_High_0_PC		(Motor_High__0__PC)
#define Motor_High_0_DR		(Motor_High__0__DR)
#define Motor_High_0_SHIFT	(Motor_High__0__SHIFT)
#define Motor_High_0_INTR	((uint16)((uint16)0x0003u << (Motor_High__0__SHIFT*2u)))

#define Motor_High_INTR_ALL	 ((uint16)(Motor_High_0_INTR))


#endif /* End Pins Motor_High_ALIASES_H */


/* [] END OF FILE */
