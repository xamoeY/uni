#!usr/bin/env python2

import argparse
import os
import struct
from common.isa import *

def parse_line(line):
	instruction = line.split()

	# opcode is always the leftmost string
	opcode = instruction[0]

	mcode = "None"

	if opcode == "halt":
		mcode = OPCODES["halt"]
		mcode = mcode.ljust(INSTRUCTION_SIZE, "0")
	elif opcode == "store":
		mcode = OPCODES["store"]
		mcode += REGISTERS[instruction[1]]
		mcode += REGISTERS[instruction[2]]
	elif opcode == "load":
		mcode = OPCODES["load"]
		mcode += REGISTERS[instruction[1]]
		mcode += REGISTERS[instruction[2]]

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