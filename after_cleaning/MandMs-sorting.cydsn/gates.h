#ifndef _GATES_H_
#define _GATES_H_

#include <stdbool.h>
#include "tcs34725.h"
#include "utils.h"

#define CW 0
#define CCW 1

#define DELAY_STOP_AFTER_CLOSE 10
#define DELAY_STOP_AFTER_OPEN 550
    
struct motors{
    bool motor_1;
    bool motor_2_5;
    bool motor_3_4;
};

void RunMotors45Degrees(bool direction, struct motors gates);
void OpenCloseGates(struct motors gates);
void OpenCloseTestGates(int count_settings, bool open);

    
#endif