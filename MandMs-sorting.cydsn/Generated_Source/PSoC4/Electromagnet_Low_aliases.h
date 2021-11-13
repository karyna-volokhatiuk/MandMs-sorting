/*******************************************************************************
* File Name: Electromagnet_Low.h  
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

#if !defined(CY_PINS_Electromagnet_Low_ALIASES_H) /* Pins Electromagnet_Low_ALIASES_H */
#define CY_PINS_Electromagnet_Low_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Electromagnet_Low_0			(Electromagnet_Low__0__PC)
#define Electromagnet_Low_0_PS		(Electromagnet_Low__0__PS)
#define Electromagnet_Low_0_PC		(Electromagnet_Low__0__PC)
#define Electromagnet_Low_0_DR		(Electromagnet_Low__0__DR)
#define Electromagnet_Low_0_SHIFT	(Electromagnet_Low__0__SHIFT)
#define Electromagnet_Low_0_INTR	((uint16)((uint16)0x0003u << (Electromagnet_Low__0__SHIFT*2u)))

#define Electromagnet_Low_INTR_ALL	 ((uint16)(Electromagnet_Low_0_INTR))


#endif /* End Pins Electromagnet_Low_ALIASES_H */


/* [] END OF FILE */
