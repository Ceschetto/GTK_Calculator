output : obj/calculator_data.o obj/gtk_interface.o
	gcc src/main.c `pkg-config --cflags gtk4` -o bin/main obj/gtk_interface.o obj/calculator_data.o `pkg-config --cflags --libs gtk4` 


obj/gtk_interface.o:  obj/calculator_data.o
	gcc -c src/gtk_interface.c `pkg-config --cflags gtk4` -o obj/gtk_interface.o `pkg-config --cflags --libs gtk4` 

obj/calculator_data.o: headers/calculator_data.h src/calculator_data.c
	gcc -c src/calculator_data.c -o obj/calculator_data.o






clean: 
	rm -f bin/*
	rm -f obj/*


run:
	./bin/main

