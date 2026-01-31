#ifndef __DMI_GPIO_H__
#define __DMI_GPIO_H__

#include <STC8G.H>
/* com */

// P3.0 as RxD
// P3.1 as TxD
sbit SERIAL_RXD   = P3 ^ 0;
sbit SERIAL_TXD   = P3 ^ 1;

/* i2c */
sbit I2C_SCL      = P1 ^ 2;
sbit I2C_SDA      = P1 ^ 3;

/* button */
sbit BUTTON_INT0  = P3 ^ 2;
sbit BUTTON_INT1  = P3 ^ 3;
sbit BUTTON_A     = P3 ^ 4;
sbit BUTTON_B     = P3 ^ 5;
sbit BUTTON_KEY   = P3 ^ 6;

/* led */
sbit LED_DIM1     = P1 ^ 1;
sbit LED_DIM2     = P1 ^ 0;


void gpio_initialize (void);


#endif
