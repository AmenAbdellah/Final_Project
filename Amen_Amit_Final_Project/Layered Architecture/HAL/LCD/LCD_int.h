#ifndef LCD_INT_H_
#define LCD_INT_H_


#define EN PC2
#define RW PC1
#define RS PC0

#define LCD_Data_Dir DDRA
#define LCD_Data_Value PORTA

#define LCD_Cmd_Dir DDRC
#define LCD_Cmd_Value PORTC

void LCD_Cmd_Fun (unsigned char cmd);
void LCD_Data_Fun (unsigned char data);
void LCD_init(void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();

#endif