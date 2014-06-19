movi a 5
movi b 1
movi c 1
.loop
movi jmp_next .loop
inc c
mul b c
jl c a
stop
