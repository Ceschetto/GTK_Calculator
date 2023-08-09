compile : calculator.o 
	gcc src/test.c `pkg-config --cflags gtk4` -o bin/test `pkg-config --cflags --libs gtk4` obj/calculator_data.o 

calculator.o: headers/calculator_data.h
	gcc -c src/calculator_data.c -o obj/calculator_data.o


run:
	./bin/test
