from myhdl import Signal, delay, always, now, Simulation

def ClkDriver(clk):
    """ClkDriver"""

    half_period = delay(10)

    @always(half_period)
    def driveClk():
        clk.next = not clk

    return driveClk
