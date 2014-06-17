from myhdl import *
from cpu.constants import *
from common.isa import *

def register_bank(register, sig_in, sig_out, ovf, clk):
	"""sig_in, sig_out - are input and output data
	accordingly
	ovf - is a status bit, that shows whether register
	is overflowed
	0 - not overflowed
	1 - owerflowed
	"""
	register_bank = [Signal(intbv(0)[WIDTH:]) for i in range(9)]
	@always(clk.posedge)
	def logic():
		if ovf == 0:
			if register == REGISTERS["zero"]:
				register_bank[0b000000].next = 0
			elif register == REGISTERS["pc"]:
				register_bank[0b000001].next = sig_in
			elif register == REGISTERS["cmp_result"]:
				register_bank[0b000010].next = sig_in
			elif register == REGISTERS["jmp_next"]:
				register_bank[0b000011].next = sig_in
			elif register == REGISTERS["temp"]:
				register_bank[0b000100].next = sig_in
			elif register == REGISTERS["a"]:
				register_bank[0b000101].next = sig_in 
			elif register == REGISTERS["b"]:
				register_bank[0b000110].next = sig_in
			elif register == REGISTERS["c"]:
				register_bank[0b000111].next = sig_in
			elif register == REGISTERS["d"]:
				register_bank[0b001000].next = sig_in

	@always_comb
	def output():
		sig_out.next = sig_in
	

	return logic, output
