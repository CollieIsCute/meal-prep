all:
	clang-format -style=file -i *.cpp *.h
	g++ -o main.out -std=c++17 main.cpp csv.cpp
exe:
	./main.out
clean:
	rm -f main.out 打飯表1.txt 打飯表2.txt