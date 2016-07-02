app: main.o
	g++ -o app main.o -lopenblas
main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++11 -Dunix

clean:
	rm app *.o


