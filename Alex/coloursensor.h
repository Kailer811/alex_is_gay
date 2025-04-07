#include <avr/io.h>

#define PIN_OUTPUT 1<<0
#define PIN_OE 1<<3
#define PIN_S0 1<<4
#define PIN_S1 1<<5
#define PIN_S2 1<<6
#define PIN_S3 1<<7
// use pin 22 - 26 (PB3 to PB7)

void colour_sensor_init()
{
  DDRL &= 0b11111110; // set PL0 pin 35 to input for colour sensor (ICP4)
  DDRB |= 0b11111000; // set pins 22 - 26 to output for all the pins
  PORTD |= PIN_OE | PIN_S1; // set OE HIGH to disable reading, S1 HIGH for 20% frequency
  PORTD &= ~PIN_S0; // set S0 LOW for 20% frequency scaling
  // TCNT4 = 0;
  // TCCR4A = 0;
  // TCCR4B |= 0b01000010; // Timer 4 on input capture mode, detect on rising edge
}
/*
void readColour(unsigned long &red, unsigned long &green, unsigned long &blue)
{
  PORTB &= ~PIN_OE; // set OE pin LOW to enable readings

  PORTB &= ~PIN_S2; // set S2 to LOW
  PORTB &= ~PIN_S3; // set S3 to LOW
  red = pulseIn(PIN_OUTPUT, LOW);
 delay(20);

  PORTB |= PIN_S2;
  PORTB |= PIN_S3;
  green = pulseIn(PIN_OUTPUT, LOW);
  delay(20);

  PORTB &= ~PIN_S2;
  blue = pulseIn(PIN_OUTPUT, LOW);
  delay(20);

  // need to either return a value, or carry out an instruction
  PORTB |= PIN_OE;
}
*/

void readColour(unsigned long &red, unsigned long &green, unsigned long &blue) {
 pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(35, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(23, HIGH);      
  digitalWrite(24, LOW);

 digitalWrite(25,HIGH);
 digitalWrite(26,LOW);
 //white = (double)pulseIn(sensorOut,LOW);
 delay(20);

  // Read Red Pulse Width
  digitalWrite(25,LOW);
  digitalWrite(26,LOW);
  red = (double)pulseIn(35,LOW);
  // Delay to stabilize sensor
  delay(20);

  // Read Green Pulse Width
  digitalWrite(25,HIGH);
  digitalWrite(26,HIGH);
  green = (double)pulseIn(35,LOW);
  // Delay to stabilize sensor
  delay(20);

  // Read Blue Pulse Width
  digitalWrite(25,LOW);
  digitalWrite(26,HIGH);
  blue = (double)pulseIn(35,LOW);
  // Delay to stabilize sensor
  delay(20);

  //colour = identifyColour((float)red/(float)red, (float)green/(float)red, (float)blue/(float)red);
  //delay(500);
}
