#ifndef GET_TEMP_H
#define DET_TEMP_H

#include <avr/io.h>

void setup_adc(void);
void start_and_wait_conversion(void);
int get_temp(int c_temp);

#endif