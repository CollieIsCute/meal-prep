all: format	
	g++ -o main.out -std=c++17 main.cpp csv.cpp
format:
	clang-format -style=file -i *.cpp *.h
exe:
	./main.out
clean:
	rm -f main.out 打飯表1.txt 打飯表2.txt