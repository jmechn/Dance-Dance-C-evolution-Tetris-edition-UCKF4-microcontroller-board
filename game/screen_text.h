/**
 * @file screen_text.h
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Screen text module that provides the endscreen text for when a game is over.
 * @date 2022-10-14
 * 
 */

#ifndef SCREEN_TEXT_H
#define SCREEN_TEXT_H

#include <stdbool.h>

/**
 * @brief Displays text on the screen when the game is over.
 * 
 * @param is_win bool value for if the player is the winner or loser.
 */
void display_win(bool is_win);

#endif