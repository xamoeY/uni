from myhdl import *

def Rom(dout, addr, CONTENT):
    """Read Only Memory

    CONTENT needs to be static
    """

    @always_comb
    def read():
        dout.next = CONTENT[int(addr)]

    return read
