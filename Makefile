# A Makefile for simple lex and yacc examples

# Comment out the proper lines below according to the scanner and
# parser generators available in your system

LEX = flex
YACC = bison -d -y
# LEX = flex 
# YACC = bison -d

# We assume that your C-compiler is called gcc

CC = g++ -std=c++17 -Wall -Werror

# Parser is the final object that we will generate, it is produced by
# the C compiler from the y.tab.o and from the lex.yy.o

DedalCompiler: y.tab.o lex.yy.o
	$(CC) -o DedalCompiler y.tab.o lex.yy.o -lm main.cpp

y.tab.o: y.tab.c
lex.yy.o: lex.yy.c

## This rule will use yacc to generate the files y.tab.c and y.tab.h
## from our file parser.y

y.tab.c y.tab.h: parser.y
	$(YACC) -v parser.y

## this is the make rule to use lex to generate the file lex.yy.c from
## our file lexer.l

lex.yy.c: lexer.l
	$(LEX) lexer.l

## Make clean will delete all of the generated files so we can start
## from scratch

clean:
	-rm -f lex.yy.c lex.yy.o *.tab.*  DedalCompiler *.output
