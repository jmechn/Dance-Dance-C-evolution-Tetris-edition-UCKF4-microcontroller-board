/**
 * @file level.h
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Level module that provides the level datatype and level functionality.
 * @date 2022-10-14
 * 
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>

/**
 * @brief Struct for the game levels.
 */

typedef struct {
    uint8_t level;
    uint8_t lives;
    uint32_t arrow_speed;
    uint8_t num_moves;

} Level_t;


/**
 * @brief Level initialisation.
 * 
 * @return Level_t the level properties for the round. 
 */
Level_t level_init(void);

/**
 * @brief Updates the level, arrow speed and number of moves.
 * 
 * @param game_level the current level object of the game.
 */
void level_update(Level_t* game_level);

#endif