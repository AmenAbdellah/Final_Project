/*
 * Last Pwm.c
 *
 * Created: 30/1/2023 1:57:21 AM
 * Author : Amen Abdellah
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_int.h"
#include "PWM_int.h"
#include "LCD_int.h"


#define F_CPU 16000000UL

//Config OCR0 value here:
#define MY_OCR0_VALUE 115 //gives duty cycle of 45% ( (115/255) *100 ) //255 bec. Timer0 is 8 Bit

u16 TR=0,TF=0,TR2=0; //global variables to store the value of rising and falling

int main (void){
	
	
	u16 high=0,period=0;
	s8 frequency[14],dc[7];
	
	DIO_voidInit();
	
	
	LCD_init();
	_delay_ms(100);
	LCD_Cmd_Fun(0x0C);
	_delay_ms(100);
	
	u8 duty;
	
	PWM_init();
	
	while(1)
	{
		TCCR1A = 0x00;
		TCNT1=0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		while((TIFR&(1<<ICF1)) == 0);
		TR = ICR1;  		/* Take value of capture register */
		TIFR =(1<<ICF1); 	/* Clear ICF flag */
		
		TCCR1B = 0x01;  	/* Falling edge, no prescaler */
		while((TIFR&(1<<ICF1))== 0);
		TF = ICR1;  		/* Take value of capture register */
		TIFR =(1<<ICF1);  	/* Clear ICF flag */
		
		
		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		while((TIFR&(1<<ICF1)) == 0);
		TR2 = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		

		TCCR1B = 0x00;  		/* Stop the timer */
		
		if(TF>TR && TF<TR2)  	/* Check for valid condition, 
					to avoid timer overflow reading */
		{
			high=TF-TR;
			period=TR2-TR;
			

			
			u32 freq= ( (16000000/period)); /* Calculate frequency */
			
            float duty_cycle =((float) high /(float)period)*100; /* Calculate duty cycle */
			
			ltoa(freq,frequency,10);
			
			itoa((int)duty_cycle,dc,10);
			
			LCD_Cmd_Fun(0x80);
			LCD_String("F:");
			LCD_String(frequency);
			LCD_String("Hz");
			
			LCD_Cmd_Fun(0x88);
			LCD_String(" DC:");
			LCD_String(dc);
			LCD_String("%");
			
		
		}
		else
		{
			LCD_Clear();
			LCD_String("out of range");
		}
		_delay_ms(50);
		
		PWM_Drawer();    //for drawing pwm signal
/*-----------------------------*/
			OCR0= MY_OCR0_VALUE;      //value of generated pwm by timer0
	}
	
	return 0;
} 




void PWM_Drawer() //function for drawing pwm signal
{
	
	 
	int duty = (((TF-TR)*100)/(TR2-TR));
	int get_up = (duty*8)/100;
	int loop =0;
	int get_down = 8-get_up;
	LCD_Cmd_Fun(0xC0);
	while(loop<4)
	{
		LCD_String("-");
		for(int up=1; up<get_up; up++)
			LCD_String("-");
		
			
		//LCD_String("-");
		for(int down=1; down<get_down; down++)
			LCD_String("_");
			
			
		loop++;
	}
}
