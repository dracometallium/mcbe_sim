#ifndef __mcbe_h
#define __mcbe_h

#include<stdint.h>
#include<stdbool.h>

enum opMask {
    LD  = 0x40,
    ST  = 0x60,
    ADD = 0x80,
    SUB = 0xA0,
    JMP = 0xC0,
    JZ  = 0xE0,
    HLT = 0x20,
    NOP = 0x00,
    /*useful masks*/
    OP  = 0xE0,
    ARG = 0x1F,
};

enum FLAGS {
    F_HALT = 0x01,
    F_IN = 0x02,    /* Needs Data */
    F_OUT = 0x04,   /* Has Data */
    F_MEM = 0x08,   /* Memory was modified */
};

/*
 * Sets the registers, memory and status to zero.
 */
void init();

/*
 * Do one step.
 * Might do nothing if the machine is off, is waiting for input, or it needs
 * to print. 'nothing' is not an NOP! Not even the PC will be changed.
 */
void step();

/*
 * Push some data to the machine and clears the 'wating for input' status.
 */
void in(uint8_t num);

/*
 * Returns what ever the machine wants to print and clears the 'waiting for
 * output' status. 
 */
int8_t out();

void set_mem(int8_t val, uint8_t pos);

int8_t get_mem(uint8_t pos);

void set_flag(enum FLAGS f);

void unset_flag(enum FLAGS f);

bool get_flag(enum FLAGS f);

uint8_t bitExt(uint8_t num);

uint8_t get_PC();

uint8_t get_IR();

int8_t get_AC();

uint8_t get_mval();

int8_t get_mdir();

#endif
