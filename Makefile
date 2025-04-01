FLAGS = -pedantic-errors -std=c++11
ENGFLAG = -lncurses


main.o: main.cpp 
	g++ $(FLAGS) -c $<
	
main: main.o 
	g++ $(FLAGS) $^ -o $@ $(ENGFLAG)

run: main
	./main

clean:
	rm -f main.o main.tgz
tar:
	tar -czvf *.cpp *.h
.PHONY: clean tar