from myhdl import *
from random import randrange
from cpu.alu import *
from cpu.constants import *

def test_alu():
    a = Signal(intbv(0)[8:])
    b = Signal(intbv(0)[8:])
    result = Signal(intbv(0)[8:])
    opcode = Signal(alu_func.sub)
    clk = Signal(bool(0))
    period = 10

    dut = alu(opcode, a, b, result, clk)
    @always(delay(period))
    def clkgen():
        clk.next = not clk

    @always(clk.negedge)
    def monitor():
        if DEBUG:
            print "a=%s %s b=%s -> result %s" % (a, opcode, b, result)
    
    @instance
    def stimulus():
        # test_add
        a.next = 5
        b.next = 2
        opcode.next = alu_func.add
        yield clk.posedge
        yield clk.negedge
        assert result == 7
            
        # test_sub
        a.next = 5
        b.next = 2
        opcode.next = alu_func.sub
        yield clk.posedge
        yield clk.negedge
        assert result == 3
            
        # test_mul
        a.next = 5
        b.next = 5
        opcode.next = alu_func.mul
        yield clk.posedge
        yield clk.negedge
        assert result == 25

        # test_inc
        a.next = 5
        opcode.next = alu_func.inc
        yield clk.posedge
        yield clk.negedge
        assert result == 6

        # test_dec
        a.next = 5
        opcode.next = alu_func.dec
        yield clk.posedge
        yield clk.negedge
        assert result == 4

        # test_not_a
        a.next = 5
        opcode.next = alu_func.not_a
        yield clk.posedge
        yield clk.negedge
        print result
        assert result.signed() == -6

        # test_b_and_a
        a.next = 5
        b.next = 5
        opcode.next = alu_func.a_and_b
        yield clk.posedge
        yield clk.negedge
        assert result == 5

        # test_a_or_b
        a.next = 5
        b.next = 5
        opcode.next = alu_func.a_or_b
        yield clk.posedge
        yield clk.negedge
        assert result == 5

        # Test shift left
        a.next = 6
        b.next = 1
        opcode.next = alu_func.shift_l
        yield clk.posedge
        yield clk.negedge
        assert result == 12

        # Test shift right
        a.next = 6
        b.next = 1
        opcode.next = alu_func.shift_r
        yield clk.posedge
        yield clk.negedge
        assert result == 3

        # Test comparison a is bigger than b. 1 is expected
        a.next = 8
        b.next = 1
        opcode.next = alu_func.cmp
        yield clk.posedge
        yield clk.negedge
        assert result == 1
        assert result != 0

        # Test cmp if a equal to b
        a.next = 12
        b.next = 12
        opcode.next = alu_func.cmp
        yield clk.posedge
        yield clk.negedge
        assert result == 0
        assert result != -1

        # Test je, if a == b
        a.next = 3
        b.next = 3
        opcode.next = alu_func.je
        yield clk.posedge
        yield clk.negedge
        assert result == a # and check whether jumped

        # Test je, if a != b
        a.next = 6
        b.next = 9
        opcode.next = alu_func.je
        yield clk.posedge
        yield clk.negedge
        assert result == a

        raise StopSimulation

    return clkgen, monitor, stimulus, dut

sim = Simulation(test_alu())
sim.run()