#include "tcs34725.h"

extern int min_none_color[3];
extern int max_none_color[3];


int red_struct_min[] = {255, 255, 255};
int red_struct_max[] = {0, 0, 0};

int green_struct_min[] = {255, 255, 255};
int green_struct_max[] = {0, 0, 0};

int blue_struct_min[] = {255, 255, 255};
int blue_struct_max[] = {0, 0, 0};

int yellow_struct_min[] = {255, 255, 255};
int yellow_struct_max[] = {0, 0, 0};


int orange_struct_min[] = {255, 255, 255};
int orange_struct_max[] = {0, 0, 0};

int brown_struct_min[] = {255, 255, 255};
int brown_struct_max[] = {0, 0, 0};

/*
int red_struct_min[] = {112, 65, 54};
int red_struct_max[] = {122, 73, 62};

int green_struct_min[] = {54, 110, 60};
int green_struct_max[] = {60, 117, 67};

int blue_struct_min[] = {36, 83, 111};
int blue_struct_max[] = {45, 97, 133};

int yellow_struct_min[] = {94, 91, 37};
int yellow_struct_max[] = {101, 96, 45};


int orange_struct_min[] = {112, 69, 43};
int orange_struct_max[] = {121, 75, 51};

int brown_struct_min[] = {73, 80, 64};
int brown_struct_max[] = {84, 88, 78};
*/
struct RGB red_led = {255, 0, 0};
struct RGB green_led = {0, 255, 0};
struct RGB blue_led = {0, 0, 255};
struct RGB yellow_led = {255, 130, 3};
struct RGB orange_led = {255, 126, 0};
struct RGB brown_led = {117, 76, 0};
struct RGB black_led = {0, 0, 0};

uint8_t _tcs34725Initialised = false;
uint8_t _tcs34725Gain;
uint8_t _tcs34725IntegrationTime;

uint32 status;

bool state = NONE;

//for learn_color
bool button_pushed = false;

int min_none_color[3] = {255, 255, 255};
int max_none_color[3] = {0, 0, 0};

#define MAX_NUM_TO_MEASURE 10
#define MAX_NUM_TO_MEASURE_NONE 100
    
#define THRESHOLD_NONE 5
#define THRESHOLD_COLOR 2



//write 8-bit value to reg
void write8(uint8_t reg, uint32_t value)
{   
	I2C_I2CMasterSendStart(TCS34725_ADDRESS, I2C_I2C_WRITE_XFER_MODE, timeoutMs);
    
	status = I2C_I2CMasterWriteByte(TCS34725_COMMAND_BIT | reg, timeoutMs);
    if (status != I2C_I2C_MSTR_NO_ERROR){
        print("ERROR_WRITE8");
    }
    
    status = I2C_I2CMasterWriteByte(value & 0xFF, timeoutMs);
    if (status != I2C_I2C_MSTR_NO_ERROR){
        print("ERROR_WRITE8");
    }
    
    I2C_I2CMasterSendStop(stopTime);
}

//read and return 8-bit value from reg
uint8_t read8(uint8_t reg)
{   
    uint8_t current;
	I2C_I2CMasterSendStart(TCS34725_ADDRESS, I2C_I2C_WRITE_XFER_MODE, timeoutMs);
	status = I2C_I2CMasterWriteByte(TCS34725_COMMAND_BIT | reg, timeoutMs);
    if (status != I2C_I2C_MSTR_NO_ERROR){
        print("ERROR_READ8");
    }
    I2C_I2CMasterSendStop(stopTime);

    I2C_I2CMasterSendStart(TCS34725_ADDRESS, I2C_I2C_READ_XFER_MODE, timeoutMs);
    status = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA, &current, timeoutMs);
    if (status != I2C_I2C_MSTR_NO_ERROR){
        print("ERROR_READ8");
    }
    I2C_I2CMasterSendStop(stopTime);
    
    return current;
}


//read and return 16-bit value from reg
uint16_t read16(uint8_t reg)
{   
    uint8_t low, high;
	I2C_I2CMasterSendStart(TCS34725_ADDRESS, I2C_I2C_WRITE_XFER_MODE, timeoutMs);
	I2C_I2CMasterWriteByte(TCS34725_COMMAND_BIT | reg, timeoutMs);
    I2C_I2CMasterSendStop(stopTime);

    I2C_I2CMasterSendStart(TCS34725_ADDRESS, I2C_I2C_READ_XFER_MODE, timeoutMs);
    
    status = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA, &low, timeoutMs);
    if (status != I2C_I2C_MSTR_NO_ERROR){
        print("ERROR_READ16");
    }
    
    status = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA, &high, timeoutMs);
    if (status != I2C_I2C_MSTR_NO_ERROR){
        print("ERROR_READ16");
    }
    
    I2C_I2CMasterSendStop(stopTime);
    
    uint16_t x = high;
    uint16_t t = low;
    
    x <<= 8;
    x |= t;

    return x;
}


void enable(){
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
  CyDelay(3);
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
  CyDelay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
}

void disable(){
  uint8_t reg = 0;
  reg = read8(TCS34725_ENABLE);
  write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

void setIntegrationTime(uint8_t it) {

  write8(TCS34725_ATIME, it);

  _tcs34725IntegrationTime = it;
}

void setGain(uint8_t gain) {
  
  write8(TCS34725_CONTROL, gain);

  _tcs34725Gain = gain;
}


uint8_t init(uint8_t it, uint8_t gain) {
  /* Make sure we're actually connected */
  uint8_t x = read8(TCS34725_ID);

  if ((x != 0x4d) && (x != 0x44) && (x != 0x10)) {
    print("PROBLEM_READ_ID");
    return false;
  }
  sprintf(str, "%u", x);
  print(str);

  _tcs34725Initialised = true;

  setIntegrationTime(it);
  setGain(gain);

  enable();

  return true;
}

//write raw values of red, green, blue, clear to r, g, b, c
void getRawData(uint16_t *r, uint16_t *g, uint16_t *b,
                                   uint16_t *c) {
  *c = read16(TCS34725_CDATAL);
  *r = read16(TCS34725_RDATAL);
  *g = read16(TCS34725_GDATAL);
  *b = read16(TCS34725_BDATAL);

  /* Set a delay for the integration time */
  /* 12/5 = 2.4, add 1 to account for integer truncation */
  CyDelay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
}
                                
//write calculated values of red, green, blue, clear to r, g, b
//in range 0-255
void getRGB(int *r, int *g, int *b) {
  uint16_t red, green, blue, clear;
  getRawData(&red, &green, &blue, &clear);

  uint32_t sum = clear;

  // Avoid dividing by zero errors ... if clear = 0 return black
  if (clear == 0) {
    *r = *g = *b = 0;
    return;
  }

  *r = (int)((float)red / sum * 255.0);
  *g = (int)((float)green / sum * 255.0);
  *b = (int)((float)blue / sum * 255.0);

}

uint8_t checkColor(int color_min[3], int color_max[3], int r, int g, int b){
    
    if ((color_min[0] <= r) && (color_min[1] <= g) && (color_min[2] <= b)){
        if ((color_max[0] >= r) && (color_max[1] >= g) && (color_max[2] >= b)){
            return true;
        }
        
    }
    return false;
}

//return scanned color
uint8_t getColor(int r, int g, int b){
    sprintf(str, "r %d | g %d | b %d\n", r, g, b) ;
    print(str) ;
    
    state = CANDY;
    if (checkColor(red_struct_min, red_struct_max, r, g, b)){
        print("RED");
        return RED;
    }else if (checkColor(green_struct_min, green_struct_max, r, g, b)){
        print("GREEN");
        return GREEN;
    }else if (checkColor(blue_struct_min, blue_struct_max, r, g, b)){
        print("BLUE");
        return BLUE;
    }else if (checkColor(orange_struct_min, orange_struct_max, r, g, b)){
        print("ORANGE");
        return ORANGE;
    }else if (checkColor(brown_struct_min, brown_struct_max, r, g, b)){
        print("BROWN");
        return BROWN;
    }else if (checkColor(yellow_struct_min, yellow_struct_max, r, g, b)){
        print("YELLOW");
        return YELLOW;
    }else{
        print("NONE");
        state = NONE;
        return BLACK;
    }
    
}

//light LED with input color
void LED(struct RGB color){
    
    PWM_RED_WriteCompare(255 - color.r);
    PWM_GREEN_WriteCompare(255 -color.g);
    PWM_BLUE_WriteCompare(255 - color.b);
    
}

//light led with scanned color
void lightColor(uint8_t col){
    switch(col){
        case RED:
            LED(red_led);
            break;
        case GREEN:
            LED(green_led);
            break;
        case BLUE:
            LED(blue_led);
            break;
        case YELLOW:
            LED(yellow_led);
            break;
        case ORANGE:
            LED(orange_led);
            break;
        case BROWN:
            LED(brown_led);
            break;
        default:
            LED(black_led);
            break;
           
    }
}


int preparation(int count_settings){
    
    
    if (count_settings == 0){
        //print("preparation");

        analyze_measurement_boundaries_none(min_none_color, max_none_color);
        return 0;
    }
    
    
    switch(count_settings){
        case RED:
            analyze_measurement_boundaries_color(red_struct_min, red_struct_max, count_settings);
            break;
        case GREEN:
            analyze_measurement_boundaries_color(green_struct_min, green_struct_max, count_settings);
            break;
        case BLUE:
            analyze_measurement_boundaries_color(blue_struct_min, blue_struct_max, count_settings);
            break;
        case YELLOW:
            analyze_measurement_boundaries_color(yellow_struct_min, yellow_struct_max, count_settings);
            break;
        case ORANGE:
            analyze_measurement_boundaries_color(orange_struct_min, orange_struct_max, count_settings);
            break;
        case BROWN:
            analyze_measurement_boundaries_color(brown_struct_min, brown_struct_max, count_settings);
            break;
        default:
            
            break;
    }
    
    return 0;
}


//#include "learn_color.h"



int analyze_measurement_boundaries(int min_rgb[3], int max_rgb[3], bool none_col, int count_settings){
    
    int color[3];
    
    size_t curr_num = 0;
    
    if(!button_pushed){
        return 0;
    }
    
    PWM_Container_WriteCompare(1);
    
    size_t max_num_to_measure = none_col ? MAX_NUM_TO_MEASURE_NONE : MAX_NUM_TO_MEASURE;
    
    sprintf(str, "max_num_to_measure %d", max_num_to_measure);
    print(str);
    

    
    if (!none_col){
        OpenCloseTestGates(count_settings, true);
    }
    
    int count_not_none = 0;
    //sprintf(str, "r %d | g %d | b %d", color[0], color[1], color[2]);
    sprintf(str, "startNone%d|", none_col);
    print(str);
   
    
    while(curr_num < max_num_to_measure){
        getRGB(&color[0], &color[1], &color[2]);
        //sprintf(str, "r %d | g %d | b %d", color[0], color[1], color[2]);
        sprintf(str, "%d|", none_col);
        print(str);
        
        
        if (none_col == false && compare_to_none_color(color)){
            count_not_none = 0;
            //print("notNone");
            continue;
            
        }

        count_not_none += 1;
        if (count_not_none == 3 || count_not_none == 4 || none_col == true){
            print("true");
            
            for (size_t i = 0; i<3; i++){
                if (color[i] < min_rgb[i]){
                    min_rgb[i] = color[i];
                }
                if (color[i] > max_rgb[i]){
                    max_rgb[i] = color[i];
                }
                
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
        for (size_t i = 0; i<3; i++){
            min_rgb[i] -= THRESHOLD_NONE;
            max_rgb[i] += THRESHOLD_NONE;
        }
    } else{;
        for (size_t i = 0; i<3; i++){
            min_rgb[i] -= THRESHOLD_COLOR;
            max_rgb[i] += THRESHOLD_COLOR;
        }
    }
    
    sprintf(str, "min r %d | g %d | b %d", min_rgb[0], min_rgb[1], min_rgb[2]);
    print(str);
    
    sprintf(str, "max r %d | g %d | b %d", max_rgb[0], max_rgb[1], max_rgb[2]);
    print(str);
    
    return 0;

}

void analyze_measurement_boundaries_none(int min_rgb[3], int max_rgb[3]){
    print("hello");
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

  