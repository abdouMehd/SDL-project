prog:tictac.o main.o
	gcc tictac.o main.o -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_image -lSDL_mixer -g 
main.o:main.c 
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
fonction.o:tictac.c
	gcc -c tictac.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
