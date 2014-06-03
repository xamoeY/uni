from myhdl import *
from cpu.register import *

def test_register():
    sig_in = Signal(intbv(1)[8:])
    sig_out = Signal(intbv(3)[8:])
    clk = Signal(bool(0))
    ce = Signal(0)

    dut = register(sig_in, sig_out, ce, clk)

    @always(delay(10))
    def clkgen():
        clk.next = not clk

    @always(clk.negedge)
    def monitor():
        print "sig_in= %s  sig_out= %s" % (bin(sig_in, 16), bin(sig_out, 16))

    @instance
    def stimulus():
        ce = 0
        sig_in.next = 3
        yield clk.posedge
        yield clk.negedge
        assert sig_in == sig_out

        ce = 1
        sig_in.next = 5
        yield clk.posedge
        yield clk.negedge
        assert sig_in != sig_out
        
        raise StopSimulation

    return clkgen, monitor, stimulus, dut, 

sim = Simulation(test_register())
sim.run