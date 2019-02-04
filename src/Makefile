CC = gcc


#the .o tells the make file to build the files before executing
main: parser.tab.o lex.yy.o tree.o tree.h main.o pretty.o pretty.h
	$(CC) -g  lex.yy.o parser.tab.o tree.o main.o pretty.o -o minic -lfl

parser.tab.c parser.tab.h: mini.y
	bison  --verbose --yacc --defines=parser.tab.c --output=parser.tab.h  mini.y

lex.yy.c: mini.l parser.tab.h
	flex mini.l

clean:
	rm parser.* lex.yy.* minic *.o
