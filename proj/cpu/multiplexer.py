from myhdl import *
from cpu.constants import *

def multiplexer(a, b, sel, out, clk):

	@always(clk.posedge)
	def logic():
		if sel==0:
			out.next = a
		else:
			out.next = b

	return logic
