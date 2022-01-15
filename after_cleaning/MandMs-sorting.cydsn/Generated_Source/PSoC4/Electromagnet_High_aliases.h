/*******************************************************************************
* File Name: Electromagnet_High.h  
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

#if !defined(CY_PINS_Electromagnet_High_ALIASES_H) /* Pins Electromagnet_High_ALIASES_H */
#define CY_PINS_Electromagnet_High_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Electromagnet_High_0			(Electromagnet_High__0__PC)
#define Electromagnet_High_0_PS		(Electromagnet_High__0__PS)
#define Electromagnet_High_0_PC		(Electromagnet_High__0__PC)
#define Electromagnet_High_0_DR		(Electromagnet_High__0__DR)
#define Electromagnet_High_0_SHIFT	(Electromagnet_High__0__SHIFT)
#define Electromagnet_High_0_INTR	((uint16)((uint16)0x0003u << (Electromagnet_High__0__SHIFT*2u)))

#define Electromagnet_High_INTR_ALL	 ((uint16)(Electromagnet_High_0_INTR))


#endif /* End Pins Electromagnet_High_ALIASES_H */


/* [] END OF FILE */
