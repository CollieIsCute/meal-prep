all:
	g++ -o main -std=c++20 main.cpp CSV-header/csv.cpp calendar.cpp -static
format:
	clang-format -style=file -i *.cpp *.h
exe:
	./main
clean:
	rm -f main work* attend*