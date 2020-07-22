/*
 * File:   main.c
 * Author: MARCELO DELGADO DEL CARPIO
 *
 * Created on 12 de junio de 2019, 04:49 PM
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned int ctrl_1=0;
volatile unsigned int ctrl_2=0;
volatile unsigned int ctrl_3=0;

ISR(PCINT2_vect){
    
    /*------- BAJOS ---------*/
    if(!(PIND & (1<<PIND0)))
    {
        if(ctrl_1==3){
            ctrl_1=0;
        }
        else{
            ctrl_1++;
        }
    }
    if(!(PIND & (1<<PIND1)))
    {
        if(ctrl_1==0){
            ctrl_1=3;
        }
        else{
            ctrl_1--;
        }
    }
    /*------- ALTOS ---------*/
    if(!(PIND & (1<<PIND2)))
    {
        if(ctrl_2==3){
            ctrl_2=0;
        }
        else{
            ctrl_2++;
        }
    }
    if(!(PIND & (1<<PIND3)))
    {
        if(ctrl_2==0){
            ctrl_2=3;
        }
        else{
            ctrl_2--;
        }
    }
    /*------- VOLUMEN ---------*/
    if(!(PIND & (1<<PIND4)))
    {
        if(ctrl_3==3){
            ctrl_3=0;
        }
        else{
            ctrl_3++;
        }
    }
    if(!(PIND & (1<<PIND5)))
    {
        if(ctrl_3==0){
            ctrl_3=3;
        }
        else{
            ctrl_3--;
        }
    }
}

int main(void) {
    /* Port configuration */
    DDRD = 0xC0;    // PORTD output/input
    DDRC = 0x3F;    // PORTC as output
    DDRB = 0xFF;    // PORTB as output
    PORTC = 0x00;
    PORTB = 0x00;
    PORTD |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);	// Enable pull-up resistors
    /* Interrupts */
    PCICR |= 1<<PCIE2;  // Enable PCINT[23:16] interrupt
    PCMSK2 |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);    // Enable PCINT[21:16]
	
    sei();  //Enable Global Interrupt
    
    while (1) {
        switch(ctrl_1){ // BAJOS 1
            case 0:
                PORTB |= (1<<PB0);
                PORTB &=~ (1<<PB1);
                PORTB &=~ (1<<PB2);
                PORTB &=~ (1<<PB3);
                break;
            case 1:
                PORTB &=~ (1<<PB0);
                PORTB |= (1<<PB1);
                PORTB &=~ (1<<PB2);
                PORTB &=~ (1<<PB3);
                break;
            case 2:
                PORTB &=~ (1<<PB0);
                PORTB &=~ (1<<PB1);
                PORTB |= (1<<PB2);
                PORTB &=~ (1<<PB3);
                break;
            case 3:
                PORTB &=~ (1<<PB0);
                PORTB &=~ (1<<PB1);
                PORTB &=~ (1<<PB2);
                PORTB |= (1<<PB3);
                break;
            default:
                PORTB = 0x00;
        }
        switch(ctrl_2){ // BAJOS 2
            case 0:
                PORTB |= (1<<PB4);
                PORTB &=~ (1<<PB5);
                PORTB &=~ (1<<PB6);
                PORTB &=~ (1<<PB7);
                break;
            case 1:
                PORTB &=~ (1<<PB4);
                PORTB |= (1<<PB5);
                PORTB &=~ (1<<PB6);
                PORTB &=~ (1<<PB7);
                break;
            case 2:
                PORTB &=~ (1<<PB4);
                PORTB &=~ (1<<PB5);
                PORTB |= (1<<PB6);
                PORTB &=~ (1<<PB7);
                break;
            case 3:
                PORTB &=~ (1<<PB4);
                PORTB &=~ (1<<PB5);
                PORTB &=~ (1<<PB6);
                PORTB |= (1<<PB7);
                break;
            default:
                PORTB = 0x00;
        }
        switch(ctrl_3){ // VOLUMEN
            case 0:
                PORTC |= (1<<PC0);
                PORTC &=~ (1<<PC1);
                PORTC &=~ (1<<PC2);
                PORTC &=~ (1<<PC3);
                break;
            case 1:
                PORTC &=~ (1<<PC0);
                PORTC |= (1<<PC1);
                PORTC &=~ (1<<PC2);
                PORTC &=~ (1<<PC3);
                break;
            case 2:
                PORTC &=~ (1<<PC0);
                PORTC &=~ (1<<PC1);
                PORTC |= (1<<PC2);
                PORTC &=~ (1<<PC3);
                break;
            case 3:
                PORTC &=~ (1<<PC0);
                PORTC &=~ (1<<PC1);
                PORTC &=~ (1<<PC2);
                PORTC |= (1<<PC3);
                break;
            default:
                PORTC = 0x00;
        }
    }
}
