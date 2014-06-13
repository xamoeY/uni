from myhdl import *
from cpu.register import *
from cpu.constants import *

def test_register_bank():
    sig_in = Signal(intbv(1)[8:])
    sig_out = Signal(intbv(3)[8:])
    clk = Signal(bool(0))
    ovf = Signal(0)

    dut = register(sig_in, sig_out, ovf, clk)

    @always(delay(10))
    def clkgen():
        clk.next = not clk

    @always(clk.negedge)
    def monitor():
        if DEBUG:
            print "sig_in= %s  sig_out= %s" % (bin(sig_in, 16), bin(sig_out, 16))

    @instance
    def stimulus():
        # Not overflowed - writing is possible
        ovf.next = 0
        sig_in.next = 3
        yield clk.posedge
        yield clk.negedge
        assert sig_in == sig_out

        # Overflowed, the value can't be overwritten
        sb.next = 1
        sig_in.next = 5
        yield clk.posedge
        yield clk.negedge
        assert sig_in != sig_out

        raise StopSimulation

    return clkgen, monitor, stimulus, dut, 

sim = Simulation(test_register())
sim.run