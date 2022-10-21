/**
 * @file arrow.h
 * @author Bede Nathan | nrb55
 * @author Jaymee Chen | jch423
 * @brief Arrow functionality and datastructures.
 * @date 2022-10-14
 * 
 */

#ifndef ARROW_H
#define ARROW_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DOWN,
    LEFT,
    UP,
    RIGHT
} Rotation_t;

typedef enum {
    AWAY,
    TOWARDS
} Direction_t;

typedef struct {
    uint8_t x;
    uint8_t y;
    Rotation_t rotation;
} Arrow_t;

struct Node_s{
    struct Node_s* next_node;
    struct Node_s* prev_node;
    Arrow_t* arrow;
};

typedef struct Node_s Node_t;

typedef struct {
    Node_t* head;
    Node_t* tail;
} ArrowQueue_t;

/**
 * @brief Move all incomming/outgoing arrows by one position at once.
 * 
 * @param queue The queue of arrows to be moved.
 * @param direction Direction_t enum value for the direction of movement.
 */
void move_arrows(ArrowQueue_t* queue, Direction_t directon);

/**
 * @brief Pops an arrow off the head of the queue. Assumes that there is at least one node in the queue.
 * 
 * @param queue ArrowQueue_t to be popped.
 * @return Arrow_t* the Arrow pointer from the head of the queue.
 */
Arrow_t* queue_pop(ArrowQueue_t* queue);

/**
 * @brief Clears the queue of all nodes/arrows and frees all memory.
 * 
 * @param queue The ArrowQueue to be cleared.
 */
void queue_clear(ArrowQueue_t* queue);

/**
 * @brief Appends an arrow to the end of a queue.
 * 
 * @param queue ArrowQueue to be appened to.
 * @param arrow Arrow pointer to be added to the queue.
 */
void queue_append(ArrowQueue_t* queue, Arrow_t* arrow);

/**
 * @brief Moves an arrow to the left and updates diplay.
 * 
 * @param arrow Arrow to be shifted to the left by one position.
 */
void move_arrow_left(Arrow_t* arrow);

/**
 * @brief Moves an arrow to the right and updates diplay.
 * 
 * @param arrow Arrow to be shifted to the right by one position.
 */
void move_arrow_right(Arrow_t* arrow);

/**
 * @brief Rotates an arrow clockwise and updates diplay
 * 
 * @param arrow Arrow to be rotated.
 */
void rotate_clockwise(Arrow_t* arrow);

/**
 * @brief Rotates an arrow anticlockwise and updates diplay.
 * 
 * @param arrow Arrow to be rotated.
 */
void rotate_anticlockwise(Arrow_t* arrow);

/**
 * @brief Updates the arrows position diplayed on the screen.
 * 
 * @param arrow Arrow to be updated on the screen.
 * @param state bool for being on or off.
 */
void update_arrow(Arrow_t* arrow, uint8_t state);

/**
 * @brief Equates if two arrows are equal.
 * 
 * @param arrow1 First arrow.
 * @param arrow2 Second arrow.
 * @return true Arrows have the same cooridinates and rotation.
 * @return false Arrows are ether of different rotation, different cooridinates or both.
 */
bool is_arrow_equal(Arrow_t* arrow1, Arrow_t* arrow2);

/**
 * @brief Returns True if the player missed the arrow.
 * 
 * @param player The players arrow
 * @param arrow The arrow that might've been missed.
 * @return true The player has missed this arrow.
 * @return false The arrow has yet to pass the player.
 */
bool arrow_missed(Arrow_t* player, Arrow_t* arrow);

/**
 * @brief Returns a new arrow initilised to the provided values and allocated the correct memory.
 * 
 * @param x x-position.
 * @param y y-position.
 * @param rotation Rotation_t for the arrow rotation.
 * @return Arrow_t* pointer to the newly created arrow.
 */
Arrow_t* new_arrow(uint8_t x, uint8_t y, Rotation_t rotation);

/**
 * @brief Deletes an arrow from the display and frees the memory the arrow was allocated.
 * 
 * @param arrow Arrow to be deleted.
 */
void delete_arrow(Arrow_t* arrow);

#endif