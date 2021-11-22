	.arch msp430g2553
	.p2align 1,0
	.text

	.global LED_off_on
	.extern P1OUT

LED_off_on:
	cmp #0, r12
	jne case_1
	and #65, &P1OUT
	pop r0
	
case1:	cmp #1, r12
	jne case2
	and #~64, &P1OUT
	bis #1, &P1OUT
	pop r0
	
case2:	cmp #2, r12
	jne default
	bis #64, &P1OUT
	and #~1, &P1OUT
	pop r0

def:	bis #~65, &P1OUT
	pop r0
