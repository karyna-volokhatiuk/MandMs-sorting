/*******************************************************************************
* File Name: Motort_Low.h  
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

#if !defined(CY_PINS_Motort_Low_ALIASES_H) /* Pins Motort_Low_ALIASES_H */
#define CY_PINS_Motort_Low_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Motort_Low_0			(Motort_Low__0__PC)
#define Motort_Low_0_PS		(Motort_Low__0__PS)
#define Motort_Low_0_PC		(Motort_Low__0__PC)
#define Motort_Low_0_DR		(Motort_Low__0__DR)
#define Motort_Low_0_SHIFT	(Motort_Low__0__SHIFT)
#define Motort_Low_0_INTR	((uint16)((uint16)0x0003u << (Motort_Low__0__SHIFT*2u)))

#define Motort_Low_INTR_ALL	 ((uint16)(Motort_Low_0_INTR))


#endif /* End Pins Motort_Low_ALIASES_H */


/* [] END OF FILE */
