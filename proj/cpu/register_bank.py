from myhdl import *
from cpu.constants import *

def register_bank(sig_in, sig_out, ovf, clk):
	"""sig_in, sig_out - are input and output data
	accordingly
	ovf - is a status bit, that shows whether register
	is overflowed
	0 - not overflowed
	1 - owerflowed
	"""
	regiser_bank = [Signal(intbv(0)[WIDTH:]) for i in range(9)]
	@always(clk.posedge)
	def always_zero_register():
		register_bank[0].next = 0

	"""@qlways(clk.posedge)
	def """
	@always(clk.posedge)
	def logic():
		if ovf == 0:
			sig_out.next = sig_in
	return logic
