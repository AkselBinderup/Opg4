#include "ProjectDefines.h"
#include "Uart.h"

void start_uart(void) {
    UBRR0 = BAUD_9600;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    UBRR1 = BAUD_9600;
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void uart0_send_tekst(const char* tekst) {
    for (int i = 0; tekst[i] != '\0'; i++) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = tekst[i];
    }
}

void uart1_send_tekst(const char* tekst) {
    for (int i = 0; tekst[i] != '\0'; i++) {
        while (!(UCSR1A & (1 << UDRE1)));
        UDR1 = tekst[i];
    }
}

ISR(USART0_RX_vect) {
    char c = UDR0;
    if (c >= 'a' && c <= 'z') {
        c = c - 32; 
    }
    UDR0 = c;  
}

ISR(USART1_RX_vect) {
    char c = UDR1;
    if (c >= 'A' && c <= 'Z') {
        c = c + 32; 
    }
    UDR1 = c;  
}