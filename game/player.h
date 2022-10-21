/**
 * @file player.h
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Player module that provides the player datatype and player functionality.
 * @date 2022-10-14
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "arrow.h"
#include "level.h"
#include <stdint.h>

/**
 * @brief Struct for a player object.
 */
typedef struct {
    uint8_t lives;
    uint8_t moves;
    bool is_sender;
    Arrow_t player_arrow;

} Player_t;

/**
 * @brief Decreases the lives of the player by one.
 * 
 * @param player player to be updated.
 */

void update_lives(Player_t* player);

/**
 * @brief Decreases the player moves by one.
 * 
 * @param player player to be updated.
 */
void dec_moves (Player_t* player);

/**
 * @brief Updates the role of the player.
 * 
 * @param player player to be updated.
 */
void player_update (Player_t* player, uint8_t num_moves);

/**
 * @brief Player module which holds the player's information 
 * 
 * @param num_players number of players that ready in the game.
 * @param game_level the game level object.
 * @return Player_t the player object.
 */
Player_t player_init(uint8_t num_players, Level_t* game_level);

/**
 * @brief Returns true if the player has run out of lives.
 * 
 * @param player The player to be tested.
 * @return true Player is dead.
 * @return false Player is still alive.
 */
bool is_player_dead(Player_t* player);

#endif