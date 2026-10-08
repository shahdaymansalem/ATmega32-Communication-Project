#include "DIO.h"


void DIO_initPin(uint8 pinNumber, uint8 port, uint8 pinDirection)
{
	switch(port)
	{
		case PORT_A:
			if(pinDirection == OUTPUT)
				SET(DDRA, pinNumber);
			else
				CLEAR(DDRA, pinNumber);
			break;

		case PORT_B:
			if(pinDirection == OUTPUT)
				SET(DDRB, pinNumber);
			else
				CLEAR(DDRB, pinNumber);
			break;

		case PORT_C:
			if(pinDirection == OUTPUT)
				SET(DDRC, pinNumber);
			else
				CLEAR(DDRC, pinNumber);
			break;

		case PORT_D:
			if(pinDirection == OUTPUT)
				SET(DDRD, pinNumber);
			else
				CLEAR(DDRD, pinNumber);
			break;
	}
}


void DIO_initPort(uint8 port, uint8 portDirection)
{
	switch(port)
	{
		case PORT_A:
			DDRA = portDirection;
			break;

		case PORT_B:
			DDRB = portDirection;
			break;

		case PORT_C:
			DDRC = portDirection;
			break;

		case PORT_D:
			DDRD = portDirection;
			break;
	}
}


void DIO_WritePin(uint8 pinNumber, uint8 port, uint8 value)
{
	switch(port)
	{
		case PORT_A:
			if(value == HIGH)
				SET(PORTA, pinNumber);
			else
				CLEAR(PORTA, pinNumber);
			break;

		case PORT_B:
			if(value == HIGH)
				SET(PORTB, pinNumber);
			else
				CLEAR(PORTB, pinNumber);
			break;

		case PORT_C:
			if(value == HIGH)
				SET(PORTC, pinNumber);
			else
				CLEAR(PORTC, pinNumber);
			break;

		case PORT_D:
			if(value == HIGH)
				SET(PORTD, pinNumber);
			else
				CLEAR(PORTD, pinNumber);
			break;
	}
}


void DIO_WritePort(uint8 port, uint8 value)
{
	switch(port)
	{
		case PORT_A:
			PORTA = value;
			break;

		case PORT_B:
			PORTB = value;
			break;

		case PORT_C:
			PORTC = value;
			break;

		case PORT_D:
			PORTD = value;
			break;
	}
}


uint8 DIO_ReadPin(uint8 pinNumber, uint8 port)
{
	uint8 value = LOW;

	switch(port)
	{
		case PORT_A:
			value = GET(PINA, pinNumber);
			break;

		case PORT_B:
			value = GET(PINB, pinNumber);
			break;

		case PORT_C:
			value = GET(PINC, pinNumber);
			break;

		case PORT_D:
			value = GET(PIND, pinNumber);
			break;
	}

	return value;
}


uint8 DIO_ReadPort(uint8 port)
{
	uint8 value = PORT_LOW;

	switch(port)
	{
		case PORT_A:
			value = PINA;
			break;

		case PORT_B:
			value = PINB;
			break;

		case PORT_C:
			value = PINC;
			break;

		case PORT_D:
			value = PIND;
			break;
	}

	return value;
}


void DIO_Toggle(uint8 pinNumber, uint8 port)
{
        switch(port)
        {
                case PORT_A:
                        TOGGLE(PORTA, pinNumber);
                        break;

                case PORT_B:
                        TOGGLE(PORTB, pinNumber);
                        break;

                case PORT_C:
                        TOGGLE(PORTC, pinNumber);
                        break;

                case PORT_D:
                        TOGGLE(PORTD, pinNumber);
                        break;
        }
}
