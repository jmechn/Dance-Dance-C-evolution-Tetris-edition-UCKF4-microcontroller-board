/**
 * @file input.h
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Input module to deal with player input on the navswitch.
 * @date 2022-10-14
 * 
 */

#ifndef INPUT_H
#define INPUT_H

#include "player.h"
#include "arrow.h"
#include <stdint.h>

/**
 * @brief Initalising the input module
 */
void input_init(void);

/**
 * @brief Checks for the player's input and changes arrows accordingly.
 *        Returns true if navswitch is pushed in.
 * 
 * @param player the current player of the game.
 * @return bool True if the navswitch button has been pushed.
 */
bool player_input(Player_t* player);

#endif
