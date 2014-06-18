#!usr/bin/env python2

import argparse
import os
import struct
from common.isa import *

def get_opcode_bitstring(opcode):
	c = OPCODES[opcode]
	return "{0:04b}".format(int(c, 2))

def get_register_bitstring(register):
	r = REGISTERS[register]
	return "{0:06b}".format(int(r, 2))

def parse_line(line):
	instruction = line.split()

	# opcode is always the leftmost string
	opcode = instruction[0]

	mcode = "None"

	if opcode == "stop":
		mcode = get_opcode_bitstring("stop")
		mcode = mcode.ljust(INSTRUCTION_SIZE, "0")
	elif opcode == "store":
		mcode = get_opcode_bitstring("store")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "load":
		mcode = get_opcode_bitstring("load")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "mov":
		mcode = get_opcode_bitstring("mov")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "movi":
		mcode = get_opcode_bitstring("movi")
		mcode += get_register_bitstring(instruction[1])
		mcode += "{0:06b}".format(int(instruction[2]))
	elif opcode == "add":
		mcode = get_opcode_bitstring("add")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "sub":
		mcode = get_opcode_bitstring("sub")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "mul":
		mcode = get_opcode_bitstring("mul")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "div":
		mcode = get_opcode_bitstring("div"]
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "addi":
		pass
	elif opcode == "subi":
		pass
	elif opcode == "muli":
		pass
	elif opcode == "divi":
		pass
	elif opcode == "inc":
		pass
	elif opcode == "dec":
		pass
	elif opcode == "not":
		mcode = get_opcode_bitstring("not")
		mcode += get_register_bitstring(instruction[1])
		mcode = mcode.ljust(INSTRUCTION_SIZE, "0")
	elif opcode == "and":
		mcode = get_opcode_bitstring("and")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "or":
		mcode = get_opcode_bitstring("or")	
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "shift_l":
		mcode = get_opcode_bitstring("shift_l")
		mcode += get_register_bitstring(instruction[1])
		mcode += "{0:06b}".format(int(instruction[2]))
	elif opcode == "shift_r":
		mcode = get_opcode_bitstring("shift_r")
		mcode += get_register_bitstring(instruction[1])
		mcode += "{0:06b}".format(int(instruction[2]))
	elif opcode == "cmp":
		mcode = get_opcode_bitstring("cmp")
		mcode += get_register_bitstring(instruction[1])
		mcode += get_register_bitstring(instruction[2])
	elif opcode == "j":
		pass
	elif opcode == "je":
		mcode = get_opcode_bitstring("je")
		mcode += get_register_bitstring(instruction[1])
		mcode += "{0:06b}".format(int(instruction[2]))
	elif opcode == "jne":
		pass
	elif opcode == "jg":
		pass
	elif opcode == "jge":
		pass
	elif opcode == "jl":
		pass
	elif opcode == "jle":
		pass

	# TODO return list of codes instead as some opcodes
	# actually generate multiple instructions instead of 
	# just one as we handle now
	return mcode

def parse_file(source_file):
	instructions = []

	for number, value in enumerate(source_file):
		try:
			instructions.append(parse_line(value))
		except:
			raise Exception("Parsing error at line {}".format(number))

	return instructions

def main():
	parser = argparse.ArgumentParser(description="assembler")
	parser.add_argument('file')
	args = parser.parse_args()
	
	source_file_ext = os.path.splitext(args.file)[1]
	if source_file_ext != ".asm":
		raise Exception("Expected an asm file!")

	source_file = open(args.file, 'r')
	source_file_root = os.path.splitext(args.file)[0]

	binary_file = open(source_file_root + ".o", 'wb')
	instructions = parse_file(source_file)

	print instructions

	for instruction in instructions:
		short = struct.pack('<H', int(instruction, 2))
		binary_file.write(short)

if __name__ == '__main__':
	main()