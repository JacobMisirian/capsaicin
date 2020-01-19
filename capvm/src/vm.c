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

static void set_flags (struct vm * vm, uint16_t val);

void vm_run (struct vm * vm) {
  struct inst inst;

  vm->registers [REG_IP] = 0;

  while (1) {
    inst = unpack_inst (((uint32_t *) vm->ram) [vm->registers [REG_BP]]);

    switch (inst.op_code) {
      case add:
        set_flags (vm, vm->registers [inst.op1] += vm->registers [inst.op2]);
        break;
      case and:
        set_flags (vm, vm->registers [inst.op1] &= vm->registers [inst.op2]);
        break;
      case call:
        break;
      case div_:
        set_flags (vm, vm->registers [inst.op1] /= vm->registers [inst.op2]);
        break;
      case hcf:
        return;
      case jil:
        if ((vm->registers [REG_FLGS] >> FLG_SIGN) & 1) {
          vm->registers [REG_IP] = inst.imm;
        }
        break;
      case jmp:
        vm->registers [REG_IP] = inst.imm;
        continue;
      case jne:
        if (!((vm->registers [REG_FLGS] >> FLG_ZERO) & 1)) {
          vm->registers [REG_IP] = inst.imm;
        }
        break;
      case lb:
        vm->registers [inst.op1] = vm->ram [vm->registers [inst.op2]];
        break;
      case ld:
        vm->registers [inst.op1] = vm->registers [inst.op2];
        break;
      case li:
        vm->registers [inst.op1] = inst.imm;
        break;
      case lw:
        vm->registers [inst.op1] = *(uint16_t *) (vm->ram + vm->registers [inst.op2]);
        break;
      case mod:
        set_flags (vm, vm->registers [inst.op1] ^= vm->registers [inst.op2]);
        break;
      case mul:
        set_flags (vm, vm->registers [inst.op1] *= vm->registers [inst.op2]);
        break;
      case not:
        set_flags (vm, vm->registers [inst.op1] = ~vm->registers [inst.op1]);
        break;
      case or:
        set_flags (vm, vm->registers [inst.op1] |= vm->registers [inst.op2]);
        break;
      case pop:
        vm->registers [inst.op1] = *(uint16_t *) (vm->ram + vm->registers [REG_STACK]);
        vm->registers [REG_STACK] += 2;
        break;
      case push:
        *(uint16_t *) (vm->ram + vm->registers [REG_STACK]) = vm->registers [inst.op1];
        vm->registers [REG_STACK] -= 2;
        break;
      case ret:
        break;
      case sb:
        vm->ram [vm->registers [inst.op1]] = inst.op2;
        break;
      case shil:
        set_flags (vm, vm->registers [inst.op1] << vm->registers [inst.op2]);
        break;
      case shir:
        set_flags (vm, vm->registers [inst.op1] >> vm->registers [inst.op2]);
        break;
      case sw:
        *(uint16_t *) (vm->ram + vm->registers [inst.op1]) = vm->registers [inst.op2];
        break;
      case syscall:
        break;
      case sub:
        set_flags (vm, vm->registers [inst.op1] -= vm->registers [inst.op2]);
        break;
      case xor:
        set_flags (vm, vm->registers [inst.op1] ^= vm->registers [inst.op2]);
        break;
    }

    vm->registers [REG_BP] ++;
  }
}

static void set_flags (struct vm * vm, uint16_t val) {
    vm->registers [REG_FLGS] = 0;

    if (val == 0) {
       vm->registers [REG_FLGS] |= (1 << FLG_ZERO);
    }
    if ((int16_t)val < 0) {
       vm->registers [REG_FLGS] |= (1 << FLG_SIGN);
    }
}
