/*******************************************************************************
* File Name: Timer_Dir_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Dir.h"

static Timer_Dir_backupStruct Timer_Dir_backup;


/*******************************************************************************
* Function Name: Timer_Dir_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Dir_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Dir_SaveConfig(void) 
{
    #if (!Timer_Dir_UsingFixedFunction)
        Timer_Dir_backup.TimerUdb = Timer_Dir_ReadCounter();
        Timer_Dir_backup.InterruptMaskValue = Timer_Dir_STATUS_MASK;
        #if (Timer_Dir_UsingHWCaptureCounter)
            Timer_Dir_backup.TimerCaptureCounter = Timer_Dir_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Dir_UDB_CONTROL_REG_REMOVED)
            Timer_Dir_backup.TimerControlRegister = Timer_Dir_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Dir_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Dir_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Dir_RestoreConfig(void) 
{   
    #if (!Timer_Dir_UsingFixedFunction)

        Timer_Dir_WriteCounter(Timer_Dir_backup.TimerUdb);
        Timer_Dir_STATUS_MASK =Timer_Dir_backup.InterruptMaskValue;
        #if (Timer_Dir_UsingHWCaptureCounter)
            Timer_Dir_SetCaptureCount(Timer_Dir_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Dir_UDB_CONTROL_REG_REMOVED)
            Timer_Dir_WriteControlRegister(Timer_Dir_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Dir_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Dir_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Dir_Sleep(void) 
{
    #if(!Timer_Dir_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Dir_CTRL_ENABLE == (Timer_Dir_CONTROL & Timer_Dir_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Dir_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Dir_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Dir_Stop();
    Timer_Dir_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Dir_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Dir_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Dir_Wakeup(void) 
{
    Timer_Dir_RestoreConfig();
    #if(!Timer_Dir_UDB_CONTROL_REG_REMOVED)
        if(Timer_Dir_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Dir_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
