.PHONY: build test

build:
	python2 assembler.py programs/program1.asm
	python2 assembler.py programs/program2.asm
	python2 assembler.py programs/faktorial.asm

test:
	nosetests2 -s
