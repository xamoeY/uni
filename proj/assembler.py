#!usr/bin/env python2

import argparse
import os
import struct
from common.isa import *
from common.utils import *

def parse_line(line):
    """Parses a single line

    returns list of resulting machine code instructions"""

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

        # Special handling for labels
        # We will replace it with the correct line later
        if instruction[2].startswith('.'):
            mcode += instruction[2]
        else:
            mcode += "{0:06b}".format(int(instruction[2]))
        mcodes.append(mcode)
    elif opcode == "swap":
        code1 = get_opcode_bitstring("mov")
        code1 += get_register_bitstring("tmp1")
        code1 += get_register_bitstring(instruction[1])
        code2 = get_opcode_bitstring("mov")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring(instruction[2])
        code3 = get_opcode_bitstring("mov")
        code3 += get_register_bitstring(instruction[2])
        code3 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
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
    elif opcode == "mod":
        code1 = get_opcode_bitstring("mov")
        code1 += get_register_bitstring("tmp1")
        code1 += get_register_bitstring(instruction[1])
        code2 = get_opcode_bitstring("div")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring(instruction[2])
        code3 = get_opcode_bitstring("mul")
        code3 += get_register_bitstring(instruction[1])
        code3 += get_register_bitstring(instruction[2])
        code4 = get_opcode_bitstring("sub")
        code4 += get_register_bitstring("tmp1")
        code4 += get_register_bitstring(instruction[1])
        code5 = get_opcode_bitstring("mov")
        code5 += get_register_bitstring(instruction[1])
        code5 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
        mcodes.append(code4)
        mcodes.append(code5)
    elif opcode == "addi":
        code1 = get_opcode_bitstring("movi")
        code1 += get_register_bitstring("tmp1")
        code1 += "{0:06b}".format(int(instruction[2]))
        code2 = get_opcode_bitstring("add")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "subi":
        code1 = get_opcode_bitstring("movi")
        code1 += get_register_bitstring("tmp1")
        code1 += "{0:06b}".format(int(instruction[2]))
        code2 = get_opcode_bitstring("sub")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "muli":
        code1 = get_opcode_bitstring("movi")
        code1 += get_register_bitstring("tmp1")
        code1 += "{0:06b}".format(int(instruction[2]))
        code2 = get_opcode_bitstring("mul")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "divi":
        code1 = get_opcode_bitstring("movi")
        code1 += get_register_bitstring("tmp1")
        code1 += "{0:06b}".format(int(instruction[2]))
        code2 = get_opcode_bitstring("div")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "inc":
        code1 = get_opcode_bitstring("movi")
        code1 += get_register_bitstring("tmp1")
        code1 += "{0:06b}".format(1)
        code2 = get_opcode_bitstring("add")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "dec":
        code1 = get_opcode_bitstring("movi")
        code1 += get_register_bitstring("tmp1")
        code1 += "{0:06b}".format(1)
        code2 = get_opcode_bitstring("sub")
        code2 += get_register_bitstring(instruction[1])
        code2 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
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
    elif opcode == "xor":
        code1 = get_opcode_bitstring("mov")
        code1 += get_register_bitstring("tmp1")
        code1 += get_register_bitstring(instruction[1])
        code2 = get_opcode_bitstring("mov")
        code2 += get_register_bitstring("tmp2")
        code2 += get_register_bitstring(instruction[2])
        code3 = get_opcode_bitstring("or")
        code3 += get_register_bitstring("tmp1")
        code3 += get_register_bitstring("tmp2")
        code4 = get_opcode_bitstring("and")
        code4 += get_register_bitstring(instruction[1])
        code4 += get_register_bitstring(instruction[2])
        code5 = get_opcode_bitstring("not")
        code5 += get_register_bitstring(instruction[1])
        code5 = code5.ljust(INSTRUCTION_SIZE, "0")
        code6 = get_opcode_bitstring("and")
        code6 += get_register_bitstring(instruction[1])
        code6 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
        mcodes.append(code4)
        mcodes.append(code5)
        mcodes.append(code6)
    elif opcode == "nand":
        code1 = get_opcode_bitstring("and")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("not")
        code2 += get_register_bitstring(instruction[1])
        code2 = code2.ljust(INSTRUCTION_SIZE, "0")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "nor":
        code1 = get_opcode_bitstring("or")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("not")
        code2 += get_register_bitstring(instruction[1])
        code2 = code2.ljust(INSTRUCTION_SIZE, "0")
        mcodes.append(code1)
        mcodes.append(code2)
    elif opcode == "shift_l":
        mcode = get_opcode_bitstring("shift_l")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "shift_r":
        mcode = get_opcode_bitstring("shift_r")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "cmp":
        mcode = get_opcode_bitstring("cmp")
        mcode += get_register_bitstring(instruction[1])
        mcode += get_register_bitstring(instruction[2])
        mcodes.append(mcode)
    elif opcode == "j":
        code1 = get_opcode_bitstring("mov")
        code1 += get_register_bitstring("pc")
        code1 += get_register_bitstring(instruction[1])
        mcode.append(code1)
    elif opcode == "je":
        mcode = get_opcode_bitstring("je")
        mcode += get_register_bitstring(instruction[1])
        mcode += "{0:06b}".format(int(instruction[2]))
        mcodes.append(mcode)
    elif opcode == "jne":
        code1 = get_opcode_bitstring("cmp")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("movi")
        code2 += get_register_bitstring("tmp1")
        code2 += "{0:06b}".format(1)
        code3 = get_opcode_bitstring("je")
        code3 += get_register_bitstring("tmp1")
        code3 += get_register_bitstring("cmp_result")
        code4 = get_opcode_bitstring("movi")
        code4 += get_register_bitstring("tmp1")
        code4 += "{0:06b}".format(2)
        code5 = get_opcode_bitstring("je")
        code5 += get_register_bitstring("tmp1")
        code5 += get_register_bitstring("cmp_result")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
        mcodes.append(code4)
        mcodes.append(code5)
    elif opcode == "jg":
        code1 = get_opcode_bitstring("cmp")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("movi")
        code2 += get_register_bitstring("tmp1")
        code2 += "{0:06b}".format(2)
        code3 = get_opcode_bitstring("je")
        code3 += get_register_bitstring("tmp1")
        code3 += get_register_bitstring("cmp_result")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
    elif opcode == "jge":
        code1 = get_opcode_bitstring("cmp")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("movi")
        code2 += get_register_bitstring("tmp1")
        code2 += "{0:06b}".format(2)
        code3 = get_opcode_bitstring("je")
        code3 += get_register_bitstring("cmp_result")
        code3 += get_register_bitstring("tmp1")
        code4 = get_opcode_bitstring("movi")
        code4 += get_register_bitstring("tmp1")
        code4 += "{0:06b}".format(0)
        code5 = get_opcode_bitstring("je")
        code5 += get_register_bitstring("cmp_result")
        code5 += get_register_bitstring("tmp1")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
        mcodes.append(code4)
        mcodes.append(code5)
    elif opcode == "jl":
        code1 = get_opcode_bitstring("cmp")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("movi")
        code2 += get_register_bitstring("tmp1")
        code2 += "{0:06b}".format(1)
        code3 = get_opcode_bitstring("je")
        code3 += get_register_bitstring("tmp1")
        code3 += get_register_bitstring("cmp_result")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
    elif opcode == "jle":
        code1 = get_opcode_bitstring("cmp")
        code1 += get_register_bitstring(instruction[1])
        code1 += get_register_bitstring(instruction[2])
        code2 = get_opcode_bitstring("movi")
        code2 += get_register_bitstring("tmp1")
        code2 += "{0:06b}".format(1)
        code3 = get_opcode_bitstring("je")
        code3 += get_register_bitstring("tmp1")
        code3 += get_register_bitstring("cmp_result")
        code4 = get_opcode_bitstring("movi")
        code4 += get_register_bitstring("tmp1")
        code4 += "{0:06b}".format(0)
        code5 = get_opcode_bitstring("je")
        code5 += get_register_bitstring("tmp1")
        code5 += get_register_bitstring("cmp_result")
        mcodes.append(code1)
        mcodes.append(code2)
        mcodes.append(code3)
        mcodes.append(code4)
        mcodes.append(code5)
    elif opcode.startswith('.'):
        # This is a label, special care required. Put it in there for now. We
        # will deal with this properly in the post-processing.
        mcodes.append(opcode)

    return mcodes

def parse_file(source_file):
    """Parses a file

    returns a list of machine code instructions"""

    instructions = []

    for number, value in enumerate(source_file):
        instructions += parse_line(value)

    # Second pass to collect all labels
    labels = {}
    for number, value in enumerate(instructions):
        if value.startswith('.'):
            labels[value] = number

    # Remove all elements that are only labels
    for k, v in labels.items():
        instructions.remove(k)

    # Change all labels within instructions to their proper values
    for k, v in labels.items():
        instructions = [instr.replace(k, "{0:06b}".format(v)) for instr in instructions]

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
        assert len(instruction) == 16
        # encode as short because this is for a 16 bit CPU
        short = struct.pack('<H', int(instruction, 2))
        binary_file.write(short)

if __name__ == '__main__':
    main()
