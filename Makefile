.PHONY: all build compile run clear

all:: clear compile run

clear:
	clear

build:
	cmake -B build

compile:
	cmake --build build -- -j8

run:
	./build/bin/mario

tool:
	g++ parse.cpp -o parse -std=c++17 -I/usr/local/opt/llvm/include -L/usr/local/opt/llvm/lib -lclang -lLLVM