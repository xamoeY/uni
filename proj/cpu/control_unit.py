from myhdl import *
from common.isa import *
from cpu.memory import *
from cpu.register_bank import *

def control_unit(opcode, op1, op2, clk,
                 m_we, m_sig_in, m_sig_out, m_address,
                 r_sig_in, r_sig_out, r_register, r_we):
    """Control unit, manages control operations.
    If alu operations accure, redirects them to alu
    """

    @instance
    def logic():
        yield clk.posedge
        if opcode == OPCODES["stop"]:
            raise StopSimulation
        elif opcode == OPCODES["store"]:
            print "enter store"
            m_address.next = op2
            r_register.next = op1
            yield r_sig_out
            print "post yield"
            m_sig_in.next = r_sig_out
        elif opcode == OPCODES["load"]:
            m_address.next = op2
            r_register.next = op1
            yield m_sig_out
            r_sig_in.next = m_sig_out
        elif opcode == OPCODES["mov"]:
            temp = None
            r_register.next = op1
            yield r_sig_out
            temp = r_sig_out
            r_register.next = op2
            yield r_sig_out
            r_sig_in.next = temp
        elif opcode == OPCODES["movi"]:
            r_register.next = op1
            r_sig_in.next = op2
        elif opcode == OPCODES["je"]:
            pass
        else:
            # alu
            pass

    return logic
