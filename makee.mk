a.exe: kindaworking.o fns.o
	gcc kindaworking.o fns.o
kindaworking.o: kindaworking.c headerh.h 
	gcc -c kindaworking.c
fns.o: fns.c headerh.h
	gcc -c fns.c