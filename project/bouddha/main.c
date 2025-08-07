#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Motor configuration 
    // Set PD3 (digital pin 3) as output to control the motor
    DDRD |= (1 << PD3);      // DDRD: Data Direction Register for Port D :1 = OUTPUT

    // Button configurqtion
    // Set PD2 (digital pin 2) as input with internal pull-up resistor
    DDRD &= ~(1 << PD2);     // Clear bit = input mode : 0 = INPUT
    PORTD |= (1 << PD2);     // Enable pull-up resistor

    while(1) {
        // If button is pressed (logic LOW on PD2)
        if(!(PIND & (1 << PD2))) {
            PORTD |= (1 << PD3);    // Set PD3 HIGH (motor ON)
        } else {
            PORTD &= ~(1 << PD3);   // Set PD3 LOW (motor OFF)
        }
        _delay_ms(100);  // Simple software debounce
    }
    return 0;
}