all:
	gcc -I src/include -L src/lib -o ./exe/main main.c ./app/src/gameOfLife.c  -lmingw32 -lSDL2main -lSDL2