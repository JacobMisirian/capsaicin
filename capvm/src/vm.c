#include <vm.h>

struct vm * init_vm (char * prog, size_t prog_size, size_t ram_size) {
  struct vm * vm;

  vm = calloc (1, sizeof (struct vm));

  vm->ram = calloc (ram_size, sizeof (uint8_t));
  memcpy (vm->ram, prog, prog_size);

  return vm;
}

void free_vm (struct vm * vm) {
  free (vm->ram);
  free (vm);
}

void vm_run (struct vm * vm) {
  struct inst inst;

  vm->registers [REG_IP] = 0;

  while (1) {
    inst = unpack_inst (((uint32_t *) vm->ram) [vm->registers [REG_BP]]);



    vm->registers [REG_BP] ++;
  }
}
