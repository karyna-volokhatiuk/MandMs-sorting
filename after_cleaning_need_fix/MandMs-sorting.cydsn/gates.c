#include "gates.h"

//function for running needed drivers
//EXAMPLE: if we want to run the third driver, arguments will be 0,0,1
//argument that equals to 0 means not to run this driver, 1 means to run
void RunMotors45Degrees(bool direction, struct motors gates){
    
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

void OpenCloseGates(struct motors gates){
    
    //run needed motors 45 degrees clockwise
    RunMotors45Degrees(CCW, gates);
    CyDelay(190);
    
    PWM_Container_Stop();
    CyDelay(DELAY_STOP_AFTER_OPEN);
    
    //run needed motors 45 degrees counterclockwise
    RunMotors45Degrees(CW, gates);
    
    CyDelay(DELAY_STOP_AFTER_CLOSE);
    PWM_Container_Start();
}

void OpenCloseTestGates(int count_settings, bool open){
    struct motors gates;
    
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
        RunMotors45Degrees(CCW, gates);
    } else{
        RunMotors45Degrees(CW, gates);
    }
    
}