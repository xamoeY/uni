INSTRUCTION_SIZE = 16
WIDTH = 16
DEPTH = 32
DEBUG = True

OPCODES = {"stop"    :0b0000,
           "store"   :0b0001,
           "load"    :0b0010,
           "mov"     :0b0011,
           "movi"    :0b0100,
           "add"     :0b0101,
           "sub"     :0b0110,
           "mul"     :0b0111,
           "div"     :0b1000,
           "not"     :0b1001,
           "and"     :0b1010,
           "or"      :0b1011,
           "shift_l" :0b1100,
           "shift_r" :0b1101,
           "cmp"     :0b1110,
           "je"      :0b1111}

REGISTERS = {"zero"       :0b000000,
             "pc"         :0b000001,
             "cmp_result" :0b000010,
             "jmp_next"   :0b000011,
             "tmp1"       :0b000100,
             "tmp2"       :0b000101,
             "a"          :0b000110,
             "b"          :0b000111,
             "c"          :0b001000,
             "d"          :0b001001,
             "e"          :0b001010,
             "f"          :0b001011,
             "g"          :0b001100,
             "h"          :0b001101}

# Reverse dict to lookup OPCODES or REGISTERS by int
ROPCODES = {v:k for k,v in OPCODES.items()}
RREGISTERS = {v:k for k,v in REGISTERS.items()}
