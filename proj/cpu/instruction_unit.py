from myhdl import *

def InstructionUnit(din, opcode, op1, op2):
    """Decodes incoming instruction"""

    @always_comb
    def decode_instruction():
        opcode.next = din[16:12]
        op1.next = din[12:6]
        op2.next = din[6:0]

    return decode_instruction

