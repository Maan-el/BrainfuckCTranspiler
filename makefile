##
# BrainfugCTranspiler
#
# @file
# @version 0.1

all:
	gcc Brainfuck.c -W -Wall -std=c11 -pedantic
	./a.out arq.b
	rm a.out
	gcc output.c -W -Wall -std=c11 -pedantic -o output
	./output

# end
