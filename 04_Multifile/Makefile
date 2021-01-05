GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.*
CFLAGS = -fPIC -Wall
LIBS = liboutput_static.a liboutput.so
TESTS = test_prog*

all:    README prog

prog:   const.o fun.o prog.o

README: prog
	./$< 2> $@

fun.o:  outlib.h

liboutput_static.a: const.o fun.o
	ar rcs $@ $^

liboutput.so: const.o fun.o
	$(CC) -shared $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -lncurses -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -lncurses -o $@

test: prog prog-a prog-so
	./prog > test_prog1
	./prog-a > test_prog-a1
	LD_LIBRARY_PATH=`pwd` ./prog-so > test_prog-so1
	./prog par1 > test_prog2
	./prog-a par1 > test_prog-a2
	LD_LIBRARY_PATH=`pwd` ./prog-so par1 > test_prog-so2
	./prog par1 par2 par3 > test_prog3
	./prog-a par1 par2 par3 > test_prog-a3
	LD_LIBRARY_PATH=`pwd` ./prog-so par1 par2 par3 > test_prog-so3
	cmp test_prog1 test_prog-a1
	cmp test_prog1 test_prog-so1
	cmp test_prog-a1 test_prog-so1
	cmp test_prog2 test_prog-a2
	cmp test_prog2 test_prog-so2
	cmp test_prog-a2 test_prog-so2
	cmp test_prog3 test_prog-a3
	cmp test_prog3 test_prog-so3
	cmp test_prog-a3 test_prog-so3

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES) $(TESTS)

allclean:	clean distclean
	rm -rf $(LIBS)
