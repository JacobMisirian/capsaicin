#ifndef _INST_H_
#define _INST_H_

#include <stdint.h>

struct inst {
  uint8_t  op_code;
  uint8_t  op1;
  uint8_t  op2;
  uint16_t imm;
};

typedef enum {
  add,
  and,
  call,
  div_,
  hcf,
  jil,
  jmp,
  jne,
  lb,
  ld,
  li,
  lw,
  mod,
  mul,
  not,
  or,
  pop,
  push,
  ret,
  sb,
  shil,
  shir,
  sw,
  syscall,
  sub,
  xor
} op_code_t;

struct inst unpack_inst (uint32_t data);

#endif
