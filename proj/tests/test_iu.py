from cpu.instruction_unit import *
from cpu.constants import *
from myhdl import *

def test_iu():
	data_in = Signal(intbv(0)[WIDTH:])
	opcode = Signal(intbv(0)[WIDTH:])
	op1 = Signal(intbv(0)[WIDTH:])
	op2 = Signal(intbv(0)[WIDTH:])
	clk = Signal(bool(0))

	dut = instruction_unit(data_in, opcode, op1, op2, clk)

	@instance
	def stimulus():
		# Slice one word into operands and opcode
		data_in.next = 0b00010000010001111
		yield clk.posedge
		yield clk.negedge
		assert opcode == 0b0001
		assert op1 == 0b000001
		assert op2 == 0b0001111

		# Slice another word
		data_in.next = 0b0011000001000010
		yield clk.posedge
		yield clk.negedge
		assert opcode == 0b0011
		assert opcode != 0b0001
		assert op1 == 0b000001
		assert op2 == 0b000010

		raise StopSimulation

	return dut, stimulus

sim = Simulation(test_iu())
sim.run()
