/**
 * @file game.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Main module that contains main game loop and tasks.
 * @date 2022-10-14
 * 
 */
#include "system.h"
#include "arrow.h"
#include "tinygl.h"
#include "pacer.h"
#include "game_setup.h"
#include "player.h"
#include "level.h"
#include "input.h"
#include <stdio.h>
#include "transmission.h"
#include "screen_text.h"

#define PACER_RATE 1000
#define DISPLAY_TASK_RATE 300
#define CHECK_PLAYER_TASK 10
#define GET_INPUT_TASK 250
#define TRANSMITTION_TASK 20


ArrowQueue_t outgoing_queue = {.head = NULL, .tail = NULL};
ArrowQueue_t incoming_queue = {.head = NULL, .tail = NULL};

// initialise player as global variable
uint8_t player_num;
Player_t player;
Level_t game_level;
bool gameover = false;

/**
 * @brief Sets up the game and decides player number.
 * 
 */
void game_setup(void)
{
    player_num = game_init();
    game_level = level_init();
    player = player_init(player_num, &game_level);
}

/**
 * @brief Checks payer data for let the game know when to move to a new level, sets the blue LED light and when the game is over.
 * 
 */
void check_player_task(void)
{
    if (player.is_sender) {
        if (player.moves <= 0 && outgoing_queue.head == NULL) {
            level_update(&game_level);
            player_update(&player, game_level.num_moves);  
        }
    } else {
        if (player.moves <= 0 && incoming_queue.tail == NULL) {
            level_update(&game_level);
            player_update(&player, game_level.num_moves);
        }
    }

    if (is_player_dead(&player)) {
        gameover = true;
        transmit_game_over();
    }
}

/**
 * @brief Handles the inputs queries for the game. Adds a new arrow to the outgoin queue if NAVSWITCH is pushed and the player is sender.
 * 
 */
void get_input_task(void)
{
    bool btn_pressed = player_input(&player);
    if (btn_pressed) {
        Arrow_t* player_arrow = &player.player_arrow;
        Arrow_t* arrow = new_arrow(player_arrow->x, player_arrow->y, player_arrow->rotation);
        queue_append(&outgoing_queue, arrow);
    }
}

/**
 * @brief Checks if incoming arrows have been missed or matched correctly.
 * 
 */
void check_arrow_match(void)
{
    Node_t* incoming_head = incoming_queue.head;

    if (!player.is_sender && incoming_head != NULL) {
        Arrow_t* incoming_arrow = incoming_head->arrow;

        if (is_arrow_equal(&player.player_arrow, incoming_arrow)) {
            incoming_arrow = queue_pop(&incoming_queue);
            delete_arrow(incoming_arrow);
            dec_moves(&player);

        } else if (arrow_missed(&player.player_arrow, incoming_arrow)) {
            incoming_arrow = queue_pop(&incoming_queue);
            delete_arrow(incoming_arrow);
            update_lives(&player);
            dec_moves(&player);
        }
    }
}

/**
 * @brief Main transmission task for sending and receiving arrows.
 * 
 */
void transmission_task (void)
{
    if (is_gameover()) {
        gameover = true;
    } else if (player.is_sender) {
        sender_transmission(&outgoing_queue);
    } else {
        receiver_transmission(&incoming_queue);
    }

}

/**
 * @brief Moves all the arrows in the outgoing and incoming queues.
 * 
 */
void move_arrows_task(void)
{
    if (player.is_sender) {
        move_arrows(&outgoing_queue, AWAY);
    } else {
        move_arrows(&incoming_queue, TOWARDS);
    }
    update_arrow(&(player.player_arrow), 1);
}

/**
 * @brief When the game ends, this function is called to reset the game so the players can play again.
 * 
 */
void game_over_task(void)
{
    gameover = false;
    display_win(player.lives>0);
    game_setup();
    queue_clear(&incoming_queue);
    queue_clear(&outgoing_queue);
}

/**
 * @brief Main loop and round robin scheduler
 * 
 * @return int 
 */
int main (void)
{
    system_init ();
    input_init();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    game_setup();

    int tick = 0;

    while (!gameover)
    {
        pacer_wait();
        
        if (tick % (PACER_RATE / DISPLAY_TASK_RATE) == 0) {
            tinygl_update();
        }
        if (tick % (PACER_RATE / GET_INPUT_TASK) == 0) {
            get_input_task();
        }
        if (tick % (PACER_RATE / game_level.arrow_speed) == 0) {
            move_arrows_task();
        }
        if (tick % (PACER_RATE / TRANSMITTION_TASK) == 0) {
            transmission_task();
        }

        if (tick % (PACER_RATE / CHECK_PLAYER_TASK) == 0) {
            check_player_task();
            check_arrow_match();
        }
        if (gameover) {
            game_over_task();
        }

        tick++;
    }
}
