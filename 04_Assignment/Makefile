BISON=bison
FLEX=flex
CC=gcc
CFLAGS=-Wall -Wextra -O2

all: ir_codegen

ir_codegen: ir_codegen.tab.c lex.yy.c
	$(CC) $(CFLAGS) ir_codegen.tab.c lex.yy.c -o ir_codegen -lfl

ir_codegen.tab.c ir_codegen.tab.h: ir_codegen.y
	$(BISON) -d ir_codegen.y

lex.yy.c: ir_codegen.l ir_codegen.tab.h
	$(FLEX) ir_codegen.l

run: ir_codegen
	./ir_codegen testcases/part1/ex1_arith.c resuls/result_part1/ex1_arith.txt

clean:
	rm -f ir_codegen ir_codegen.tab.c ir_codegen.tab.h lex.yy.c *.output *.o resuls/result_part1/*.txt resuls/result_part2/*.txt resuls/result_part3/*.txt resuls/result_part4/*.txt
