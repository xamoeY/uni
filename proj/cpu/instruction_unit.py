from myhdl import *

def instruction_unit(data_in, opcode, op1, op2, clk):
	"""todo schatz gogo"""
	
	@always(clk.posedge)
	def logic():
		opcode.next = data_in[0:4]
		op1.next = data_in[4:10]
		op2.next = data_in[10:16]

	return logic

