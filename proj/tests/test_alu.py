from myhdl import *
from random import randrange
from cpu.alu import *

def test_alu():
    a = Signal(intbv(0)[8:])
    b = Signal(intbv(0)[8:])
    result = Signal(intbv(0)[8:])
    operation = Signal(alu_func.add)
    clk = Signal(bool(0))
    period = 10

    dut = alu(a, b, operation, result, clk)

    @always(delay(period))
    def clkgen():
        clk.next = not clk

    @always(clk.negedge)
    def monitor():
        print "a=%s %s b=%s -> result %s" % (a, operation, b, result)
            
    @instance
    def test_add():
        a.next = 1
        b.next = 2
        operation.next = alu_func.add
        yield clk.posedge
        yield clk.negedge
        assert result == 3
        raise StopSimulation

    """
    @instance
    def test_sub():
        yield operation(7, 1, alu_func["sub"])
        yield delay(period//4)
        assert result == 6

    @instance
    def test_multiply():
        yield operation(2, 2, alu_func["mul"])
        yield delay(period//4)
        assert result == 4

    @instance
    def test_increment():
        yield operation(2, 5, alu_func["inc"])
        yield delay(period//4)
        assert result == 3

    @instance
    def test_decrement():
        yield operation(9, 2, alu_func["dec"])
        yield delay(period//4)
        assert result == 8

    @instance
    def test_not_a():
        yield operation(5, 1, alu_func["not_a"])
        yield delay(period//4)
        assert result == -6

    @instance
    def test_and():
        yield operation(7, 3, alu_func["b_and_a"])
        yield delay(period//4)
        assert result == 3

    @instance
    def test_or():
        yield operation(5, 9, alu_func["b_or_a"])
        yield delay(period//4)
        assert result == 13"""

    return clkgen, monitor, test_add, dut

sim = Simulation(test_alu())
sim.run()