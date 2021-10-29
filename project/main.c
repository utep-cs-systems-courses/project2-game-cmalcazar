#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"


#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0 | BIT6)
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)



int main(){

  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  P1REN |= SWITCHES;
  P1IE |= SWITCHES;
  P1OUT |= SWITCHES;
  P1DIR &= ~SWITCHES;
  
  configureClocks();
  buzzer_init();
  or_sr(0x18);  //CPU off, GIE on
}

void

switch_interrupt_handler()
{
  char p1val = P1IN;/* switch is in P1 */

  /* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);/* if switch down, sense up */

  /* up=red, down=green */
  if (p1val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}


/* Switch on P1 (S2) */
void

__interrupt_vec(PORT1_VECTOR) Port_1(){
  
  if (P1IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
