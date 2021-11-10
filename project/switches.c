#include <msp430.h>
#include <led.h>
#include <buzzer.h>
#include <switches.h>

void switch_update_interrupt_sense(){
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val & SWITCHES);

  return p2val;
}

void
_interrupt_vec(PORT2_VECTOR) PORT2(){
  if (P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

int sw1Down = 0;
int sw2Down = 0;
int sw3Down = 0;
int sw4Down = 0;

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();

  int prev1 = sw1Down;
  int prev2 = sw2Down;
  int prev3 = sw3Down;
  int prev4 = sw4Down;

  
  sw1Down = (p2Val & SW1) ? 0 : 1;
  sw2Down = (p2Val & SW2) ? 0 : 1;
  sw3Down = (p2Val & SW3) ? 0 : 1;
  sw4Down = (p2Val & SW4) ? 0 : 1;
  
  else{
    buzzer_set_period(0);
  }

}

void
_interrupt_vec(WDT_VECTOR) WDT(){
  if (sw1Down == 1){
    playSong();
    P1OUT |= LED_GREEN;
  }
  else if (sw2Down == 1){
    P1OUT |= LED_RED;
    P1OUT |= LED_GREEN
  }
  else if (sw3Down == 1){
    buzzer_set_period(1000);
  }
  else if (sw4Down == 1){
    buzzer_set_period(1100);
  }
  else if (sw1Down == 1 && sw2Down == 1){
    buzzer_set_period(0);
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_GREEN;
  }
