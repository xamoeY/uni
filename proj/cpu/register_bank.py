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
				register_bank[0].next = 0
			elif register == REGISTERS["pc"]:
				register_bank[1].next = sig_in
			elif register == REGISTERS["cmp_result"]:
				register_bank[2].next = sig_in
			elif register == REGISTERS["jmp_next"]:
				register_bank[3].next = sig_in
			elif register == REGISTERS["temp"]:
				register_bank[4].next = sig_in
			elif register == REGISTERS["a"]:
				register_bank[5].next = sig_in 
			elif register == REGISTERS["b"]:
				register_bank[6].next = sig_in
			elif register == REGISTERS["c"]:
				register_bank[7].next = sig_in
			elif register == REGISTERS["d"]:
				register_bank[8].next = sig_in

	@always_comb
	def output():
		sig_out.next = sig_in
	

	return logic, output
