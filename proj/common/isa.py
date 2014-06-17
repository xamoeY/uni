OPCODES = {"stop"    :"0000",
		   "store"   :"0001",
		   "load"    :"0010",
		   "mov"     :"0011",
		   "movi"    :"0100",
		   "add"     :"0101",
		   "sub"     :"0110",
		   "mul"     :"0111",
		   "div"	 :"1000",
		   "not"     :"1001",
		   "and"     :"1010",
		   "or"      :"1011",
		   "shift_l" :"1100",
		   "shift_r" :"1101",
	 	   "cmp"     :"1110",
		   "je"      :"1111"}

REGISTERS = {"zero"       :"000000",
			 "pc"         :"000001",
			 "cmp_result" :"000010",
			 "jmp_next"   :"000011",
			 "temp"       :"000100",
			 "a"          :"000101",
			 "b"          :"000110",
			 "c"          :"000111",
			 "d"          :"001000"}

INSTRUCTION_SIZE = 16

PROGRAM_COUNTER = 0