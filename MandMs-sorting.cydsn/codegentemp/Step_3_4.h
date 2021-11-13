/*******************************************************************************
* File Name: Step_3_4.h  
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

#if !defined(CY_PINS_Step_3_4_H) /* Pins Step_3_4_H */
#define CY_PINS_Step_3_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Step_3_4_aliases.h"


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
} Step_3_4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Step_3_4_Read(void);
void    Step_3_4_Write(uint8 value);
uint8   Step_3_4_ReadDataReg(void);
#if defined(Step_3_4__PC) || (CY_PSOC4_4200L) 
    void    Step_3_4_SetDriveMode(uint8 mode);
#endif
void    Step_3_4_SetInterruptMode(uint16 position, uint16 mode);
uint8   Step_3_4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Step_3_4_Sleep(void); 
void Step_3_4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Step_3_4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Step_3_4_DRIVE_MODE_BITS        (3)
    #define Step_3_4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Step_3_4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Step_3_4_SetDriveMode() function.
         *  @{
         */
        #define Step_3_4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Step_3_4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Step_3_4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Step_3_4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Step_3_4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Step_3_4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Step_3_4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Step_3_4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Step_3_4_MASK               Step_3_4__MASK
#define Step_3_4_SHIFT              Step_3_4__SHIFT
#define Step_3_4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Step_3_4_SetInterruptMode() function.
     *  @{
     */
        #define Step_3_4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Step_3_4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Step_3_4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Step_3_4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Step_3_4__SIO)
    #define Step_3_4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Step_3_4__PC) && (CY_PSOC4_4200L)
    #define Step_3_4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Step_3_4_USBIO_DISABLE              ((uint32)(~Step_3_4_USBIO_ENABLE))
    #define Step_3_4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Step_3_4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Step_3_4_USBIO_ENTER_SLEEP          ((uint32)((1u << Step_3_4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Step_3_4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Step_3_4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Step_3_4_USBIO_SUSPEND_SHIFT)))
    #define Step_3_4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Step_3_4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Step_3_4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Step_3_4__PC)
    /* Port Configuration */
    #define Step_3_4_PC                 (* (reg32 *) Step_3_4__PC)
#endif
/* Pin State */
#define Step_3_4_PS                     (* (reg32 *) Step_3_4__PS)
/* Data Register */
#define Step_3_4_DR                     (* (reg32 *) Step_3_4__DR)
/* Input Buffer Disable Override */
#define Step_3_4_INP_DIS                (* (reg32 *) Step_3_4__PC2)

/* Interrupt configuration Registers */
#define Step_3_4_INTCFG                 (* (reg32 *) Step_3_4__INTCFG)
#define Step_3_4_INTSTAT                (* (reg32 *) Step_3_4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Step_3_4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Step_3_4__SIO)
    #define Step_3_4_SIO_REG            (* (reg32 *) Step_3_4__SIO)
#endif /* (Step_3_4__SIO_CFG) */

/* USBIO registers */
#if !defined(Step_3_4__PC) && (CY_PSOC4_4200L)
    #define Step_3_4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Step_3_4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Step_3_4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Step_3_4_DRIVE_MODE_SHIFT       (0x00u)
#define Step_3_4_DRIVE_MODE_MASK        (0x07u << Step_3_4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Step_3_4_H */


/* [] END OF FILE */
