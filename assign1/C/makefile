OPTIONS=-std=c99 -O2

all:	assign1

assign1: basesixtyfour.o hexConverter.o main.o
	gcc $(OPTIONS) basesixtyfour.o hexConverter.o main.o -o assign1

basesixtyfour.o: basesixtyfour.h basesixtyfour.c
	gcc $(OPTIONS) -c basesixtyfour.c

hexConverter.o: hexConverter.h hexConverter.c
	gcc $(OPTIONS) -c hexConverter.c

main.o: basesixtyfour.h hexConverter.h main.c
	gcc $(OPTIONS) -c main.c

clean:
	rm -f assign1
	rm -f *.o