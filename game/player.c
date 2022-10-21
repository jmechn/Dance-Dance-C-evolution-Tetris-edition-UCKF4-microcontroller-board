/**
 * @file player.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Player module that provides the player datatype and player functionality.
 * @date 2022-10-14
 * 
 */

#include "player.h"
#include "led.h"
#include <stdint.h>

#define DEFAULT_X 2
#define DEFAULT_Y 1

/**
 * @brief Initialises the main player object.
 * 
 * @param num_players number of players that ready in the game.
 * @param game_level the game level object.
 * @return Player_t the player object.
 */
Player_t player_init(uint8_t num_players, Level_t* game_level)
{
    led_init();
    Player_t newPlayer;
    newPlayer.lives = game_level->lives;
    newPlayer.moves = game_level->num_moves;

    if (num_players == 1) {
        newPlayer.is_sender = false;
        led_set(LED1, false);
    } else {
        newPlayer.is_sender = true;
        led_set(LED1, true);
    }

    newPlayer.player_arrow = *new_arrow(DEFAULT_X, DEFAULT_Y, UP);
    return newPlayer;
}

/**
 * @brief Decreases the lives of the player by one.
 * 
 * @param player player to be updated.
 */
void update_lives(Player_t* player)
{
    player->lives--;
}

/**
 * @brief Decreases the player moves by one.
 * 
 * @param player player to be updated.
 */
void dec_moves (Player_t* player)
{
    player->moves--;
}

/**
 * @brief Updates the role of the player at the end of a round.
 * 
 * @param player player to be updated.
 * @param num_moves number of moves to be updated to.
 */
void player_update (Player_t* player, uint8_t num_moves)
{
    player->moves = num_moves;
    if (player->is_sender) {
        player->is_sender = false;
        led_set(LED1, false);
    } else {
        player->is_sender = true;
        led_set(LED1, true);
    }
}

/**
 * @brief Returns true if the player has run out of lives.
 * 
 * @param player The player to be tested.
 * @return true Player is dead.
 * @return false Player is still alive.
 */
bool is_player_dead(Player_t* player)
{
    return player->lives == 0;
}