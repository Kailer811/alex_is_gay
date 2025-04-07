#include <avr/io.h>

// To calibrate if necessary
#define LEFT_CLAW_OPEN 1200
#define LEFT_CLAW_CLOSE 400
#define RIGHT_CLAW_OPEN 600
#define RIGHT_CLAW_CLOSE 1300
#define ARM_OPEN 1200
#define ARM_CLOSE 400

void arm_init() {
  DDRL |= 0b00011100; // set the pin 46 45 44 on arduino mega
  TCCR5A = 0b10100010; // Phase correct PWM with ICR5 as TOP
  ICR5 = 19999; // 50 Hz --> 0.02 s

  // 1 ms pulse is 999 for 0, 1.5 ms is 1499 for 90, 2 ms is 1999 for 180
  OCR5A = LEFT_CLAW_OPEN; // left claw angle, to be connected to OC5A
  OCR5B = RIGHT_CLAW_OPEN;
  OCR5C = ARM_CLOSE; // right claw angle, to be connected to OC5B
  TCCR5B = 0b00010010; // Prescaler 8
  
}

void arm_open() {
	OCR5A = LEFT_CLAW_OPEN;
	OCR5B = RIGHT_CLAW_OPEN;
}

void arm_close() {
   OCR5A = LEFT_CLAW_CLOSE;
   OCR5B = RIGHT_CLAW_CLOSE;
}

void release() {
	OCR5C = ARM_OPEN;
}
