
default:
	mkdir -p bin
	g++ src/main.cpp -o bin/rw -Wall -Wextra -Werror
