from myhdl import *
from cpu.constants import *

def register(sig_in, sig_out, ovf, clk):
	"""sig_in, sig_out - are input and output data
	accordingly
	ovf - is a status bit, that shows whether register
	is overflowed
	0 - not overflowed
	1 - owerflowed
	"""

	@always(clk.posedge)
	def logic():
		if ovf == 0:
			sig_out.next = sig_in
	return logic
