/**
 * @file input.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Input module to deal with player input on the navswitch.
 * @date 2022-10-14
 * 
 */

#include "input.h"
#include "arrow.h"
#include "player.h"
#include "navswitch.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initalising the input module
 */
void input_init(void)
{
    navswitch_init();
}

/**
 * @brief for the player's input and changes arrows accordingly.
 *        Returns true if navswitch is pushed in.
 * 
 * @param player the current player of the game.
 * @return bool True if the navswitch button has been pushed.
 */
bool player_input(Player_t* player)
{
    navswitch_update();
    
    if (navswitch_push_event_p (NAVSWITCH_NORTH))
        rotate_anticlockwise(&(player->player_arrow));

    if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        rotate_clockwise(&(player->player_arrow));

    if (navswitch_push_event_p (NAVSWITCH_EAST))
        move_arrow_left(&(player->player_arrow));

    if (navswitch_push_event_p (NAVSWITCH_WEST))
        move_arrow_right(&(player->player_arrow));

    if (navswitch_push_event_p (NAVSWITCH_PUSH) && player->is_sender && player->moves > 0){
        dec_moves(player);
        return true;
    }
    return false;
}
