#include <inst.h>

struct inst unpack_inst (uint32_t data) {
  struct inst inst;

  inst.op_code = (uint8_t)  (data >> 27);
  inst.op1     = (uint8_t) ((data >> 16) & 63);
  inst.op2     = (uint8_t) ((data >> 22) & 31);
  inst.imm     = (uint16_t) (data &  0xFF);

  return inst;
}
