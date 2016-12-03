all:
	-mkdir -p bin 
	g++ -Wall -Werror -ansi -pedantic -o bin/rshell src/main.cpp
	
rshell:
	-mkdir -p bin 
	g++ -Wall -Werror -ansi -pedantic -o bin/rshell src/main.cpp