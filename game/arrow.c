/**
 * @file arrow.c
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Arrow functionality and datastructures.
 * @date 2022-10-14
 * 
 */

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include <stdint.h>
#include "arrow.h"
#include <stdio.h>
#include <stdlib.h>

#define ARROW_DISTANCE 4

/**
 * @brief Pops an arrow off the head of the queue. Assumes that there is at least one node in the queue.
 * 
 * @param queue ArrowQueue_t to be popped.
 * @return Arrow_t* the Arrow pointer from the head of the queue.
 */
Arrow_t* queue_pop(ArrowQueue_t* queue)
{
    Node_t* node = queue->head;
    Arrow_t* arrow = node->arrow;
    if (node == queue->tail) {
        queue->tail = NULL;
    }
    queue->head = node->next_node;
    queue->head->prev_node = NULL;
    free(node);
    return arrow;
}

/**
 * @brief Clears the queue of all nodes/arrows and frees all memory.
 * 
 * @param queue The ArrowQueue to be cleared.
 */
void queue_clear(ArrowQueue_t* queue)
{
    while (queue->head != NULL) {
        delete_arrow(queue_pop(queue));
    }
}

/**
 * @brief Appends an arrow to the end of a queue.
 * 
 * @param queue ArrowQueue to be appened to.
 * @param arrow Arrow pointer to be added to the queue.
 */
void queue_append(ArrowQueue_t* queue, Arrow_t* arrow)
{
    Node_t* new_node = calloc(1, sizeof(Node_t));
    new_node->arrow = arrow;
    new_node->next_node = NULL;
    new_node->prev_node = queue->tail;

    if (queue->tail == NULL) {
        queue->head = new_node;
    } else {
        queue->tail->next_node = new_node;
    }
    queue->tail = new_node;
}

/**
 * @brief Moves an arrow down the screen by one and updates display.
 * 
 * @param arrow Arrow to be moved down.
 */
void move_arrow_down(Arrow_t* arrow)
{
    update_arrow(arrow, 0);
    arrow->y -= 1;
    update_arrow(arrow, 1);
}

/**
 * @brief Moves an arrow up the screen by one and updates display.
 * 
 * @param arrow Arrow to be moved up.
 */
void move_arrow_up(Arrow_t* arrow)
{
    update_arrow(arrow, 0);
    arrow->y += 1;
    update_arrow(arrow, 1);
}

/**
 * @brief Moves an arrow to the left and updates diplay.
 * 
 * @param arrow Arrow to be shifted to the left by one position.
 */
void move_arrow_left(Arrow_t* arrow)
{
    if (arrow->x != 3) {
        update_arrow(arrow, 0);
        arrow->x += 1;
        update_arrow(arrow, 1);
    }
}

/**
 * @brief Moves an arrow to the right and updates diplay.
 * 
 * @param arrow Arrow to be shifted to the right by one position.
 */
void move_arrow_right(Arrow_t* arrow)
{
    if (arrow->x != 1) {
        update_arrow(arrow, 0);
        arrow->x -= 1;
        update_arrow(arrow, 1);
    }
}

/**
 * @brief Rotates an arrow clockwise and updates diplay.
 * 
 * @param arrow Arrow to be rotated.
 */
void rotate_clockwise(Arrow_t* arrow)
{
    update_arrow(arrow, 0);
    if (arrow->rotation == RIGHT) {
        arrow->rotation = DOWN;
    } else {
        arrow->rotation += 1;
    }
    update_arrow(arrow, 1);
}

/**
 * @brief Rotates an arrow anticlockwise and updates diplay.
 * 
 * @param arrow Arrow to be rotated.
 */
void rotate_anticlockwise(Arrow_t* arrow)
{
    rotate_clockwise(arrow);
    rotate_clockwise(arrow);
    rotate_clockwise(arrow);
}

/**
 * @brief Move all incomming/outgoing arrows by one position at once.
 * 
 * @param queue The queue of arrows to be moved.
 * @param direction Direction_t enum value for the direction of movement.
 */
void move_arrows(ArrowQueue_t* queue, Direction_t direction)
{
    Node_t* current_node = queue->head;
    Arrow_t* current_arrow = current_node->arrow;
    Node_t* prev_node = current_node->prev_node;

    // Moves each arrow in the queue if its distance is greater than ARROW_DISTANCE to previous arrow.
    while (current_node != NULL) {
        if (prev_node == NULL || current_arrow->y + ARROW_DISTANCE < prev_node->arrow->y) {
            switch (direction) {
                case TOWARDS:
                    move_arrow_down(current_arrow);
                    break;
                case AWAY:
                    move_arrow_up(current_arrow);
                    break;
                default:
                    break;
            }
        }
        current_node = current_node->next_node;
        current_arrow = current_node->arrow;
        prev_node = current_node->prev_node;
    }
}

/**
 * @brief Updates the arrows position diplayed on the screen.
 * 
 * @param arrow Arrow to be updated on the screen.
 * @param state bool for being on or off.
 */
void update_arrow(Arrow_t* arrow, uint8_t state)
{
    switch (arrow->rotation) {
    case DOWN:
        tinygl_draw_point(tinygl_point(arrow->x, arrow->y - 1), state);
        tinygl_draw_point(tinygl_point(arrow->x - 1, arrow->y), state);
        tinygl_draw_point(tinygl_point(arrow->x + 1, arrow->y), state);
        break;
    
    case UP:
        tinygl_draw_point(tinygl_point(arrow->x, arrow->y + 1), state);
        tinygl_draw_point(tinygl_point(arrow->x - 1, arrow->y), state);
        tinygl_draw_point(tinygl_point(arrow->x + 1, arrow->y), state);
        break;
    
    case LEFT:
        tinygl_draw_point(tinygl_point(arrow->x + 1, arrow->y), state);
        tinygl_draw_point(tinygl_point(arrow->x, arrow->y + 1), state);
        tinygl_draw_point(tinygl_point(arrow->x, arrow->y - 1), state);
        break;
    
    case RIGHT:
        tinygl_draw_point(tinygl_point(arrow->x - 1, arrow->y), state);
        tinygl_draw_point(tinygl_point(arrow->x, arrow->y + 1), state);
        tinygl_draw_point(tinygl_point(arrow->x, arrow->y - 1), state);
        break;

    default:
        break;
    }
}

/**
 * @brief Equates if two arrows are equal.
 * 
 * @param arrow1 First arrow.
 * @param arrow2 Second arrow.
 * @return true Arrows have the same cooridinates and rotation.
 * @return false Arrows are ether of different rotation, different cooridinates or both.
 */
bool is_arrow_equal(Arrow_t* arrow1, Arrow_t* arrow2)
{
    bool x_equal = arrow1->x == arrow2->x;
    bool y_equal = arrow1->y == arrow2->y;
    bool rotation_equal = arrow1->rotation == arrow2->rotation;

    return x_equal && y_equal && rotation_equal;
}

/**
 * @brief Returns True if the player missed the arrow.
 * 
 * @param player The players arrow
 * @param arrow The arrow that might've been missed.
 * @return true The player has missed this arrow.
 * @return false The arrow has yet to pass the player.
 */
bool arrow_missed(Arrow_t* player, Arrow_t* arrow)
{
    return player->y > arrow->y;
}

/**
 * @brief Returns a new arrow initilised to the provided values and allocated the correct memory.
 * 
 * @param x x-position.
 * @param y y-position.
 * @param rotation Rotation_t for the arrow rotation.
 * @return Arrow_t* pointer to the newly created arrow.
 */
Arrow_t* new_arrow(uint8_t x, uint8_t y, Rotation_t rotation)
{
    Arrow_t* arrow = calloc(1, sizeof(Arrow_t));
    arrow->x = x;
    arrow->y = y;
    arrow->rotation = rotation;

    return arrow;
}

/**
 * @brief Deletes an arrow from the display and frees the memory the arrow was allocated.
 * 
 * @param arrow Arrow to be deleted.
 */
void delete_arrow(Arrow_t* arrow)
{
    update_arrow(arrow, 0);
    free(arrow);
}