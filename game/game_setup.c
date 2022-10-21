/**
 * @file game_setup.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Game setup module to set the game initial parameters.
 * @date 2022-10-14
 * 
 */

#include "button.h"
#include "ir_uart.h"
#include "game_setup.h"
#include <stdint.h>

#define PLAYER_ONE 1
#define PLAYER_TWO 2

/**
 * @brief Initialises the game. First player to press the button is player 1.
 * 
 */
uint8_t game_init (void)
{
    button_init();
    ir_uart_init();

    while (1) {
        button_update ();
        if (ir_uart_read_ready_p() && ir_uart_getc() == PLAYER_TWO) {
            return PLAYER_TWO;
        }
        if (button_push_event_p(0)) {
            ir_uart_putc(PLAYER_TWO);
            return PLAYER_ONE;
        }
    }
}
