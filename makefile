all: main.o
	gcc -o run main.o
main.o: main.c
	gcc -c main.c
run:
	./run
clean:
	rm *.o
