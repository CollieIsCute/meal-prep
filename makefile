all: format	
	g++ -o main -std=c++17 main.cpp csv.cpp
format:
	clang-format -style=file -i *.cpp *.h
exe:
	./main
clean:
	rm -f main work* attend*