all:
	g++ -std=c++2a main.cpp -o main -O2 -Wall -Wextra -Wshadow -Wno-unused-result -Wno-sign-compare -fsanitize=undefined -fno-sanitize-recover
run:
	./main