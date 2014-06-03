from myhdl import *

def register(sig_in, sig_out, ce, clk):
	"""sig_in, sig_out - are input and output data
	accordingly
	ce - is a status bit, that shows whether register
	is overflowed
	0 - not overflowed
	1 - owerflowed
	"""

	@always(clk.posedge)
	def logic():
		if ce == 0:
			sig_out.next = sig_in
	return logic
