all:
	g++ -I src/include -L src/lib -o ./exe/main main.cpp ./app/src/gameOfLife.cpp  -lmingw32 -lSDL2main -lSDL2