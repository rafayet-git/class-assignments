#ifndef TUI_INSTRUCTION_H
#define TUI_INSTRUCTION_H

#include "Canvas.h"

struct _InstructionNode
{
    size_t x_offset;
    size_t y_offset;
    Canvas *canvas;
    char do_free_mem;

    struct _InstructionNode *next;
    struct _InstructionNode *prev;
};

/**
 * A node object containing instruction information.
 * 
 * @note x_offset and y_offset uses the coordinate system of the terminal. meaning (1, 1) is the top-left-most corner of the terminal
 * @note users should not instantiate this type. leave it for the provided functions
 * 
 * @data x_offset - the starting x position to print the canvas
 * @data y_offset - the starting y position to print the canvas
 * @data canvas - a pointer to the canvas to print at (x_offset, y_offset)
 * @data do_free_mem - a flag to determine if the canvas should be free when the InstructionNode is freed to avoid memory leaks
 * 
 * @data next - the next instruction node. NULL if there is no next node
 * @data prev - the prev instruction node. NULL if there is no previous node
*/
typedef struct _InstructionNode InstructionNode;

/**
 * A struct representing a queue using a doubly-linked list.
 * 
 * @note users should not instantiate this type. use make_instruction_queue function.
 * @note do NOT call free on the queue pointer. this will lead to a memory leak. use free_queue function.
 * 
 * @data head - the head of the queue where data exits the queue
 * @data tail - the tail of the queue where data enters the queue
 * 
 * @invariant - queue is empty when head == NULL and tail == NULL
 * @invariant - queue contains one item when head == tail
 * @invariant - queue contains more than one item when head != tail
*/
typedef struct
{
    InstructionNode *head;
    InstructionNode *tail;
} InstructionQueue;

/**
 * creates an InstructionQueue on the heap
 * 
 * @return a pointer to the InstructionQueue on the heap
*/
InstructionQueue *make_instruction_queue();

/**
 * checks if the instruction queue is empty
 * 
 * @arg queue - a pointer to the instruction queue being checked
 * @returns a boolean on if the queue is empty
*/
char is_queue_empty(InstructionQueue *queue);

/**
 * creates an instruction and pushes it onto the instruction queue.
 * 
 * @arg queue - a pointer to the instruction queue
 * @arg canvas - the canvas being drawn
 * @arg x_offset - the x position to draw the canvas 
 * @arg y_offset - the y position to draw the canvas
 * @arg do_free_mem - a flag to check if the memory should be freed when the instruction node is freed.
 * @return a boolean on if the instruction was successfully made and pushed onto the queue
*/
char push_instruction(InstructionQueue *queue, Canvas *canvas, size_t x_offset, size_t y_offset, char do_free_mem);

/**
 * executes an instruction on the queue.
 * 
 * @arg queue - a pointer to the instruction queue
*/
void execute_instruction(InstructionQueue *queue);

/**
 * executes all instructions on the queue. the queue will be empty after this function is called.
 * 
 * @arg queue - a pointer to the instruction queue
*/
void execute_all_instructions(InstructionQueue *queue);

/**
 * a debug print statement to check the queue
 * 
 * @arg queue - a pointer to the instruction queue to print
*/
void debug_print_queue(InstructionQueue *queue);

/**
 * a function that frees a instruction node. 
 * 
 * @note the user should not call this function. call the free_queue function instead to free the queue.
 * 
 * @arg instruction - the instruction node to free.
*/
void free_instruction(InstructionNode *instruction);

/**
 * a safe function that frees the instruction queue.
 * 
 * @arg queue - a pointer to the instruction queue to free.
*/
void free_queue(InstructionQueue *queue);

#endif