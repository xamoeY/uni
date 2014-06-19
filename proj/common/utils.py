from common.isa import *

def get_opcode_bitstring(opcode):
    c = OPCODES[opcode]
    return "{0:04b}".format(c)

def get_register_bitstring(register):
    r = REGISTERS[register]
    return "{0:06b}".format(r)
