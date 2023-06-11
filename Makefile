prog:main.o enigme5.o  
	gcc main.o enigme5.o  -o game -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
 main.o:main.c
	gcc -c main.c -g
 enigme5.o:enigme5.c
	gcc -c enigme5.c -g