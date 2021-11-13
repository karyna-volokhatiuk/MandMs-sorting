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

/* [] END OF FILE */
#include "learn_color.h"
#include "main.h"

//new
bool button_pushed = false;

int min_none_color[3] = {255, 255, 255};
int max_none_color[3] = {0, 0, 0};


//int min_rgb[3] = {255, 255, 255};
//int max_rgb[3] = {0, 0, 0};
//int mid_rgb[3];
//

/*
void fill_boundaries(){
    
    for(size_t i; i<6; i++){
        for (size_t j; j<3; j++){
            boundaries[i].min_rgb[j] = 255;
            boundaries[i].max_rgb[j] = 0;
        }
        
    }
    
    boundaries[0].min_rgb[0] = 1;
    boundaries[0].min_rgb[1] = 1;
    boundaries[0].min_rgb[2] = 1;
    
    boundaries[0].max_rgb[0] = 1;
    boundaries[0].max_rgb[1] = 1;
    boundaries[0].max_rgb[2] = 1;
    
    
}
*/

int analyze_measurement_boundaries(int min_rgb[3], int max_rgb[3], bool none_col, int count_settings){
    
    int color[3];
    
    //int all_measurements[MAX_NUM_TO_MEASURE][3];
    
    sprintf(str, "none %d", none_col);
    //print(str);
    
    sprintf(str, "settings %d", count_settings);
    //print(str);    
    
    size_t curr_num = 0;
    
    if(!button_pushed){
        return 0;
    }
    
    PWM_Container_WriteCompare(1);
    
    size_t max_num_to_measure = none_col ? MAX_NUM_TO_MEASURE_NONE : MAX_NUM_TO_MEASURE;
    
    if (!none_col){
        OpenCloseTestGates(count_settings, true);
    }
    
    int count_not_none = 0;
   
    
    while(curr_num < max_num_to_measure){
        getRGB(&color[0], &color[1], &color[2]);
        sprintf(str, "r %d | g %d | b %d", color[0], color[1], color[2]);
        print(str);
        
        
        if (none_col == false && compare_to_none_color(color)){
            sprintf(str, "SOS");
            print(str);
            count_not_none = 0;
            continue;
            
        }
        
        sprintf(str, "r %d | g %d | b %d", color[0], color[1], color[2]);
        //print(str);
        
        count_not_none += 1;
        if (count_not_none == 3 || count_not_none == 4 || none_col == true){
            
            for (size_t i = 0; i<3; i++){
            
                sprintf(str, "check %d", 0);
                //print(str);
                if (color[i] < min_rgb[i]){
                    sprintf(str, "check %d", 1);
                    //print(str);
                    min_rgb[i] = color[i];
                }
                if (color[i] > max_rgb[i]){
                    sprintf(str, "check %d", 2);
                    //print(str);
                    max_rgb[i] = color[i];
                }
                
                //all_measurements[curr_num][i] = color[i];
            }
            curr_num += 2;
        }
        
        
        
        
    }
    
    
    button_pushed = false;
    CyDelay(2000);
    
    if (!none_col){
        OpenCloseTestGates(count_settings, false);
    }
    
    PWM_Container_WriteCompare(0);
    
    
    if(none_col){
        sprintf(str, "NONE");
        print(str);
        for (size_t i = 0; i<3; i++){
            min_rgb[i] -= 5;
            max_rgb[i] += 5;
        }
    } else{;
        for (size_t i = 0; i<3; i++){
            min_rgb[i] -= 2;
            max_rgb[i] += 2;
        }
    }
    
    //for (size_t i; i < curr_num; i++){
      //  sprintf(str, "r %d | g %d | b %d", all_measurements[i][0], all_measurements[i][1], all_measurements[i][2]);
     //   print(str);
    //}
    
    sprintf(str, "min r %d | g %d | b %d", min_rgb[0], min_rgb[1], min_rgb[2]);
    print(str);
    
    sprintf(str, "max r %d | g %d | b %d", max_rgb[0], max_rgb[1], max_rgb[2]);
    print(str);
    
    //CyDelay(10000);
    return 0;
    //total sum of color measurements
    //for (size_t i; i <= curr_num; i++){
      //  for (size_t j; j < 3; j++){
        //    mid_rgb[j] += all_measurements[i][j];
        //}
    //}
    //find the average
    //for (size_t i; i < 3; i++){
      //  mid_rgb[i] /= curr_num+1;
    //}

}

void analyze_measurement_boundaries_none(int min_rgb[3], int max_rgb[3]){
    analyze_measurement_boundaries(min_rgb, max_rgb, true, 0);
}
void analyze_measurement_boundaries_color(int min_rgb[3], int max_rgb[3], int count_settings){
    analyze_measurement_boundaries(min_rgb, max_rgb, false, count_settings);
}

//true if color == none
bool compare_to_none_color(int color[3]){
    for (size_t i = 0; i<3; i++){
        if (min_none_color[i] > color[i] || max_none_color[i] < color[i]){
            return false;
        }       
    }
    
    return true;
    
}

    