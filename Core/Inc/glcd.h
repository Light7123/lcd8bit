#ifndef _GLCD_H
#define _GLCD_H

#include "stm32f1xx.h"
#include "font.h"
#include "gpio.h"

#define T  1
//Data Pins
#define D0_PIN_NUMBER  0
#define D1_PIN_NUMBER  1
#define D2_PIN_NUMBER  2
#define D3_PIN_NUMBER  3
#define D4_PIN_NUMBER  4
#define D5_PIN_NUMBER  5
#define D6_PIN_NUMBER  6
#define D7_PIN_NUMBER  7
//Data Port
#define DATA_PORT  GPIOA
//Control Port
#define CTRL_PORT  GPIOB
//Select Column Port
#define SECO_PORT  GPIOC
//Control Pins
#define DI_PIN_NUMBER  0
#define RW_PIN_NUMBER  1
#define E_PIN_NUMBER   2
//Select Column Pins
#define CS1_PIN_NUMBER   4
#define CS2_PIN_NUMBER   5

//GLCD Function
void glcd_on(void );
void glcd_off(void);
void glcd_putchar(unsigned char data,unsigned char j);
void glcd_putImage(unsigned char data,unsigned char j);
void glcd_puts(char *str,char x,char y);
void glcd_int_puts(int *str, char x, char y);
void glcd_puts_point(char x,char y,char w);
void glcd_disp_Image(unsigned char *str,char x1,char x2, char y1,char y2);
void glcd_gotoxy(unsigned char x, unsigned char y);
void glcd_clear_all(void);
void glcd_clrearline(unsigned line);
void Delay(int t);
void send_command(unsigned char data);
void goto_row(unsigned char y);
void goto_column(unsigned char x);
void glcd_clear_here(char x1,char x2, char y1,char y2);
// Functions Code:

#endif
