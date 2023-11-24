
xo: xo.o stringmanip.o config.o
	gcc xo.o stringmanip.o config.o

xo.o: xo.c
	gcc -c xo.c

stringmanip.o: helpers/stringmanip.c helpers/stringmanip.h
	gcc -c helpers/stringmanip.c

config.o: helpers/config.c helpers/config.h
	gcc -c helpers/config.c

clean: 
	rm *.o a.out
