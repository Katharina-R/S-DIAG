all:
	g++ -std=c++17 main.cpp -o main -O2 -Wall -Wextra -Wshadow -Wno-unused-result -Wno-sign-compare -fsanitize=undefined -fno-sanitize-recover
run:
	./main