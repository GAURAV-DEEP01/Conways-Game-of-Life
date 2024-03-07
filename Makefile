all:
	gcc -I src/include -L src/lib -o exe/main main.c app/src/gameOfLife.c app/src/golUI.c  -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf