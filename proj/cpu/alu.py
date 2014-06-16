from myhdl import *
from cpu.constants import *

alu_func = enum("add",
                "sub",
                "mul",
                "inc",
                "dec",
                "not_a",
                "a_and_b",
                "a_or_b",
                "shift_l",
                "shift_r",
                "cmp",
                "je")

def alu(a, b, operation, result, clk):
    """This module represents an ALU.
    a, b - input 8 u_sign int
    result - output 32bits
    clk - moment, when alu works"""
    @always(clk.posedge)
    def logic():
        if operation == alu_func.add:
            result.next = a + b
        elif operation == alu_func.sub:
            result.next = a - b
        elif operation == alu_func.mul:
            result.next = a * b
        elif operation == alu_func.inc:
            result.next = a + 1
        elif operation == alu_func.dec:
            result.next = a - 1
        elif operation ==  alu_func.not_a:
            result.next = ~a
        elif operation == alu_func.a_and_b:
            result.next = a & b
        elif operation == alu_func.a_or_b:
            result.next = a | b
        elif operation == alu_func.shift_l:
            result.next = a << b
        elif operation == alu_func.shift_r:
            result.next = a >> b
        elif operation == alu_func.cmp:
            if a < b:
                result.next = -1
            elif a == b:
                result.next = 0
            elif a > b:
                result.next = 1 
        elif operation == alu_func.je:
            if a == b:
                #jump where?
                result.next = a
            else:
                result.next = min(a, b)

       
    return logic