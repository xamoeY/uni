from myhdl import *
from common.isa import *

def RegisterBank(dout, din, reg, we, clk):
    """Register Bank"""

    registers = [Signal(intbv(0)[WIDTH:]) for i in range(9)]

    @always(clk.posedge)
    def write():
        if we:
            if reg == REGISTERS["zero"]:
                registers[0b000000].next = 0
            else:
                registers[reg].next = din

    @always_comb
    def read():
        dout.next = registers[reg]

    return read, write
