from myhdl import *
from cpu.constants import *
from common.isa import *

def alu(opcode, a, b, result, clk):
    """This module represents an ALU.
    opcode - 4 bit opcode
    a, b - input 8 u_sign int
    result - output 16bits
    clk - moment, when alu works"""
    @always(clk.posedge)
    def logic():
        if opcode == OPCODES["add"]:
            result.next = a + b
        elif opcode == OPCODES["sub"]:
            result.next = a - b
        elif opcode == OPCODES["mul"]:
            result.next = a * b
        elif opcode == OPCODES["div"]:
            result.next = a / b
        elif opcode ==  OPCODES["not"]:
            result.next = ~a
        elif opcode == OPCODES["and"]:
            result.next = a & b
        elif opcode == OPCODES["or"]:
            result.next = a | b
        elif opcode == OPCODES["shift_l"]:
            result.next = a << b
        elif opcode == OPCODES["shift_r"]:
            result.next = a >> b
        elif opcode == OPCODES["cmp"]:
            if a < b:
                result.next = -1
            elif a == b:
                result.next = 0
            elif a > b:
                result.next = 1 
    return logic