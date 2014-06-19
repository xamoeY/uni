from myhdl import *
from cpu.constants import *
from common.isa import *

def register_bank(register, sig_in, sig_out, we, clk):
	"""sig_in, sig_out - are input and output data
	accordingly
	we 
	"""
	register_bank = [Signal(intbv(0)[WIDTH:]) for i in range(9)]
	@always(clk.posedge)
	def write():
		if we:
			if register == REGISTERS["zero"]:
				register_bank[0b000000].next = 0
			else:
				register_bank[REGISTERS[register]].next = sig_in
			
			# elif register == REGISTERS["pc"]:
			# 	register_bank[0b000001].next = sig_in
			# elif register == REGISTERS["cmp_result"]:
			# 	register_bank[0b000010].next = sig_in
			# elif register == REGISTERS["jmp_next"]:
			# 	register_bank[0b000011].next = sig_in
			# elif register == REGISTERS["temp"]:
			# 	register_bank[0b000100].next = sig_in
			# elif register == REGISTERS["a"]:
			# 	register_bank[0b000101].next = sig_in 
			# elif register == REGISTERS["b"]:
			# 	register_bank[0b000110].next = sig_in
			# elif register == REGISTERS["c"]:
			# 	register_bank[0b000111].next = sig_in
			# elif register == REGISTERS["d"]:
			# 	register_bank[0b001000].next = sig_in

	@always_comb
	def read():
		sig_out.next = sig_in

	return read, write