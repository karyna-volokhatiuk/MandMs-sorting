/*******************************************************************************
* File Name: Motor_High.c  
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
#include "Motor_High.h"

static Motor_High_BACKUP_STRUCT  Motor_High_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Motor_High_Sleep
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
*  \snippet Motor_High_SUT.c usage_Motor_High_Sleep_Wakeup
*******************************************************************************/
void Motor_High_Sleep(void)
{
    #if defined(Motor_High__PC)
        Motor_High_backup.pcState = Motor_High_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Motor_High_backup.usbState = Motor_High_CR1_REG;
            Motor_High_USB_POWER_REG |= Motor_High_USBIO_ENTER_SLEEP;
            Motor_High_CR1_REG &= Motor_High_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Motor_High__SIO)
        Motor_High_backup.sioState = Motor_High_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Motor_High_SIO_REG &= (uint32)(~Motor_High_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Motor_High_Wakeup
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
*  Refer to Motor_High_Sleep() for an example usage.
*******************************************************************************/
void Motor_High_Wakeup(void)
{
    #if defined(Motor_High__PC)
        Motor_High_PC = Motor_High_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Motor_High_USB_POWER_REG &= Motor_High_USBIO_EXIT_SLEEP_PH1;
            Motor_High_CR1_REG = Motor_High_backup.usbState;
            Motor_High_USB_POWER_REG &= Motor_High_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Motor_High__SIO)
        Motor_High_SIO_REG = Motor_High_backup.sioState;
    #endif
}


/* [] END OF FILE */
