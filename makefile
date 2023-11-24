
xo: xo.o stringmanip.o
	gcc xo.o stringmanip.o

xo.o: xo.c
	gcc -c xo.c

stringmanip.o: helpers/stringmanip.c helpers/stringmanip.h
	gcc -c helpers/stringmanip.c

clean: 
	rm *.o a.out
