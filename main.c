/*
 * WEEk3-LCD.c
 *
 * Created: 10/24/2022 9:46:09 AM
 * Author : Mohamed
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

//LCD  initialize
#define LCD_DATA PORTB
#define LCD_CONT PORTA
#define en PA6
#define rs PA7

void LCD_cmd( char command)
{
	LCD_CONT = _BV(en);
	LCD_DATA = command;
	_delay_ms(1);
	LCD_CONT = 0x00;
	_delay_ms(1);
}
void init_LCD(void){
	
	
	
	LCD_cmd(0x38);				//Initialize 8bit mode
	_delay_ms(1);
	LCD_cmd(0x1);				//clear
	_delay_ms(1);
	LCD_cmd(0x6);
	_delay_ms(1);

	LCD_cmd(0x0E);				//First line start
	_delay_ms(1);
	
}
void LCD_write( char data){
	LCD_CONT = _BV(en) | _BV(rs);
	LCD_DATA = data;
	_delay_ms(1);
	LCD_CONT = _BV(rs);
	_delay_ms(1);
	
}
void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_write (str[i]);
	}
}
char *Keypad(void){
	PORTC = 0b11100000;
	if ((PIND & 0b00010000) == 0) return "SW1";
	if ((PIND & 0b00100000) == 0) return "SW2";
	if ((PIND & 0b01000000) == 0) return "SW3";
	if ((PIND & 0b10000000) == 0) return "SW4";
	_delay_ms(1);
	PORTC = 0b11010000;
	if ((PIND & 0b00010000) == 0) return "SW5";
	if ((PIND & 0b00100000) == 0) return "SW6";
	if ((PIND & 0b01000000) == 0) return "SW7";
	if ((PIND & 0b10000000) == 0) return "SW8";
	_delay_ms(1);
	PORTC = 0b10110000;
	if ((PIND & 0b00010000) == 0) return "SW9";
	if ((PIND & 0b00100000) == 0) return "SW10";
	if ((PIND & 0b01000000) == 0) return "SW11";
	if ((PIND & 0b10000000) == 0) return "SW12";
	_delay_ms(1);
	PORTC = 0b01110000;
	if ((PIND & 0b00010000) == 0) return "SW13";
	if ((PIND & 0b00100000) == 0) return "SW14";
	if ((PIND & 0b01000000) == 0) return "SW15";
	if ((PIND & 0b10000000) == 0) return "SW16";
	_delay_ms(1);
	return "NULL";
}
int main(void)
{
	DDRB = 0xFF	;							//out	data
	DDRA = 0xFF;							//out en,rs
	
	DDRC = 0xFF;
	DDRD = 0x00;
	
	init_LCD();								//initialize the LCD function
	_delay_ms(5);						//				  x
	LCD_cmd (0x0C);						//hide cursor "CSE_"
	
		
	LCD_String("keypad: ");
	while(1){
	
				 if(Keypad() !="NULL"){
						LCD_cmd(0x01);
						LCD_String("keypad: ");
						LCD_String(Keypad());
					    _delay_ms(500);	  
				 }
					
			 }
		return 0;
	}
