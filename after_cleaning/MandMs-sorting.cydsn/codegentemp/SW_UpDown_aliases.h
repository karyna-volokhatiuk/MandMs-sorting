/*******************************************************************************
* File Name: SW_UpDown.h  
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

#if !defined(CY_PINS_SW_UpDown_ALIASES_H) /* Pins SW_UpDown_ALIASES_H */
#define CY_PINS_SW_UpDown_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SW_UpDown_0			(SW_UpDown__0__PC)
#define SW_UpDown_0_PS		(SW_UpDown__0__PS)
#define SW_UpDown_0_PC		(SW_UpDown__0__PC)
#define SW_UpDown_0_DR		(SW_UpDown__0__DR)
#define SW_UpDown_0_SHIFT	(SW_UpDown__0__SHIFT)
#define SW_UpDown_0_INTR	((uint16)((uint16)0x0003u << (SW_UpDown__0__SHIFT*2u)))

#define SW_UpDown_INTR_ALL	 ((uint16)(SW_UpDown_0_INTR))


#endif /* End Pins SW_UpDown_ALIASES_H */


/* [] END OF FILE */
