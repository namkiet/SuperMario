.PHONY: all build compile run clear

all:: clear compile run

clear:
	clear

build:
	cmake -B build

compile:
	cmake --build build -- -j8

run:
	./build/bin/main

