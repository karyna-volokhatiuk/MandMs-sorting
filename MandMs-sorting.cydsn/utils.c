#include "project.h"
#include "utils.h"

char str[STRING_LENGTH+1] ; /* print buff */

void print(char *str)
{
    UART_UartPutString(str) ;
}
