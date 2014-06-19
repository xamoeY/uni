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
    return logic
