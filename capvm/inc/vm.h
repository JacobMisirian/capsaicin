#ifndef _VM_H_
#define _VM_H_

#include <inst.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG_FLGS 0xC
#define REG_BP 0xD
#define REG_IP 0xE
#define REG_STACK 0XF

#define FLG_ZERO 0
#define FLG_SIGN 1

struct vm {
  uint8_t  * ram;
  uint16_t   registers [16];
};

struct vm * vm_init (char * prog, size_t prog_size, size_t ram_size);
void        vm_free (struct vm * vm);

void vm_run (struct vm * vm);

#endif
