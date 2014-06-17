from myhdl import *
from cpu.constants import *
from common.isa import *

def control_unit(opcode, op1, op2, rsult, clk):
	"""Control unit, manages control operations.
	If alu operations accure, redirects them to alu"""
	
	@always(clk.posedge)
	def logic():
		if opcode == OPCODES["stop"]:
			result.next = None
		elif opcode == OPCODES["store"]:
			pass
		elif opcode == OPCODES["load"]:
			pass
		elif opcode == OPCODES["mov"]:
			pass
		elif opcode == OPCODES["movi"]:
			pass
		elif opcode == OPCODES["je"]:
			pass

	return logic
