GENERATES = prog prog-a prog-so README liboutput.so liboutput_static.a
TRASH = *.o *~ o.* *.stdout.out *.stderr.out

all:    README prog prog-a prog-so

prog:	const.o fun.o prog.o

prog-a:	prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so:	const.o fun.o
	cc -shared $^ -o $@


README:	prog
	./$< 2> $@

fun.o:	outlib.h

test:	prog prog-a prog-so
	exec -a progtest ./prog > prog.1.stdout.out 2> prog.1.stderr.out
	exec -a progtest ./prog-a > prog-a.1.stdout.out 2> prog-a.1.stderr.out
	exec -a progtest ./prog-so > prog-so.1.stdout.out 2> prog-so.1.stderr.out

	cmp -s prog.1.stdout.out prog-a.1.stdout.out
	cmp -s prog.1.stdout.out prog-so.1.stdout.out
	cmp -s prog.1.stderr.out prog-a.1.stderr.out
	cmp -s prog.1.stderr.out prog-so.1.stderr.out

	exec -a progtest ./prog wow > prog.2.stdout.out 2> prog.2.stderr.out
	exec -a progtest ./prog-a wow > prog-a.2.stdout.out 2> prog-a.2.stderr.out
	exec -a progtest ./prog-so wow > prog-so.2.stdout.out 2> prog-so.2.stderr.out

	cmp -s prog.2.stdout.out prog-a.2.stdout.out
	cmp -s prog.2.stdout.out prog-so.2.stdout.out
	cmp -s prog.2.stderr.out prog-a.2.stderr.out
	cmp -s prog.2.stderr.out prog-so.2.stderr.out

	exec -a progtest ./prog wow such test > prog.3.stdout.out 2> prog.3.stderr.out
	exec -a progtest ./prog-a wow such test > prog-a.3.stdout.out 2> prog-a.3.stderr.out
	exec -a progtest ./prog-so wow such test > prog-so.3.stdout.out 2> prog-so.3.stderr.out

	cmp -s prog.3.stdout.out prog-a.3.stdout.out
	cmp -s prog.3.stdout.out prog-so.3.stdout.out
	cmp -s prog.3.stderr.out prog-a.3.stderr.out
	cmp -s prog.3.stderr.out prog-so.3.stderr.out

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)