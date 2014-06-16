from myhdl import *
from cpu.register_bank import *
from cpu.constants import *
from common.isa import *

def test_register_bank():
    sig_in = Signal(intbv(1)[8:])
    sig_out = Signal(intbv(3)[8:])
    register = Signal(REGISTERS["zero"])
    clk = Signal(bool(0))
    ovf = Signal(0)

    dut = register_bank(register, sig_in, sig_out, ovf, clk)

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
        # Cheking special registers. Zero register is always 0
        ovf.next = 0
        register.next = REGISTERS["zero"]
        sig_in = 3
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 0

        ovf.next = 0
        register.next = REGISTERS["pc"]
        sig_in = 6
        yield clk.posedge 
        yield clk.negedge
        # Here don't know to do. It should store adress from next operation
        assert sig_out == 6

        # Here result of comparison (cmp) is stored
        # For example result is equal
        ovf.next = 0
        register.next = REGISTERS["cmp_result"]
        sig_in = 8
        yield clk.posedge
        yield clk.negedge
        # TODO comparison in alu
        assert sig_out == 8

        # TODO Register for jump
        ovf.next = 0
        register.next = REGISTERS["jmp_next"]
        sig_in = 4
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 4

        # What is temp?
        ovf.next = 0
        register.next = REGISTERS["temp"]
        sig_in = 9
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 9

        # Normal registers a, b, c, d. Not overflowed
        ovf.next = 0
        register.next = REGISTERS["a"]
        sig_in = 16
        yield clk.posedge
        yield clk.negedge
        assert sig_out == 16

        # Now overflowed. The value of the registers can't be overwritten
        ovf.next = 1
        register.next = REGISTERS["a"]
        sig_in = -5
        yield clk.posedge
        yield clk.negedge
        assert sig_out != -5
        assert sig_out == 16

        # Overflowed, the value can't be overwritten
        """ovf.next = 1
        sig_in.next = 5
        yield clk.posedge
        yield clk.negedge
        assert sig_in != sig_out"""

        raise StopSimulation

    return clkgen, monitor, stimulus, dut, 

sim = Simulation(test_register_bank())
sim.run