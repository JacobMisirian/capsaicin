#ifndef _VM_H_
#define _VM_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vm {
  uint8_t  * ram;
  uint16_t   registers [16];
};

struct vm * init_vm (char * prog, size_t prog_size, size_t ram_size);
void        free_vm (struct vm * vm);

void vm_run (struct vm * vm);

#endif
