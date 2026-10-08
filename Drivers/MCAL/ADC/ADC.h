#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include "../../Library/Platform_types.h"

/* ADC Reference Voltage */
#define ADC_REF_AREF        0
#define ADC_REF_AVCC        1
#define ADC_REF_INTERNAL    3

/* ADC Prescaler */
#define ADC_PRESCALER_2     1
#define ADC_PRESCALER_4     2
#define ADC_PRESCALER_8     3
#define ADC_PRESCALER_16    4
#define ADC_PRESCALER_32    5
#define ADC_PRESCALER_64    6
#define ADC_PRESCALER_128   7

void ADC_Init(uint8 reference, uint8 prescaler);

uint16 ADC_Read(uint8 channel);

#endif