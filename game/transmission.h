/**
 * @file transmission.h
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Transmission module that deals with inter-board commications.
 * @date 2022-10-14
 * 
 */

#include "arrow.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Transmits an arrow to the other device.
 * 
 * @param arrow Arrow pointer to be transmitted.
 */
void transmit_arrow(Arrow_t* arrow);

/**
 * @brief Receives an arrow.
 * 
 * @return Arrow_t* The new received arrow pointer.
 */
Arrow_t* receive_arrow(void);

/**
 * @brief Transmit that the game has been lost to the other player.
 * 
 */
void transmit_game_over(void);

/**
 * @brief Returns true if the other player has sent a GAMEOVER message.
 * 
 * @return true Game is over and player has won.
 * @return false Game is still playing.
 */
bool is_gameover(void);

/**
 * @brief Transmission task for the sender.
 * 
 * @param outgoing_queue The queue of arrows that are needing to be sent.
 */
void sender_transmission (ArrowQueue_t* outgoing_queue);

/**
 * @brief Transmission task for the receiver.
 * 
 * @param incoming_queue The incoming queue of arrows the player needs to match.
 */
void receiver_transmission (ArrowQueue_t* incoming_queue);