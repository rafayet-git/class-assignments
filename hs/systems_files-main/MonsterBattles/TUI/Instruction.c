#include "Instruction.h"

#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>

InstructionQueue *make_instruction_queue()
{
    return (InstructionQueue*) calloc(1, sizeof(InstructionQueue));
}

char is_queue_empty(InstructionQueue *queue)
{
    return queue->head == NULL && queue->tail == NULL;
}

char push_instruction(InstructionQueue *queue, Canvas *canvas, size_t x_offset, size_t y_offset, char do_free_mem)
{
    InstructionNode *instruction = (InstructionNode*) malloc(sizeof(InstructionNode));
    instruction->canvas = canvas;
    instruction->x_offset = x_offset;
    instruction->y_offset = y_offset;
    instruction->do_free_mem = do_free_mem;

    instruction->next = NULL;
    if (!is_queue_empty(queue))
    {
        queue->tail->next = instruction;
        instruction->prev = queue->tail;
        queue->tail = instruction;
    }
    else
    {
        queue->tail = instruction;
        queue->head = instruction;
        instruction->prev = NULL;
    }
}

void execute_instruction(InstructionQueue *queue)
{
    InstructionNode *instruction;
    if (is_queue_empty(queue)) return;
    else if (queue->tail == queue->head) // size of 1
    {
        instruction = queue->head;
        queue->tail = NULL;
        queue->head = NULL;
    }
    else
    {
        instruction = queue->head;
        instruction->next->prev = NULL;
        queue->head = instruction->next;
        instruction->next = NULL;
    }

    // debug_print_canvas(instruction->canvas, 1);

    for (size_t i = 0; i < instruction->canvas->height; ++i)
    {
        PRINTF("\033[%ld;%ldf", instruction->y_offset + i, instruction->x_offset);
        if (instruction->canvas->choice == use_style_char) 
        { 
            print_style_line(get_canvas_row(instruction->canvas, i), instruction->canvas->width, 0);
        }
        else if (instruction->canvas->choice == use_raw_char) 
        {
            PRINTF("%ls", ((wchar_t*) instruction->canvas->characters) + instruction->canvas->width * i);
        }
    }
    fflush(stdout);
    
    //free_instruction(instruction);
}

void execute_all_instructions(InstructionQueue *queue)
{
    while (!is_queue_empty(queue))
    {
        execute_instruction(queue);
    }
}

void debug_print_queue(InstructionQueue *queue)
{
    InstructionNode *iter = queue->head;
    while (iter)
    {
        debug_print_canvas(iter->canvas, 0);
        iter = iter->next;
    }
}

void free_instruction(InstructionNode *instruction)
{
    if (instruction == NULL) return;
    if (instruction->next) free_instruction(instruction->next);
    // no memory leaks :) unless user messes up
    if (instruction->do_free_mem) {
        free_canvas(instruction->canvas);
    }
    free(instruction);
}

void free_queue(InstructionQueue *queue)
{
    free_instruction(queue->head);
    free(queue);
}