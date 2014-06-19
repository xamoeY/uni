from myhdl import *
from common.isa import *

def Ram(dout, din, addr, we, clk):
    """Random Access Memory"""

    mem = [Signal(intbv(0)[WIDTH:]) for i in range(DEPTH)]

    @always(clk.posedge)
    def write():
        if we:
            mem[addr].next = din

    @always_comb
    def read():
        dout.next = mem[addr]

    return write, read
