from myhdl import *
from cpu.constants import *

def memory(ro, address, sig_in, sig_out, clk):

	memory = [Signal(intbv(0)[WIDTH:]) for i in range(DEPTH)]

	@always(clk.posedge)
	def write():
		if not ro:
			memory[address].next = sig_in
			
	@always_comb
	def read():
		sig_out.next = memory[address]
		
	return instances()