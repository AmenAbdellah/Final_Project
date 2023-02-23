
#include "LCD_int.h"
#include <avr/io.h>
#include <util/delay.h>

void LCD_Cmd_Fun (unsigned char cmd){
	LCD_Data_Value=cmd;
	LCD_Cmd_Value &=~(1<<RS); //select command mode 
	LCD_Cmd_Value &=~(1<<RW); // select write mode
	LCD_Cmd_Value |=(1<<EN); // give a pulse
	_delay_ms(2);
	LCD_Cmd_Value &=~(1<<EN);
}
void LCD_Data_Fun (unsigned char data){
	LCD_Data_Value=data;
	LCD_Cmd_Value |=(1<<RS); //select data mode
	LCD_Cmd_Value &=~(1<<RW); // select write mode
	LCD_Cmd_Value |=(1<<EN); // give a pulse
	_delay_ms(2);
	LCD_Cmd_Value &=~(1<<EN);
}
void LCD_init(void){
	LCD_Cmd_Fun(0x38);
	_delay_ms(2);
	LCD_Cmd_Fun(0x01);
	_delay_ms(2);
	LCD_Cmd_Fun(0x02);
	_delay_ms(2);
	LCD_Cmd_Fun(0x06);
	_delay_ms(2);
	LCD_Cmd_Fun(0x80);
	_delay_ms(2);
}
void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Data_Fun (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Cmd_Fun((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Cmd_Fun((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Cmd_Fun (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Cmd_Fun (0x80);		/* Cursor at home position */
}