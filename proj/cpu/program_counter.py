from myhdl import *
from cpu.instruction_unit import *
from common.isa import *

def program_counter(instruction, memory_in, memory_out, clk):
	 

	 @always_comb
	 def logic():
	 	# Counter increase by 1 -> next instruction will be executed
	 	
