/**
  ******************************************************************************
  * @file    user_debug.c
  * @author  Tai-Action SD Team
  * @brief   This file provides the Debug User Config Method.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "dbg/user_debug.h"


/** @defgroup TAE_Utilities TAE Utilities
  * @brief    TAE Utilities
  * @{
  */

/** @defgroup User_Debug User Debug
  * @brief    User Debug
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/** @defgroup User_Debug_Private_Constants User Debug Private Constants
  * @brief    User Debug Private Constants
  * @{
  */

/**
  * @brief C lib stdio.h putchar/getchar interface retarget
  * @note  With GCC/RAISONANCE, small DBG_NOR (option LD Linker->Libraries->Small DBG_NOR set to 'Yes') calls these functions
  */
#if   defined (__CC_ARM)                                        /*!< AC5 Compiler */

    #define PUTCHAR_PROTOTYPE           int fputc(int ch, FILE *f)
    #define GETCHAR_PROTOTYPE           int fgetc(FILE *f)

#elif defined (__ICCARM__)                                      /*!< IAR Compiler */

    #define PUTCHAR_PROTOTYPE           size_t __write(int handle, const unsigned char *buffer, size_t size)
    #define GETCHAR_PROTOTYPE           size_t __read(int handle, unsigned char *buffer, size_t size)

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */

    #define PUTCHAR_PROTOTYPE           int fputc(int ch, FILE *f)
    #define GETCHAR_PROTOTYPE           int fgetc(FILE *f)

#elif defined (__GNUC__)                                        /*!< GCC Compiler */

    #define PUTCHAR_PROTOTYPE           int _write(int fd, char *pBuffer, int size)
    #define GETCHAR_PROTOTYPE           int _read(int fd, char *pBuffer, int size)

#else

    #error "Not supported compiler type"

#endif

/**
  * @}
  */


/* Private Types -------------------------------------------------------------*/
/** @defgroup User_Debug_Private_Types User Debug Private Types
  * @brief    User Debug Private Types
  * @{
  */

/**
  * @brief C lib stdio.h __FILE struct definition for KEIL Compiler
  */
#if defined(__CC_ARM)
#pragma import(__use_no_semihosting_swi)
struct __FILE {
    int handle;
    /* Add whatever you need here */
};
#endif

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup User_Debug_Private_Variables User Debug Private Variables
  * @brief    User Debug Private Variables
  * @{
  */
//#if defined(__CC_ARM) || defined(__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
    /**
    * @brief C lib stdio.h __stdout FILE stream definition
    */
    FILE __stdout;

    /**
    * @brief C lib stdio.h __stdin FILE stream definition
    */
    FILE __stdin;

    /**
    * @brief C lib stdio.h __stderr FILE stream definition
    */
    //FILE __stderr;
#endif

/**
  * @brief user debug interface
  */
USER_DBG_IfcETypeDef user_dbg_ifc;

/**
  * @brief user debug ITM Rx buffer
  */
volatile int32_t ITM_RxBuffer;

#if defined(UART0) || defined(UART1) || defined(UART2)  || defined(UART3)  || defined(UART4) 
/**
* @brief user debug uart instance
*/
UART_TypeDef *user_dbg_uart_ins;
#endif

#if (defined(HAL_UART_MODULE_ENABLED) && (HAL_UART_MODULE_ENABLED == 1))
/**
* @brief user debug uart handle
*/
HAL_UART_HandleTypeDef huart = {0};
#endif

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup User_Debug_Exported_Functions User Debug Exported Functions
  * @brief    User Debug Exported Functions
  * @{
  */


/**
  * @brief  User Debug Init
  * @note   Remember to implement the HAL_UART_MspInit interface in the user file if use UART as debug interface
  * @param  ifc User debug interface
  * @return 0:OK -1:ERROR
  */
uint32_t User_Debug_Init(USER_DBG_IfcETypeDef ifc)
{
    uint32_t ret = 0;
    const uint32_t baudrate = 115200;
    uint32_t baud_rate_tmp;

    //Check ifc to be Valid
    if (ifc == USER_DBG_IFC_NO) {
        user_dbg_ifc = USER_DBG_IFC_NO;
        user_dbg_uart_ins = NULL;
        return 0;
    }

    //User Debug Interface Init
    if (ifc == USER_DBG_IFC_ITM) {
        //SWO GPIO Init: PB3

        LL_GPIO_SetIntMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_INT_MODE_CLOSE);
        LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL);
        LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_NO);
        LL_GPIO_SetAFPin(GPIOB, LL_GPIO_PIN_3, LL_GPIO_AF_2);

        user_dbg_ifc = ifc;
    } else {

        UART_TypeDef *uart_ins_temp = NULL;

        if (ifc == USER_DBG_IFC_UART0) {
            uart_ins_temp = UART0;

            //UART0 Pinmux Config: PB12(RX) & PC5(TX)
            LL_GPIO_SetIntMode(GPIOB, LL_GPIO_PIN_12, LL_GPIO_INT_MODE_CLOSE);
            LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_12, LL_GPIO_PULL_UP);
            LL_GPIO_SetAFPin(GPIOB, LL_GPIO_PIN_12, LL_GPIO_AF_5);

            LL_GPIO_SetIntMode(GPIOC, LL_GPIO_PIN_5, LL_GPIO_INT_MODE_CLOSE);
            LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_5, LL_GPIO_PULL_UP);
            LL_GPIO_SetAFPin(GPIOC, LL_GPIO_PIN_5, LL_GPIO_AF_5);

            //UART0 Bus Clock Enable and Soft Reset Release
            LL_RCU_RegWrite_Unlock(RCU);
            LL_RCU_APB0_EnableUART0Clock(RCU);
            LL_RCU_APB0_ForceResetUART0(RCU);
			LL_RCU_APB0_ReleaseResetUART0(RCU);
            LL_RCU_RegWrite_Lock(RCU);

        } else if (ifc == USER_DBG_IFC_UART1) {
            uart_ins_temp = UART1;

            //UART1 Pinmux Config: PA7(RX) & PA8(TX)
            LL_GPIO_SetIntMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_INT_MODE_CLOSE);
            LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);
            LL_GPIO_SetAFPin(GPIOA, LL_GPIO_PIN_7, LL_GPIO_AF_6);

            LL_GPIO_SetIntMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_INT_MODE_CLOSE);
            LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_8, LL_GPIO_PULL_UP);
            LL_GPIO_SetAFPin(GPIOA, LL_GPIO_PIN_8, LL_GPIO_AF_6);

            //UART1 Bus Clock Enable and Soft Reset Release
            LL_RCU_RegWrite_Unlock(RCU);
            LL_RCU_APB0_EnableUART1Clock(RCU);
            LL_RCU_APB0_ForceResetUART1(RCU);
			LL_RCU_APB0_ReleaseResetUART1(RCU);
            LL_RCU_RegWrite_Lock(RCU);

        } else if (ifc == USER_DBG_IFC_UART2) {
            uart_ins_temp = UART2;
            return -1;///TODO
        } else if (ifc == USER_DBG_IFC_UART3) {
            uart_ins_temp = UART3;
            return -1;///TODO
        } else if (ifc == USER_DBG_IFC_UART4) {
            uart_ins_temp = UART4;
            return -1;///TODO
        } else {
            return -1;
        }

        LL_UART_Disable(uart_ins_temp);

        LL_UART_ResetTxFIFO(uart_ins_temp);
        LL_UART_ResetRxFIFO(uart_ins_temp);

        LL_UART_SetParity(uart_ins_temp, LL_UART_PARITY_NONE);
        LL_UART_SetStopBitsLength(uart_ins_temp, LL_UART_STOPBITS_1);
        LL_UART_SetDataWidth(uart_ins_temp, LL_UART_DATAWIDTH_8B);

        LL_UART_DisableExtBit(uart_ins_temp);

        //Baudrate Config
        if (uart_ins_temp == UART0 || uart_ins_temp == UART1 || uart_ins_temp == UART2) {
            baud_rate_tmp = ((SystemCoreClockGet() / LL_RCU_GetAHBPrescaler(RCU) / LL_RCU_GetAPB0Prescaler(RCU)) + baudrate / 2) / baudrate;
        } else if (uart_ins_temp == UART3 || uart_ins_temp == UART4) {
            baud_rate_tmp = ((SystemCoreClockGet() / LL_RCU_GetAHBPrescaler(RCU) / LL_RCU_GetAPB1Prescaler(RCU)) + baudrate / 2) / baudrate;
        } else {
            return ret;
        }

        LL_UART_SetBaudRate(uart_ins_temp, baud_rate_tmp);
        LL_UART_SetOverSampling(uart_ins_temp, LL_UART_OVERSAMPLING_16);

        //All Interrupt Pending Clear
        LL_UART_ClearFlag_All(uart_ins_temp);

        //TX/RX Enable
        LL_UART_EnableDirectionTx(uart_ins_temp);
        LL_UART_EnableDirectionRx(uart_ins_temp);

        //UART Enable
        LL_UART_Enable(uart_ins_temp);

        if (ret == 0) {
            user_dbg_ifc = ifc;
            user_dbg_uart_ins = uart_ins_temp;
        } else {
            LL_UART_Disable(uart_ins_temp);
        }
    }

    return ret;
}

/**
  * @brief  User Debug DeInit
  * @note   Remember to implement the HAL_UART_MspDeInit interface in the user file if use UART as debug interface
  * @return HAL Status
  */
uint32_t User_Debug_DeInit(void)
{
    uint32_t ret = 0;

    //Check current user debug interface to be Valid
    if (user_dbg_ifc == USER_DBG_IFC_NO) {
        user_dbg_uart_ins = NULL;
        return 0;
    }

    if (user_dbg_ifc == USER_DBG_IFC_ITM) {
        //SWO GPIO DeInit:
        ///TODO GPIO DEINIT

        if (ret == 0) {
            user_dbg_ifc = USER_DBG_IFC_NO;
        }

    } else {
        if (user_dbg_uart_ins == NULL) {
            return -1;
        }

        //UART DeInit
        ///TODO UART DEINIT

        if (ret == 0) {
            user_dbg_ifc = USER_DBG_IFC_NO;
            user_dbg_uart_ins = NULL;
        }
    }

    return ret;
}


/**
  * @brief  User Debug Get Char
  * @param  None
  * @return get char value
  */
int User_Debug_GetChar(void)
{
    int val = 0;

    //Check user debug interface to be Valid
    if (user_dbg_ifc == USER_DBG_IFC_NO) {
        return 0;
    }

    if (user_dbg_ifc == USER_DBG_IFC_ITM) {
        while (!ITM_CheckChar()) {
            __NOP();
        }

        val = ITM_ReceiveChar();
    } else {

#if defined(UART0) || defined(UART1) || defined(UART2)  || defined(UART3)  || defined(UART4) 
        if (user_dbg_uart_ins == NULL) {
            return 0;
        }

        //Wait RX data to be ready
        while (LL_UART_IsRxFIFOEmpty(user_dbg_uart_ins));

        //Read data from UART
        val = LL_UART_ReceiveData9(user_dbg_uart_ins);
#endif
    }

    return val;
}

/**
  * @brief  User Debug Put Char
  * @param  Data put data
  * @return None
  */
void User_Debug_PutChar(uint16_t Data)
{
    //Check user debug interface to be Valid
    if (user_dbg_ifc == USER_DBG_IFC_NO) {
        return;
    }

    if (user_dbg_ifc == USER_DBG_IFC_ITM) {
        ITM_SendChar(Data);
    } else {

#if defined(UART0) || defined(UART1) || defined(UART2)  || defined(UART3)  || defined(UART4) 
        if (user_dbg_uart_ins == NULL) {
            return;
        }

        //Wait TXFIFO to be no full
        while (LL_UART_IsTxFIFOFull(user_dbg_uart_ins));

        //Send data to UART
        LL_UART_TransmitData9(user_dbg_uart_ins, Data);
#endif
    }
}

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @defgroup User_Debug_Private_Functions User Debug Private Functions
  * @brief    User Debug Private Functions
  * @{
  */

//#if defined(__CC_ARM) || defined(__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/**
  * @brief  Get char, Retargets the C library DBG_NOR function to the UART or ITM.
  * @param  f file pointer
  * @retval get char value
  */
GETCHAR_PROTOTYPE {
    int val = 0;

    val = User_Debug_GetChar();

    return val;
}

/**
  * @brief  Put char, Retargets the C library DBG_NOR function to the UART or ITM.
  * @param  ch put data
  * @param  f file pointer
  * @retval ch
  */
PUTCHAR_PROTOTYPE {
    User_Debug_PutChar(ch);

    return ch;
}

/**
  * @brief  ferror
  * @param  f: Printed entry pointer
  * @retval Return result
  */
int ferror(FILE *f)
{
    /* Your implementation of ferror */
    return EOF;
}

/**
  * @brief  _ttywrch
  * @param  ch: The value of the string to print
  * @retval None
  */
void _ttywrch(int ch)
{
    int file = 0;
    fputc(ch, (FILE *)file);
}

/**
  * @brief  _sys_exit
  * @param  return_code: Return wrong information
  * @retval None
  */
void _sys_exit(int return_code)
{
    while (1);    /* endless loop */
}

/**
  * @brief  backspace
  * @param  None
  * @return 0
  */
int __backspace()
{
    return 0;
}

#elif defined(__ICCARM__)

/**
  * @brief  Get char, Retargets the C library DBG_NOR function to the UART or ITM.
  * @param  f file pointer
  * @retval get char value
  */
GETCHAR_PROTOTYPE {
    if (handle == 0) {
        for (size_t i = 0; i < size; i++) {
            buffer[i] = (unsigned char)User_Debug_GetChar();
        } 
        return size;
    }
    
    return 0;
}

/**
  * @brief  Put char, Retargets the C library DBG_NOR function to the UART or ITM.
  * @param  ch put data
  * @param  f file pointer
  * @retval ch
  */
PUTCHAR_PROTOTYPE {
    if (handle == 1 || handle == 2) {
        for (size_t i = 0; i < size; i++) {
            User_Debug_PutChar((uint16_t)buffer[i]);
        } 
        
        return size;
    }
    

    return (size_t)-1;
}

#else

PUTCHAR_PROTOTYPE {
    for (int i = 0; i < size; i++)
    {
        User_Debug_PutChar(pBuffer[i]);
    }

    return size;
}

GETCHAR_PROTOTYPE {
    for (int i = 0; i < size; i++)
    {
        pBuffer[i] = User_Debug_GetChar();
    }

    return size;
}

#endif

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

