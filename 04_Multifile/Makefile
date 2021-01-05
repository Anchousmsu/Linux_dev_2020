GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.*
CFLAGS = -fPIC -Wall
LIBS = liboutput_static.a liboutput.so

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

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)

allclean:	clean distclean
	rm -rf $(LIBS)
