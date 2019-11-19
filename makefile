all: direct.o
			gcc -o program direct.o
stat.o: direct.c
			gcc -c direct.c
run:
			./program
clean:
			rm *.o
			rm program.exe
			rm *~
