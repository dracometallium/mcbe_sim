#include "mcbe.h"

/*MCBE*/
int8_t AC;
uint8_t PC;
uint8_t IR;
uint8_t flags;
uint8_t mdir;
uint8_t mval;
int8_t mem[32];

uint8_t bitExt(uint8_t num)
{
    return (num & 0xF0) ? 0xF0 | num : num;
}

void init()
{
    int i;
    AC = 0;
    PC = 0;
    IR = 0;
    flags = 0;
    for (i = 0; i < 32; i++) {
        mem[i] = 0;
    }
    return;
}

void step()
{
    uint8_t op;
    uint8_t arg;
    if (flags & (F_HALT | F_IN | F_OUT)) {
        /*The computer needs data, wants to push data, or is off */
        return;
    }
    flags = flags & ~F_MEM;
    PC = PC & ARG;
    IR = mem[PC];
    op = IR & OP;
    arg = IR & ARG;
    switch (op) {
    case LD:
        if (arg == 30) {
            flags = flags | F_IN;
            return;
        }
        AC = mem[arg];
        PC++;
        break;
    case ST:
        if (arg == 31) {
            flags = flags | F_OUT;
            mem[arg] = AC;
            return;
        } else {
            flags = flags | F_MEM;
        }
        mem[arg] = AC;
        mval = AC;
        mdir = arg;
        PC++;
        break;
    case ADD:
        AC = AC + mem[arg];
        PC++;
        break;
    case SUB:
        AC = AC - mem[arg];
        PC++;
        break;
    case JMP:
        PC = PC + bitExt(arg);
        break;
    case JZ:
        if (AC == 0) {
            PC = PC + bitExt(arg);
        } else {
            PC++;
        }
        break;
    case HLT:
        flags = flags | F_HALT;
        break;
    case NOP:
        PC++;
        break;
    }
    return;
}

void in(uint8_t num)
{
    mem[30] = num;
    AC = num;
    flags = flags & ~F_IN;
    PC++;
    return;
}

int8_t out()
{
    flags = flags & ~F_OUT;
    PC++;
    return mem[31];
}

void set_mem(int8_t val, uint8_t pos)
{
    mem[pos & ARG] = val;
    return;
}

int8_t get_mem(uint8_t pos)
{
    return mem[pos & ARG];
}

void set_flag(enum FLAGS f)
{
    flags = (flags | f);
    return;
}

void unset_flag(enum FLAGS f)
{
    flags = (flags & (~f));
    return;
}

bool get_flag(enum FLAGS f)
{
    return (flags & f);
}

uint8_t get_PC()
{
    return PC & ARG;
}

uint8_t get_IR()
{
    return IR;
}

int8_t get_AC()
{
    return AC;
}

uint8_t get_mval()
{
    return mval;
}

int8_t get_mdir()
{
    return mdir;
}
