/**
 * @file level.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Level module that provides the level datatype and level functionality.
 * @date 2022-10-14
 * 
 */

#include "level.h"
#include <stdint.h>

#define START_SPEED 2
#define START_LIVES 3
#define START_MOVES 2
#define ARROW_SPEED_INC 1
#define MOVES_INC 2
/**
 * @brief Level initialisation.
 * 
 * @return Level_t the level properties for the round. 
 */
Level_t level_init(void)
{
    Level_t new_level;
    new_level.lives = START_LIVES;
    new_level.arrow_speed = START_SPEED;
    new_level.num_moves = START_MOVES;
    return new_level;
}

/**
 * @brief Updates the arrow speed and number of moves when the round is over.
 * 
 * @param game_level the current level object of the game.
 */
void level_update(Level_t* game_level)
{
    game_level->arrow_speed += ARROW_SPEED_INC;
    game_level->num_moves += MOVES_INC;
}