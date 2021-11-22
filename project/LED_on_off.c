#include <msp430.h>
#include "led.h"

void LED_off_on(int input){
  switch(input){
  case 0:  //both leds on
    P1OUT |= LEDS;
    break;
  case 1:  //red led on
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  case 2:  //green led on 
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  default:  //both leds off
    P1OUT &= LEDS;
    break;
  }
}
