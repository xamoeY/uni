import argparse
import struct

from myhdl import *

from common.isa import *
from cpu.clkdriver import ClkDriver
from cpu.ram import Ram
from cpu.rom import Rom
from cpu.instruction_unit import InstructionUnit
from cpu.register_bank import RegisterBank

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

    # Register Bank
    reg_dout = Signal(intbv(0)[WIDTH:])
    reg_din = Signal(intbv(0)[WIDTH:])
    reg_current = Signal(intbv(0)[WIDTH:])
    reg_we = Signal(bool(0))
    rb = RegisterBank(reg_dout, reg_din, reg_current, reg_we, clk)

    # InstructionUnit
    opcode = Signal(intbv(0)[4:])
    op1 = Signal(intbv(0)[6:])
    op2 = Signal(intbv(0)[6:])
    iu = InstructionUnit(rom_dout, opcode, op1, op2)

    @instance
    def stimulus():
        if DEBUG: print "program start"
        yield clk.posedge
        while opcode != 0:
            print "PC {}".format(pc)
            # This is basically our Control Unit
            if opcode == OPCODES["store"]:
                if DEBUG: print "=> store {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op1
                yield clk.posedge
                ram_we.next = True
                ram_addr.next = op2
                ram_din.next = reg_dout
                yield clk.posedge
                ram_we.next = False
            elif opcode == OPCODES["load"]:
                if DEBUG: print "=> load {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                ram_addr.next = op2
                yield clk.posedge
                reg_we.next = True
                reg_current.next = op1
                reg_din.next = ram_dout
                yield clk.posedge
                reg_we.next = False
                yield clk.posedge
            elif opcode == OPCODES["mov"]:
                if DEBUG: print "=> mov {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_we.next = True
                reg_current.next = op1
                reg_din.next = reg_op2
                yield clk.posedge
            elif opcode == OPCODES["movi"]:
                if DEBUG: print "=> movi {} {}".format(RREGISTERS[int(op1)], int(op2))
                reg_current.next = op1
                reg_din.next = op2
                reg_we.next = True
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["add"]:
                if DEBUG: print "=> add {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 + reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["sub"]:
                if DEBUG: print "=> sub {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 - reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["mul"]:
                if DEBUG: print "=> mul {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 * reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["div"]:
                if DEBUG: print "=> div {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 // reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode ==  OPCODES["not"]:
                if DEBUG: print "=> not {}".format(RREGISTERS[int(op1)])
                reg_current.next = op1
                yield clk.posedge
                reg_we.next = True
                reg_din.next = ~reg_op1
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["and"]:
                if DEBUG: print "=> and {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 & reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["or"]:
                if DEBUG: print "=> or {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 | reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["shift_l"]:
                if DEBUG: print "=> shift_l {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 << reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["shift_r"]:
                if DEBUG: print "=> shift_r {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_din.next = reg_op1 >> reg_op2
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["cmp"]:
                if DEBUG: print "=> cmp {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])
                reg_current.next = op2
                yield clk.posedge
                reg_op2 = Signal(reg_dout)

                reg_current.next = op1
                yield clk.posedge
                reg_op1 = reg_dout

                reg_we.next = True
                reg_current.next = REGISTERS["cmp_result"]
                if reg_op1 < reg_op2:
                    reg_din.next = -1
                elif reg_op1 == reg_op2:
                    reg_din.next = 0
                elif reg_op1 > reg_op2:
                    reg_din.next = 1
                yield clk.posedge
                reg_we.next = False
            elif opcode == OPCODES["je"]:
                if DEBUG: print "=> je {} {}".format(RREGISTERS[int(op1)], RREGISTERS[int(op2)])

            # After instruction, increase pc
            pc.next = pc + 1
            yield clk.posedge
        if DEBUG: print "program end"

        # At end of program, show registers and memory
        if DEBUG:
            print "registers:"
            for i in range(9):
                reg_current.next = i
                yield clk.posedge
                reg_we.next = False
                print "{}: {}".format(RREGISTERS[i], reg_dout)

        raise StopSimulation

    return clk_driver, stimulus, rom, ram, iu, rb

sim = Simulation(cpu_simulation())
sim.run()
