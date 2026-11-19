#include "ProjectDefines.h"
#include "Timer.h"
#include "Uart.h"
#include "ExtInt.h"
#include "./driver/ssd1306.h"

int main(void) {
    start_timer();
    start_uart();
    start_ext_int0();
    
    // SSD1306_Init(0x3C); 
    // SSD1306_ClearScreen();
    // SSD1306_SetPosition(0, 0);
    // SSD1306_DrawString("Antal tryk: 0");
    // SSD1306_UpdateScreen();  

    sei();

    uint16_t sekunder = 0;
    char tekst_buffer[40];

    while (1) {
        if (sekund_flag == 1) {
            sekund_flag = 0;
            sekunder++;

            sprintf(tekst_buffer, "Sekunder efter opstart: %u\r\n", sekunder);
            uart1_send_tekst(tekst_buffer);
        }

        if (opdater_knap_visninger == 1) {
            opdater_knap_visninger = 0;

            sprintf(tekst_buffer, "Ekstern Interrupt taeller: %u\r\n", knap_taeller);
            uart0_send_tekst(tekst_buffer);
            uart1_send_tekst(tekst_buffer);

            sprintf(tekst_buffer, "Antal tryk: %u", knap_taeller);
            // SSD1306_ClearScreen();
            // SSD1306_SetPosition(0, 0);
            // SSD1306_DrawString(tekst_buffer);
            // SSD1306_UpdateScreen();
        }
    }
}