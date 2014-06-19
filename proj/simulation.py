import argparse
import struct

from myhdl import *

from common.isa import *
from cpu.clkdriver import ClkDriver
from cpu.ram import Ram
from cpu.rom import Rom
from cpu.instruction_unit import InstructionUnit

def load_program(path):
    """Load program into list of instructions

    returns list of instructions a unsigned shorts
    """
    instructions = []
    file_in = open(path, "rb")
    data_in = None

    try:
        short = file_in.read(2)
        while short:
            instruction = (struct.unpack('<H', short))

            # Get first elemenet because they are tuples within tuples
            instructions.append(instruction[0])

            short = file_in.read(2)
    finally:
        file_in.close()

    return tuple(instructions)

def cpu_simulation():
    parser = argparse.ArgumentParser(description="assembler")
    parser.add_argument('file')
    args = parser.parse_args()

    program = load_program(args.file)

    # Clock
    clk = Signal(0)
    clk_driver = ClkDriver(clk)

    # Program Counter
    pc = Signal(intbv(0)[WIDTH:])

    # ROM
    rom_dout = Signal(intbv(0)[WIDTH:])
    rom = Rom(rom_dout, pc, program)

    # RAM
    ram_dout = Signal(intbv(0)[WIDTH:])
    ram_din = Signal(intbv(0)[WIDTH:])
    ram_addr = Signal(intbv(0)[WIDTH:])
    ram_we = Signal(bool(0))
    ram = Ram(ram_dout, ram_din, ram_addr, ram_we, clk)

    # InstructionUnit
    opcode = Signal(intbv(0)[4:])
    op1 = Signal(intbv(0)[6:])
    op2 = Signal(intbv(0)[6:])
    iu = InstructionUnit(rom_dout, opcode, op1, op2)

    @instance
    def stimulus():
        if DEBUG: print "start"
        yield clk.posedge
        while opcode != 0:
            # This is basically our Control Unit
            if opcode == OPCODES["store"]:
                if DEBUG: print "store {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                m_address.next = op2
                r_register.next = op1
                yield r_sig_out
                m_sig_in.next = r_sig_out
            elif opcode == OPCODES["load"]:
                if DEBUG: print "load {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                m_address.next = op2
                r_register.next = op1
                yield m_sig_out
                r_sig_in.next = m_sig_out
            elif opcode == OPCODES["mov"]:
                if DEBUG: print "mov {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                temp = None
                r_register.next = op1
                yield r_sig_out
                temp = r_sig_out
                r_register.next = op2
                yield r_sig_out
                r_sig_in.next = temp
            elif opcode == OPCODES["movi"]:
                if DEBUG: print "movi {} {}".format(RREGISTERS[int(op1)], int(op2))
                r_register.next = op1
                r_sig_in.next = op2
            elif opcode == OPCODES["add"]:
                if DEBUG: print "add {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a + b
            elif opcode == OPCODES["sub"]:
                if DEBUG: print "sub {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a - b
            elif opcode == OPCODES["mul"]:
                if DEBUG: print "mul {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a * b
            elif opcode == OPCODES["div"]:
                if DEBUG: print "div {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a // b
            elif opcode ==  OPCODES["not"]:
                if DEBUG: print "not {}".format(RREGISTERS[int(op1)])
                result.next = ~a
            elif opcode == OPCODES["and"]:
                if DEBUG: print "and {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a & b
            elif opcode == OPCODES["or"]:
                if DEBUG: print "or {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a | b
            elif opcode == OPCODES["shift_l"]:
                if DEBUG: print "shift_l {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a << b
            elif opcode == OPCODES["shift_r"]:
                if DEBUG: print "shift_r {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                result.next = a >> b
            elif opcode == OPCODES["cmp"]:
                if DEBUG: print "cmp {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                if a < b:
                    result.next = -1
                elif a == b:
                    result.next = 0
                elif a > b:
                    result.next = 1
            elif opcode == OPCODES["je"]:
                if DEBUG: print "je {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])

            # After instruction, increase pc
            pc.next = pc + 1
            yield clk.posedge
        if DEBUG: print "end"
        raise StopSimulation

    return clk_driver, stimulus, rom, ram, iu

sim = Simulation(cpu_simulation())
sim.run()
