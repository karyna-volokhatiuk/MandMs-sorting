#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "project.h"
#include "tcs34725.h"
#include "utils.h"
#include "learn_color.h"
#include "gates.h"

#define BUTTON_NUM 0

extern uint8_t _tcs34725Initialised;
extern struct RGB red_led, yellow_led, orange_led, green_led, blue_led, brown_led, black_led;
extern bool state;

int count_settings = 0;
uint16 joystick = 0;

CY_ISR(SW_Handler)
{
    count_settings++;
    button_pushed = true;
    
    SW_ClearInterrupt();
}


CY_ISR(SW_UpDown_Handler)
{

    joystick = ADC_GetResult16(BUTTON_NUM);
    
    if (joystick){
    }
    
    SW_UpDown_ClearInterrupt();
}


int main(void)
{
    //print("START");
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    I2C_Start();
    UART_Start();
    Clock_Start();
    
    PWM_RED_Start();
    PWM_GREEN_Start();
    PWM_BLUE_Start();
    
    LED(black_led);
    
    ADC_Start();
    ADC_StartConvert();

    isr_SW_StartEx(SW_Handler);
    isr_SW_UpDown_StartEx(SW_UpDown_Handler);
    
    while (_tcs34725Initialised == false){
        init(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
    }
      
    int red, green, blue;
    uint8_t color = 0;
    
    struct motors gates = {1, 1, 1};
    
    OpenCloseGates(gates);
    CyDelay(1000);
    
    PWM_Container_Start();
    PWM_Container_WriteCompare(0);
    
    while (count_settings < 8){
        preparation(count_settings);
        sprintf(str, "count_set %d", count_settings);
        print(str);
    }
    
    PWM_Container_WriteCompare(1);
    
    for(;;)
    {  
        sprintf(str, "joystick %d   \n", joystick);
        //print(str);
        
        state = CANDY;
        getRGB(&red, &green, &blue);
        color = getColor(red, green, blue);
            
        if (state == CANDY){
            
            switch (color){
                case RED:
                    gates = (struct motors){0, 0, 0};
                    break;
                case ORANGE:
                    gates = (struct motors){0, 0, 1};
                    break;
                case YELLOW:
                    gates = (struct motors){0, 1, 0};
                    break;
                case GREEN:
                    gates = (struct motors){0, 1, 1};
                    break;
                case BLUE:
                    gates = (struct motors){1, 0, 0};
                    break;
                case BROWN:
                    gates = (struct motors){1, 0, 1};
                    break;
            }
            OpenCloseGates(gates);
        
        }

    }        
}
