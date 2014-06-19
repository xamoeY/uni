#!usr/bin/env python2

import argparse
import os
import struct
from common.isa import *
from common.utils import *

def parse_line(line):
    instruction = line.split()

    # opcode is always the leftmost string
    opcode = instruction[0]

    mcodes = []

    if opcode == "stop":
        mcode = get_opcode_bitstring("stop")
        mcode = mcode.ljust(INSTRUCTION_SIZE, "0")
        mcodes.append(mcode)
    elif opcode == "store":
        mcode = get_opcode_bitstring("store")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "load":
        mcode = get_opcode_bitstring("load")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "mov":
        mcode = get_opcode_bitstring("mov")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "movi":
        mcode = get_opcode_bitstring("movi")
        mcode += get_register_bitstring(instruction[1])
        mcode += "{0:06b}".format(int(instruction[2]))
        mcodes.append(mcode)
    elif opcode == "add":
        mcode = get_opcode_bitstring("add")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "sub":
        mcode = get_opcode_bitstring("sub")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "mul":
        mcode = get_opcode_bitstring("mul")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "div":
        mcode = get_opcode_bitstring("div")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "addi":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "subi":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "muli":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "divi":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "inc":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "dec":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "not":
        mcode = get_opcode_bitstring("not")
        mcode += get_register_bitstring(instruction[1])
        mcode = mcode.ljust(INSTRUCTION_SIZE, "0")
        mcodes.append(mcode)
    elif opcode == "and":
        mcode = get_opcode_bitstring("and")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "or":
        mcode = get_opcode_bitstring("or")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "shift_l":
        mcode = get_opcode_bitstring("shift_l")
        mcode += get_register_bitstring(instruction[1])
        mcode += "{0:06b}".format(int(instruction[2]))
        mcodes.append(mcode)
    elif opcode == "shift_r":
        mcode = get_opcode_bitstring("shift_r")
        mcode += get_register_bitstring(instruction[1])
        mcode += "{0:06b}".format(int(instruction[2]))
        mcodes.append(mcode)
    elif opcode == "cmp":
        mcode = get_opcode_bitstring("cmp")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "j":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "je":
        mcode = get_opcode_bitstring("je")
        mcode += get_register_bitstring(instruction[1])
        mcode += "{0:06b}".format(int(instruction[2]))
        mcodes.append(mcode)
    elif opcode == "jne":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "jg":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "jge":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "jl":
        mcode = None
        mcodes.append(mcode)
    elif opcode == "jle":
        mcode = None
        mcodes.append(mcode)

    return mcodes

def parse_file(source_file):
    instructions = []

    for number, value in enumerate(source_file):
        instructions += parse_line(value)

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
        # encode as short because this is for a 16 bit CPU
        short = struct.pack('<H', int(instruction, 2))
        binary_file.write(short)

if __name__ == '__main__':
    main()
