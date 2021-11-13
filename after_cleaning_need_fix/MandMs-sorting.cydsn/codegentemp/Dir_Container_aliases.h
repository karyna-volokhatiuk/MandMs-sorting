/*******************************************************************************
* File Name: Dir_Container.h  
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

#if !defined(CY_PINS_Dir_Container_ALIASES_H) /* Pins Dir_Container_ALIASES_H */
#define CY_PINS_Dir_Container_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Dir_Container_0			(Dir_Container__0__PC)
#define Dir_Container_0_PS		(Dir_Container__0__PS)
#define Dir_Container_0_PC		(Dir_Container__0__PC)
#define Dir_Container_0_DR		(Dir_Container__0__DR)
#define Dir_Container_0_SHIFT	(Dir_Container__0__SHIFT)
#define Dir_Container_0_INTR	((uint16)((uint16)0x0003u << (Dir_Container__0__SHIFT*2u)))

#define Dir_Container_INTR_ALL	 ((uint16)(Dir_Container_0_INTR))


#endif /* End Pins Dir_Container_ALIASES_H */


/* [] END OF FILE */
