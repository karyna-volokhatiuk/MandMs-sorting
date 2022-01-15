/*******************************************************************************
* File Name: Step_2_5.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Step_2_5_H) /* Pins Step_2_5_H */
#define CY_PINS_Step_2_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Step_2_5_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Step_2_5_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Step_2_5_Read(void);
void    Step_2_5_Write(uint8 value);
uint8   Step_2_5_ReadDataReg(void);
#if defined(Step_2_5__PC) || (CY_PSOC4_4200L) 
    void    Step_2_5_SetDriveMode(uint8 mode);
#endif
void    Step_2_5_SetInterruptMode(uint16 position, uint16 mode);
uint8   Step_2_5_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Step_2_5_Sleep(void); 
void Step_2_5_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Step_2_5__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Step_2_5_DRIVE_MODE_BITS        (3)
    #define Step_2_5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Step_2_5_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Step_2_5_SetDriveMode() function.
         *  @{
         */
        #define Step_2_5_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Step_2_5_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Step_2_5_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Step_2_5_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Step_2_5_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Step_2_5_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Step_2_5_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Step_2_5_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Step_2_5_MASK               Step_2_5__MASK
#define Step_2_5_SHIFT              Step_2_5__SHIFT
#define Step_2_5_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Step_2_5_SetInterruptMode() function.
     *  @{
     */
        #define Step_2_5_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Step_2_5_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Step_2_5_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Step_2_5_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Step_2_5__SIO)
    #define Step_2_5_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Step_2_5__PC) && (CY_PSOC4_4200L)
    #define Step_2_5_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Step_2_5_USBIO_DISABLE              ((uint32)(~Step_2_5_USBIO_ENABLE))
    #define Step_2_5_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Step_2_5_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Step_2_5_USBIO_ENTER_SLEEP          ((uint32)((1u << Step_2_5_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Step_2_5_USBIO_SUSPEND_DEL_SHIFT)))
    #define Step_2_5_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Step_2_5_USBIO_SUSPEND_SHIFT)))
    #define Step_2_5_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Step_2_5_USBIO_SUSPEND_DEL_SHIFT)))
    #define Step_2_5_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Step_2_5__PC)
    /* Port Configuration */
    #define Step_2_5_PC                 (* (reg32 *) Step_2_5__PC)
#endif
/* Pin State */
#define Step_2_5_PS                     (* (reg32 *) Step_2_5__PS)
/* Data Register */
#define Step_2_5_DR                     (* (reg32 *) Step_2_5__DR)
/* Input Buffer Disable Override */
#define Step_2_5_INP_DIS                (* (reg32 *) Step_2_5__PC2)

/* Interrupt configuration Registers */
#define Step_2_5_INTCFG                 (* (reg32 *) Step_2_5__INTCFG)
#define Step_2_5_INTSTAT                (* (reg32 *) Step_2_5__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Step_2_5_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Step_2_5__SIO)
    #define Step_2_5_SIO_REG            (* (reg32 *) Step_2_5__SIO)
#endif /* (Step_2_5__SIO_CFG) */

/* USBIO registers */
#if !defined(Step_2_5__PC) && (CY_PSOC4_4200L)
    #define Step_2_5_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Step_2_5_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Step_2_5_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Step_2_5_DRIVE_MODE_SHIFT       (0x00u)
#define Step_2_5_DRIVE_MODE_MASK        (0x07u << Step_2_5_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Step_2_5_H */


/* [] END OF FILE */
