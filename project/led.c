
#include <msp430.h>
#include "led.h"

void led_init(){
  P1DIR |= LEDS; //set LEDS to be outputs
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();
  enableWDTInterupts();
}

