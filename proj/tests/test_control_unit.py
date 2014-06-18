from cpu.control_unit import *
from myhdl import *
from common.isa import *

def test_control_unit():
    clk = Signal(bool(0))

    m_we = Signal(bool(0))
    m_sig_in = Signal(intbv(0)[WIDTH:])
    m_sig_out = Signal(intbv(0)[WIDTH:])
    m_address = Signal(intbv(0)[WIDTH:])
    mem_inst = memory(m_we, m_address, m_sig_in, m_sig_out, clk)

    r_sig_in = Signal(intbv(1)[8:])
    r_sig_out = Signal(intbv(3)[8:])
    r_register = Signal(REGISTERS["zero"])
    r_we = Signal(bool(0))
    register_bank_inst = register_bank(r_register, r_sig_in, r_sig_out, r_we, clk)

    opcode = Signal(OPCODES["load"])
    op1 = Signal(intbv(0)[WIDTH:])
    op2 = Signal(intbv(0)[WIDTH:])

    dut = control_unit(opcode, op1, op2, clk,
                       m_we, m_sig_in, m_sig_out, m_address,
                       r_sig_in, r_sig_out, r_register, r_we) 
    period = 10

    @always(delay(period))
    def clkgen():
        clk.next = not clk

    @instance
    def stimulus():
        # Checking whether program stopped, by now with print
        # opcode.next = OPCODES["stop"]
        # op1.next = 3
        # op2.next = 4
        # print sim.now()

        # Check store operation
        r_register.next = REGISTERS["a"]
        r_sig_in.next = 2
        yield clk.posedge
        yield clk.negedge
        opcode.next = OPCODES["store"]
        op1.next = REGISTERS["a"]
        op2.next = 3
        assert m_sig_out != r_sig_out
        yield clk.posedge
        yield clk.negedge
        print m_sig_out, r_sig_out
        assert m_sig_out == r_sig_out

    return clkgen, stimulus, dut

sim = Simulation(test_control_unit())
sim.run()