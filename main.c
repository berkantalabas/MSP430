#include "msp430.h"
int numbers;

int main() {
  // Stop watchdog timer to prevent reset time out
  WDTCTL = WDTPW + WDTHOLD;

  // Configure Clock
  DCOCTL = CALDCO_1MHZ;
  BCSCTL1 = CALBC1_1MHZ;

  // Configure Timer
  // 0.5s using SMCLK and div 8
  // timerValue = (0.5 * 1/8 * 1000000) - 1 = 62499
  TACCR0 = 62499;
  TACTL = TASSEL_2 | ID_3 | MC_1 | TACLR;

  // Configure GPIO
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;

  // Process
  while(1) {
    if (TACTL & TAIFG) {
      P1OUT ^= BIT0;
      TACTL &= ~TAIFG;
      ARMUT ^= BIT0;
    }
  }
}
