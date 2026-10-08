#include "ADC.h"

void ADC_Init(uint8 reference, uint8 prescaler)
{
    /* AVCC as reference */
    ADMUX = (1 << REFS0);

    /* ADC prescaler = 64 */
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1);

    /* Disable digital input on ADC0 */
    SFIOR = 0;
}

uint16 ADC_Read(uint8 channel)
{
    ADMUX = (1 << REFS0) | (channel & 0x07);

    ADCSRA |= (1 << ADSC);

    while((ADCSRA & (1 << ADIF)) == 0);

    ADCSRA |= (1 << ADIF);

    return ADC;
}