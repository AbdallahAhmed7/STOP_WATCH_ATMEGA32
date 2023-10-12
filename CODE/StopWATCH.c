
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char sec1=0,sec2=0,min1=0,min2=0,hour1=0,hour2=0;

///////////////////////////// TIMER Initialize ////////////////////////////////////////////

void TIMER1_init_comp_mode(void)
{
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12)|(1<<CS10) | (1<<CS12);
	TCNT1=0;
	OCR1A=977; //compare value=977 for 1 second using 1Mhz and Pre-scalar=1024
	TIMSK |=(1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
	sec1++;
}

//////////////////////////////// INT0-INT1-INT2 Initialize //////////////////////////////////

void INT0_INIT_FALLING_EDGE(void)
{
	MCUCR |=(1<<ISC01);//FALLING EDGE
	GICR |=(1<<INT0); //ENABLE INT0
}

void INT1_INIT_RISING_EDGE(void)
{
	MCUCR |=(1<<ISC11)|(1<<ISC10);//RISING EDGE
	GICR |=(1<<INT1);//ENABLE INT1
}

void INT2_INIT_FALLING_EDGE(void)
{
	MCUCSR &=~(1<<ISC2);// INT2 FALLING EDGE
	GICR |=(1<<INT2); //ENABLE INT2
}


ISR(INT0_vect) //INT0 >> Reset
{
	sec1=0;
    sec2=0;
	min1=0;
	min2=0;
	hour1=0;
	hour2=0;
}


ISR(INT1_vect) //INT1 >> PAUSE
{
	TIMSK &=~(1<<OCIE1A); //TURN OFF TIMER
}


ISR(INT2_vect) //INT2 >> RESUME
{
	TIMSK |=(1<<OCIE1A); //TURN ON TIMER
}

////////////////////////////// Stop Watch Configuration //////////////////////////////////////

void stop_watch_configuration(void)
{


	if(sec1==10)
	{
		sec1=0;
		sec2++;


	}
	if(sec2==6)
	{
		sec2=0;
		min1++;

	}
	if(min1==10)
	{
		min1=0;
		min2++;

	}
	if(min2==6)
	{
		min2=0;
		hour1++;

	}
	if(hour1==10)
	{
		hour1=0;
		hour2++;

	}
	if(hour2==10)
	{
		sec1=0;
	    sec2=0;
		min1=0;
		min2=0;
		hour1=0;
		hour2=0;
	}

}

////////////////////////////// 7-SEGMENTS DISPLAY CODE //////////////////////////////////////////////////

void SIX_7segment_with_decoder_display(void)
{

	PORTA =0b11000001 ;
	PORTC =0b00001111 & sec1;
	_delay_ms(2);
	PORTA =0b11000010 ;
	PORTC =0b00001111 & sec2;
	_delay_ms(2);
	PORTA =0b11000100 ;
	PORTC =0b00001111 & min1;
	_delay_ms(2);
	PORTA =0b11001000 ;
	PORTC =0b00001111 & min2;
	_delay_ms(2);
	PORTA =0b11010000 ;
	PORTC =0b00001111 & hour1;
	_delay_ms(2);
	PORTA =0b11100000 ;
	PORTC =0b00001111 & hour2;
	_delay_ms(2);
}

/////////////////////////////////// MAIN CODE /////////////////////////////////////////////////////////


int main(void)
{
SREG |=(1<<7);
TIMER1_init_comp_mode();
INT0_INIT_FALLING_EDGE();
INT1_INIT_RISING_EDGE();
INT2_INIT_FALLING_EDGE();

DDRD &=~(1<<PD2) &~ (1<<PD3); //SET PD2,PD3, PB2 AS INPUTS PUSH BUTTONS
DDRB &=~(1<<PB2);

PORTD|=(1<<PD2); //Enable PD2 , PB2 as Internal pull up PUSH BUTTONS
PORTB|=(1<<PB2);

	DDRA |= 0b00111111; //SET FIRST 6 PINS IN PORTA AS OUTPUTS TO ENABLE THE 7-SEGMENTS
	DDRC |= 0b00001111; //SET FIRST 4 PINS IN PORTC AS OUTPUTS TO SEND NUMBERS TO DECODER
	PORTC &=0b11110000; //Initialize the decoder to 0
	PORTA  &=0b11000000; //Initialize the 7segments to OFF


    while(1)
    {
    	stop_watch_configuration();
    	SIX_7segment_with_decoder_display();

    }
}






