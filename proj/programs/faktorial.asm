movi a 5
movi b 1
movi c 1
movi jmp_next .loop
.loop:
	inc c 1
	mul b c
jl c a
stop


