

.s.o:
	clang -c -g -o $@ $<	
.c.o:
	clang -c -g -o $@ $<	

darm64execmemtest: main.o
	clang -g -o $@ $<
	codesign --sign - --entitlements darwin-arm64-execmemtest.entitlements \
		--deep $@ --force

clean:
	rm *.o darm64execmemtest

all: darm64execmemtest
