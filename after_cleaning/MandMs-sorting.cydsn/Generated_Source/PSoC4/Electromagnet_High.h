/*******************************************************************************
* File Name: Electromagnet_High.h  
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

#if !defined(CY_PINS_Electromagnet_High_H) /* Pins Electromagnet_High_H */
#define CY_PINS_Electromagnet_High_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Electromagnet_High_aliases.h"


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
} Electromagnet_High_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Electromagnet_High_Read(void);
void    Electromagnet_High_Write(uint8 value);
uint8   Electromagnet_High_ReadDataReg(void);
#if defined(Electromagnet_High__PC) || (CY_PSOC4_4200L) 
    void    Electromagnet_High_SetDriveMode(uint8 mode);
#endif
void    Electromagnet_High_SetInterruptMode(uint16 position, uint16 mode);
uint8   Electromagnet_High_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Electromagnet_High_Sleep(void); 
void Electromagnet_High_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Electromagnet_High__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Electromagnet_High_DRIVE_MODE_BITS        (3)
    #define Electromagnet_High_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Electromagnet_High_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Electromagnet_High_SetDriveMode() function.
         *  @{
         */
        #define Electromagnet_High_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Electromagnet_High_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Electromagnet_High_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Electromagnet_High_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Electromagnet_High_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Electromagnet_High_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Electromagnet_High_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Electromagnet_High_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Electromagnet_High_MASK               Electromagnet_High__MASK
#define Electromagnet_High_SHIFT              Electromagnet_High__SHIFT
#define Electromagnet_High_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Electromagnet_High_SetInterruptMode() function.
     *  @{
     */
        #define Electromagnet_High_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Electromagnet_High_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Electromagnet_High_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Electromagnet_High_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Electromagnet_High__SIO)
    #define Electromagnet_High_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Electromagnet_High__PC) && (CY_PSOC4_4200L)
    #define Electromagnet_High_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Electromagnet_High_USBIO_DISABLE              ((uint32)(~Electromagnet_High_USBIO_ENABLE))
    #define Electromagnet_High_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Electromagnet_High_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Electromagnet_High_USBIO_ENTER_SLEEP          ((uint32)((1u << Electromagnet_High_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Electromagnet_High_USBIO_SUSPEND_DEL_SHIFT)))
    #define Electromagnet_High_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Electromagnet_High_USBIO_SUSPEND_SHIFT)))
    #define Electromagnet_High_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Electromagnet_High_USBIO_SUSPEND_DEL_SHIFT)))
    #define Electromagnet_High_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Electromagnet_High__PC)
    /* Port Configuration */
    #define Electromagnet_High_PC                 (* (reg32 *) Electromagnet_High__PC)
#endif
/* Pin State */
#define Electromagnet_High_PS                     (* (reg32 *) Electromagnet_High__PS)
/* Data Register */
#define Electromagnet_High_DR                     (* (reg32 *) Electromagnet_High__DR)
/* Input Buffer Disable Override */
#define Electromagnet_High_INP_DIS                (* (reg32 *) Electromagnet_High__PC2)

/* Interrupt configuration Registers */
#define Electromagnet_High_INTCFG                 (* (reg32 *) Electromagnet_High__INTCFG)
#define Electromagnet_High_INTSTAT                (* (reg32 *) Electromagnet_High__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Electromagnet_High_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Electromagnet_High__SIO)
    #define Electromagnet_High_SIO_REG            (* (reg32 *) Electromagnet_High__SIO)
#endif /* (Electromagnet_High__SIO_CFG) */

/* USBIO registers */
#if !defined(Electromagnet_High__PC) && (CY_PSOC4_4200L)
    #define Electromagnet_High_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Electromagnet_High_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Electromagnet_High_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Electromagnet_High_DRIVE_MODE_SHIFT       (0x00u)
#define Electromagnet_High_DRIVE_MODE_MASK        (0x07u << Electromagnet_High_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Electromagnet_High_H */


/* [] END OF FILE */
