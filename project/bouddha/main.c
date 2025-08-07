#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void setup(){
    // Motor configuration 
    // Set PD3 (digital pin 3) as output to control the motor
    DDRD |= (1 << PD3);      // DDRD: Data Direction Register for Port D :1 = OUTPUT

    // Button configurqtion
    // Set PD2 (digital pin 2) as input with internal pull-up resistor
    DDRD &= ~(1 << PD2);     // Clear bit = input mode : 0 = INPUT
    PORTD |= (1 << PD2);     // Enable pull-up resistor

    // Interruption
    // Configure external interrupt INT0 on falling edge INT0 (PD2)
    EICRA |= (1 << ISC01);  // ISC01=1, ISC00=0 → falling edge
    EIMSK |= (1 << INT0);   // Enable external interrupt INT0

    sei();                  // Set global interrupt flag (enable all interrupts)
}

int main(void) {
    setup();

    while(1) {
        sleep_mode();
    }
    return 0;
}

// This function runs automatically when INT0 is triggered
ISR(INT0_vect) {
    // Toggle PD3 (if ON -> OFF, if OFF -> ON)
    PORTD ^= (1 << PD3);  // XOR to invert the current state
}