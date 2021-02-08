all:
	g++ -o a.out -std=c++17 打飯分配程式.cpp
exe:
	./a.out
clean:
	rm -f a.out 打飯表1.txt 打飯表2.txt