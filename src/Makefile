CC = gcc


#the .o tells the make file to build the files before executing
main: parser.tab.o lex.yy.o
	$(CC) lex.yy.o parser.tab.o main.c -o minic -lfl

parser.tab.c parser.tab.h: mini.y
	bison --yacc --verbose --defines=parser.tab.c --output=parser.tab.h --verbose mini.y

lex.yy.c: mini.l parser.tab.h
	flex mini.l

clean:
	rm parser.tab.* lex.yy.* minic parser.output

