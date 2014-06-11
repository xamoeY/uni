from myhdl import *
from cpu.multiplexer import *
from cpu.constants import *

def test_mux():
	a = Signal(intbv(1)[8:])
	b = Signal(intbv(3)[8:])
	sel = Signal(intbv(0)[8:])
	out = Signal(intbv(0)[8:])
	clk = Signal(bool(0))

	dut = multiplexer(a, b, sel, out, clk)

	@always(clk.negedge)
	def monitor():
		if DEBUG:
			print "a = %s  b = %s  sel = %s  out = %s" % (a, b, bin(sel, 4), out)

	@instance
	def stimulus():
		a = 3
		b = 7
		sel = 0
		yield clk.posedge
		yield clk.negedge
		assert out == a

		a = 8
		b = 1
		sel = 1
		yield clk.posedge
		yield clk.negedge
		assert out == b

		raise StopSimulation

	return dut, monitor, stimulus

sim = Simulation(test_mux())
sim.run()