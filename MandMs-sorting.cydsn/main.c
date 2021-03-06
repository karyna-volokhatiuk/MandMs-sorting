#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "project.h"
#include "tcs34725.h"
#include "utils.h"
#include "learn_color.h"

#define CW 0
#define CCW 1

#define test 30


#define DELAY_STOP_AFTER_CLOSE 10
#define DELAY_STOP_AFTER_OPEN 550


void RunMotors45Degrees(bool direction);
void OpenCloseGates();


extern uint8_t _tcs34725Initialised;

extern struct RGB black_led, red_led, green_led;

extern bool state;


struct motors{
    bool motor_1;
    bool motor_2_5;
    bool motor_3_4;
};
struct motors gates = {1, 1, 1};

uint8_t current_measure[5] = {BLACK, BLACK, BLACK, BLACK, BLACK};

uint8_t previous_state = BLACK;

//int last_int_time = 0;

int my_test = 0;

int count_settings = 0;

int joystick = 0;


CY_ISR(SW_Handler)
{
    count_settings++;
    //if (button_pushed){
       // count_settings++;
    //}
    button_pushed = true;
    
    
    if (my_test == 255){
        my_test = 0;
    }else{
       my_test = 255;
    }
    
    SW_ClearInterrupt();
}

CY_ISR(SW_UpDown_Handler)
{

    joystick = ADC_GetResult16(0);
    
    if (joystick){
    }
    
    SW_UpDown_ClearInterrupt();
}


int main(void)
{
    print("START");
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    I2C_Start();
    UART_Start();
    Clock_Start();
    
    
    PWM_RED_Start();
    PWM_GREEN_Start();
    PWM_BLUE_Start();
    
    

    LED(black_led);
    //PWM_RED_WriteCompare(255);
    //PWM_GREEN_WriteCompare(255);
    //PWM_BLUE_WriteCompare(255);
    
    isr_SW_StartEx(SW_Handler);
    isr_SW_UpDown_StartEx(SW_UpDown_Handler);
    
    while (_tcs34725Initialised == false){
        init(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
    }
      
    int red, green, blue;
    uint8_t color = 0;
    
    OpenCloseGates();
    CyDelay(1000);
    
    
    int colors[5];
    
    //int colors_test[test][3];
    size_t idx = 0;
    
    ADC_Start();
    ADC_StartConvert();
    
    //fill_boundaries();
    PWM_Container_Start();
    PWM_Container_WriteCompare(0);
    //CyDelay(2000);
    
    
    while (count_settings < 8){
        preparation(count_settings);
    }
    
    PWM_Container_WriteCompare(1);
    
    for(;;)
    {  
        sprintf(str, "joystick %d   \n", joystick);
        //print(str);
        
        
        state = CANDY;
        getRGB(&red, &green, &blue);
        color = getColor(red, green, blue);
            
            //lightColor(color);
            //CyDelay(1000);
            //state = NONE;
            
            if (state == CANDY){
                
                switch (color){
                    case RED:
                        gates = (struct motors){0, 0, 0};
                        OpenCloseGates();
                        break;
                    case ORANGE:
                        gates = (struct motors){0, 0, 1};
                        OpenCloseGates();
                        break;
                    case YELLOW:
                        gates = (struct motors){0, 1, 0};
                        OpenCloseGates();
                        break;
                    case GREEN:
                        gates = (struct motors){0, 1, 1};
                        OpenCloseGates();
                        break;
                    case BLUE:
                        gates = (struct motors){1, 0, 0};
                        OpenCloseGates();
                        break;
                    case BROWN:
                        gates = (struct motors){1, 0, 1};
                        OpenCloseGates();
                        break;
                }
            
            }
            
        
        
        }
        
}



//function for running needed drivers
//EXAMPLE: if we want to run the third driver, arguments will be 0,0,1
//argument that equals to 0 means not to run this driver, 1 means to run
void RunMotors45Degrees(bool direction){
    
    //set direction
    Dir_1_Write(direction);
    Dir_2_5_Write(direction);
    Dir_3_4_Write(direction);
    
    //count value of counter to run needed motors
    uint8_t val = 0b000;
    val = val | gates.motor_1 | (gates.motor_2_5 << 1) | (gates.motor_3_4 << 2);
    
    Control_Reg_2_Write(val);
    
    Control_Reg_1_Write(true);
    
    while (Status_Reg_1_Read() != true);
    
    Control_Reg_1_Write(false);
    
    while (Status_Reg_1_Read() != false);
}

void OpenCloseGates(){
    
    //run needed motors 45 degrees clockwise
    RunMotors45Degrees(CCW);
    CyDelay(190);
    
    PWM_Container_Stop();
    CyDelay(DELAY_STOP_AFTER_OPEN);
    
    //run needed motors 45 degrees counterclockwise
    RunMotors45Degrees(CW);
    
    CyDelay(DELAY_STOP_AFTER_CLOSE);
    PWM_Container_Start();
}

void OpenCloseTestGates(int count_settings, bool open){
    switch (count_settings){
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
    if (open){
        RunMotors45Degrees(CCW);
    } else{
        RunMotors45Degrees(CW);
    }
    
}
