/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H
    

    /*Define your macro callbacks here */
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/

//for using sprintf
#include <stdio.h>
//for using abs
#include <stdlib.h>
#include <stdbool.h>

#include "project.h"
//for printing in serial
#include "utils.h"

#include "tcs34725.h"    

#define MAX_NUM_TO_MEASURE 10
#define MAX_NUM_TO_MEASURE_NONE 100

bool button_pushed;

int min_none_color[3];
int max_none_color[3];

int min_cur_color[3];
int max_cur_color[3];

struct color_boundaries{
    int min_rgb[3];
    int max_rgb[3];
};

struct color_boundaries boundaries[6];

void fill_boundaries(void);

bool compare_to_none_color(int color[3]);
int analyze_measurement_boundaries(int min_rgb[3], int max_rgb[3], bool none_col, int count_settings);

void analyze_measurement_boundaries_none(int min_rgb[3], int max_rgb[3]);
void analyze_measurement_boundaries_color(int min_rgb[3], int max_rgb[3], int count_settings);


#endif /* CYAPICALLBACKS_H */   
/* [] */
