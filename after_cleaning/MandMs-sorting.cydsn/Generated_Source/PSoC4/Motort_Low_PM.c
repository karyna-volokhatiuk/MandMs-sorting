/*******************************************************************************
* File Name: Motort_Low.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Motort_Low.h"

static Motort_Low_BACKUP_STRUCT  Motort_Low_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Motort_Low_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Motort_Low_SUT.c usage_Motort_Low_Sleep_Wakeup
*******************************************************************************/
void Motort_Low_Sleep(void)
{
    #if defined(Motort_Low__PC)
        Motort_Low_backup.pcState = Motort_Low_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Motort_Low_backup.usbState = Motort_Low_CR1_REG;
            Motort_Low_USB_POWER_REG |= Motort_Low_USBIO_ENTER_SLEEP;
            Motort_Low_CR1_REG &= Motort_Low_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Motort_Low__SIO)
        Motort_Low_backup.sioState = Motort_Low_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Motort_Low_SIO_REG &= (uint32)(~Motort_Low_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Motort_Low_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Motort_Low_Sleep() for an example usage.
*******************************************************************************/
void Motort_Low_Wakeup(void)
{
    #if defined(Motort_Low__PC)
        Motort_Low_PC = Motort_Low_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Motort_Low_USB_POWER_REG &= Motort_Low_USBIO_EXIT_SLEEP_PH1;
            Motort_Low_CR1_REG = Motort_Low_backup.usbState;
            Motort_Low_USB_POWER_REG &= Motort_Low_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Motort_Low__SIO)
        Motort_Low_SIO_REG = Motort_Low_backup.sioState;
    #endif
}


/* [] END OF FILE */
