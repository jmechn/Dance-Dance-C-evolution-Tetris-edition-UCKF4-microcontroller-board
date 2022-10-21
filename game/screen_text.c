/**
 * @file screen_text.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Screen text module that provides the endscreen text for when a game is over.
 * @date 2022-10-14
 * 
 */
#include "screen_text.h"
#include "screen_text.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include <stdbool.h>
#include <stdint.h>

#define MESSAGE_RATE 40
#define RESET_TIMER 15000

char win_message[] = " =DYOU WIN  ";
char lose_message[] = " =(YOU LOSE  ";

/**
 * @brief Displays text on the screen when the game is over.
 * 
 * @param is_win bool value for if the player is the winner or loser.
 */
void display_win(bool is_win)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    
    if (is_win) {
        tinygl_text(win_message);
    } else {
        tinygl_text(lose_message);
    }

    uint64_t tick = 0;
    while(tick < RESET_TIMER)
    {
        pacer_wait();
        
        tinygl_update();
        tick++;
    }
    
    tinygl_clear();
    tinygl_update();
}
