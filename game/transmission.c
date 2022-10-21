/**
 * @file transmission.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Transmission module that deals with inter-board commications.
 * @date 2022-10-14
 * 
 */
#include "system.h"
#include "arrow.h"
#include "ir_uart.h"
#include "transmission.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define ARROW 100
#define GAMEOVER 99
#define ROTATION_MULT 3
#define ARROW_SUB 1
#define POS_Y 9
#define SCREEN_HEIGHT 8

/**
 * @brief Encodes an arrow to an uint8_t.
 * 
 * @param arrow Arrow to be incoded for transmission.
 * @return uint8_t Encoded value of the arrow.
 */
uint8_t encode_arrow(Arrow_t* arrow) 
{
    uint8_t rotation_arrow = arrow->rotation * ROTATION_MULT;
    uint8_t x_arrow = (arrow->x) - ARROW_SUB;
    uint8_t encoded_arrow = rotation_arrow + x_arrow;
    return encoded_arrow;
}

/**
 * @brief Transmits an arrow to the other device.
 * 
 * @param arrow Arrow pointer to be transmitted.
 */
void transmit_arrow(Arrow_t* arrow) 
{
    ir_uart_putc(ARROW);
    uint8_t encoded_arrow = encode_arrow(arrow);
    ir_uart_putc(encoded_arrow);
    delete_arrow(arrow);
}

/**
 * @brief Decodes an encoded arrow from other transmitter and returns a new arrow pointer.
 * 
 * @param encoded_arrow An encoded arrow that has been received.
 * @return Arrow_t* New arrow object that has be allocated some memory.
 */
Arrow_t* decode_arrow(uint8_t encoded_arrow) 
{
    Rotation_t rotation = encoded_arrow / ROTATION_MULT;
    uint8_t x = encoded_arrow % ROTATION_MULT + ARROW_SUB;
    Arrow_t* arrow = new_arrow(x, POS_Y, rotation);
    return arrow;
}

/**
 * @brief Receives an arrow.
 * 
 * @return Arrow_t* The new received arrow pointer.
 */
Arrow_t* receive_arrow(void) 
{
    uint8_t encoded_arrow = ir_uart_getc();
    Arrow_t* new_arrow = decode_arrow(encoded_arrow);

    return new_arrow;
}

/**
 * @brief Returns greater true when there is data to be received.
 * 
 * @return bool true when nothing in buffer, false when there is something to be received.
 */
bool recieve_ready(void) 
{
    return ir_uart_read_ready_p();
}

/**
 * @brief Transmit that the game has been lost to the other player.
 * 
 */
void transmit_game_over(void) 
{
    ir_uart_putc(GAMEOVER);
}

/**
 * @brief Returns true if the other player has sent a GAMEOVER message.
 * 
 * @return true Game is over and player has won.
 * @return false Game is still playing.
 */
bool is_gameover(void)
{   
    char type = ARROW;
    if (recieve_ready()) {
        type = ir_uart_getc();
    }
    return type == GAMEOVER;
}

/**
 * @brief Transmission task for the sender.
 * 
 * @param outgoing_queue The queue of arrows that are needing to be sent.
 */
void sender_transmission (ArrowQueue_t* outgoing_queue)
{
    Node_t* node = outgoing_queue->head;
    Arrow_t* arrow;
    if (node != NULL) {
        arrow = node->arrow;

        if (arrow->y > SCREEN_HEIGHT) {
            arrow = queue_pop(outgoing_queue);
            transmit_arrow(arrow);
        }
    }
}

/**
 * @brief Transmission task for the receiver.
 * 
 * @param incoming_queue The incoming queue of arrows the player needs to match.
 */
void receiver_transmission (ArrowQueue_t* incoming_queue)
{
    Arrow_t* arrow;
    if (recieve_ready()) {
        arrow = receive_arrow();
        queue_append(incoming_queue, arrow);
    }
}