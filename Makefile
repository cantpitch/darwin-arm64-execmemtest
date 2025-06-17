

.s.o:
	clang -c -o $@ $<	

darm64execmemtest: main.o
	clang -o $@ $<

all: darm64execmemtest
