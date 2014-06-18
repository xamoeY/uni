from cpu.instruction_unit import *
from cpu.constants import *
from cpu.memory import *
from myhdl import *
import struct

def test_load_program():

    we = Signal(bool(0))
    sig_in = Signal(intbv(0)[WIDTH:])
    sig_out = Signal(intbv(0)[WIDTH:])
    address = Signal(intbv(0)[WIDTH:])
    clk = Signal(bool(0))
    mem = memory(we, address, sig_in, sig_out, clk)
    

    instructions = []
    file_in = open("programs/program2.o", "rb")
    data_in = None
    
    try:
        short = file_in.read(2)
        while short:
            instructions.append(struct.unpack('<H', short))
            short = file_in.read(2)
    finally:
        file_in.close()

    """for lol in instructions:
        print "{0:016b}".format(int(lol[0]))"""
    @always(delay(10))
    def clkgen():
        clk.next = not clk

    
    @instance
    def stimulus():
        # read program into memory
        for index, item in enumerate(instructions):
            we.next = True
            address.next = index
            sig_in.next = item[0]
            
            yield clk.posedge
            yield clk.negedge

        # assert that program has landed in memory properly
        for index, item in enumerate(instructions):
            we.next = False
            address.next = index

            yield clk.posedge
            yield clk.negedge        

            assert item[0] == sig_out

        # run program
        
 
        raise StopSimulation

    return mem, clkgen, stimulus

sim = Simulation(test_load_program())
sim.run()