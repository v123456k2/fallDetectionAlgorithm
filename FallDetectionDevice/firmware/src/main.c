/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "imu.h"
#include "math.h"

static volatile bool isUSARTTxComplete = true;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

static void usartDmaChannelHandler(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle)
{
    if (event == DMAC_TRANSFER_EVENT_COMPLETE)
    {
        isUSARTTxComplete = true;
    }
}

void printFloatToBuffer(uint8_t* uartLocalTxBuffer, double num)
{
    int x = 0;
    int whole = (int) num;
    int frac = num >= whole ? (num - whole) * 1000: (whole - num) * 1000;


    sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"%d.", whole);
    x = frac != 0 ? frac : 1;
    while(x <= 100){
        sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"0");
        x *= 10;
    }
    sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"%d\n\r", frac);
}
int main ( void )
{
    //uint8_t uartLocalTxBuffer[1000] = {0};
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, usartDmaChannelHandler, 0);
    
    SERCOM0_I2C_Initialize();
    
    uint8_t pwr_config[2] = {0x4E,0x1F};
    
       
    double accel_x;
    double accel_y;
    double accel_z;
    
    //double gyro_x;
    //double gyro_y;
    //double gyro_z;
    
    double accMin = 0.08;
    //double accMin = 0.085;
    //double accMax = 0;
    //double angMax = 0;
    //bool belowAccMin = false;
    //bool aboveAccMax = false;
    //bool aboveAngMax = false;
    //int count = 0;
    double cur = 0;
    
    SERCOM0_I2C_Write(0x69, pwr_config, 2);
    while(SERCOM0_I2C_IsBusy());
    
    setAccelParam();
    //setGyroParam();
    
    
    
    while(true){
        accel_x = getAccelX();
        accel_y = getAccelY();
        accel_z = getAccelZ();
        //PORT_PinWrite(PORT_PIN_PA28, true);
        
        /*sprintf((char*)uartLocalTxBuffer,"Accel X: ");
        printFloatToBuffer(uartLocalTxBuffer, accel_x);
        
        sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"Accel Y: ");
        printFloatToBuffer(uartLocalTxBuffer, accel_y);
        
        sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"Accel Z: ");
        printFloatToBuffer(uartLocalTxBuffer, accel_z); */
        
        //gyro_x = getGyroX();
        //gyro_y = getGyroY();
        //gyro_z = getGyroZ();
        //PORT_PinWrite(PORT_PIN_PA28, true);
        double acc =  sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);
        //double gyro = sqrt(gyro_x * gyro_x + gyro_y * gyro_y + gyro_z * gyro_z);
        
        if (acc <= accMin) {
            //belowAccMin = true;
            PORT_PinWrite(PORT_PIN_PA28, true);
            //count = 0;
            cur = 0;
        }
        /*if (acc >= accMax && belowAccMin) {
            aboveAccMax = true;
        }
        if (gyro >= angMax && belowAccMin) {
            aboveAngMax = true;
        }
        */
        /*if (belowAccMin) {
            //sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"Free Fall!\n\r");
            belowAccMin = false;
            //aboveAccMax = false;
            //aboveAngMax = false;
            //activated = true;
            //count = 0;
            
        }*/
        
        /*if (count > 500) {
            belowAccMin = false;
            //aboveAccMax = false;
            //aboveAngMax = false;
            count=0;
        }
        count = count + 1;*/
        cur += 1;
        /*sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"Gyro X: ");
        printFloatToBuffer(uartLocalTxBuffer, gyro_x);
        
        sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"Gyro Y: ");
        printFloatToBuffer(uartLocalTxBuffer, gyro_y);
        
        sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"Gyro Z: ");
        printFloatToBuffer(uartLocalTxBuffer, gyro_z);
        
        sprintf((char*)uartLocalTxBuffer + strlen((char*)uartLocalTxBuffer),"\n\r");*/
        
        /*DMAC_ChannelTransfer(DMAC_CHANNEL_0, uartLocalTxBuffer, \
                    (const void *)&(SERCOM1_REGS->USART_INT.SERCOM_DATA), \
                    strlen((const char*)uartLocalTxBuffer));*/
        //for(int i =0; i <200; ++i);
        if (cur >= 1500) {
            //memset(uartLocalTxBuffer, 0, sizeof uartLocalTxBuffer);
            PORT_PinWrite(PORT_PIN_PA28, false);
            cur = 0;
        }
    }
    

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

