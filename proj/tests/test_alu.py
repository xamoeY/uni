from myhdl import *
from random import randrange
from cpu.alu import *
from cpu.constants import *

def test_alu():
    a = Signal(intbv(0)[8:])
    b = Signal(intbv(0)[8:])
    result = Signal(intbv(0)[8:])
    operation = Signal(alu_func.sub)
    clk = Signal(bool(0))
    period = 10

    dut = alu(a, b, operation, result, clk)
    @always(delay(period))
    def clkgen():
        clk.next = not clk

    @always(clk.negedge)
    def monitor():
        if DEBUG:
            print "a=%s %s b=%s -> result %s" % (a, operation, b, result)
    
    @instance
    def stimulus():
        # test_add
        a.next = 5
        b.next = 2
        operation.next = alu_func.add
        yield clk.posedge
        yield clk.negedge
        assert result == 7
            
        # test_sub
        a.next = 5
        b.next = 2
        operation.next = alu_func.sub
        yield clk.posedge
        yield clk.negedge
        assert result == 3
            
        # test_mul
        a.next = 5
        b.next = 5
        operation.next = alu_func.mul
        yield clk.posedge
        yield clk.negedge
        assert result == 25

        # test_inc
        a.next = 5
        operation.next = alu_func.inc
        yield clk.posedge
        yield clk.negedge
        assert result == 6

        # test_dec
        a.next = 5
        operation.next = alu_func.dec
        yield clk.posedge
        yield clk.negedge
        assert result == 4

        # test_not_a
        a.next = 5
        operation.next = alu_func.not_a
        yield clk.posedge
        yield clk.negedge
        print result
        assert result.signed() == -6

        # test_b_and_a
        a.next = 5
        b.next = 5
        operation.next = alu_func.a_and_b
        yield clk.posedge
        yield clk.negedge
        assert result == 5

        # test_a_or_b
        a.next = 5
        b.next = 5
        operation.next = alu_func.a_or_b
        yield clk.posedge
        yield clk.negedge
        assert result == 5

        raise StopSimulation

    return clkgen, monitor, stimulus, dut

sim = Simulation(test_alu())
sim.run()