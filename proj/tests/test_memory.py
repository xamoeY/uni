from myhdl import *
from cpu.memory import *
from cpu.constants import *

def test_memory():
    we = Signal(bool(0))
    sig_in = Signal(intbv(0)[WIDTH:])
    sig_out = Signal(intbv(0)[WIDTH:])
    address = Signal(intbv(0)[WIDTH:])
    clk = Signal(bool(0))

    dut = memory(we, address, sig_in, sig_out, clk)

    @always(delay(10))
    def clkgen():
        clk.next = not clk

    @instance
    def stimulus():
        # Memory at address = 1 gets value 5
        we.next = True
        address.next = Signal(intbv(1)[WIDTH:])
        sig_in.next = Signal(intbv(5)[WIDTH:])
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 5

        # Write value 31 in memory with address=0
        we.next = True
        address.next = Signal(intbv(0)[WIDTH:])
        sig_in.next = Signal(intbv(31)[WIDTH:])
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 31

        # The address=1 is 'blocked', so we can only read the old value
        we.next = False
        address.next = Signal(intbv(1)[WIDTH:])
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 5

        # Now we 'block' adress=0 and read the old value
        we.next = False
        address.next = Signal(intbv(0)[WIDTH:])
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 31

        raise StopSimulation

    return dut, stimulus, clkgen


sim = Simulation(test_memory())
sim.run()
