.PHONY: all build compile run clear tool

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
	g++ tool/parse.cpp -o tool/parse -std=c++17 -I/usr/local/opt/llvm/include -L/usr/local/opt/llvm/lib -lclang -lLLVM