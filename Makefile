# Makedatei (Linux, Mac OS) zur Erzeugung des compute_edit_distance-Programms
# Zum Erzeugen bitte "make" in der Shell schreiben
# Je nach bevorzugtem Compiler (clang++ oder g++) den jeweils anderen einfach auskommentieren

CC=clang++
#CC=g++
FLAGS=-Wall -O3

# Top-Target
all: build documentation

# Baue Programm
build: src/edit_distance_computation.cpp include/EditDistance.hpp
	$(CC) $(FLAGS) src/edit_distance_computation.cpp -o bin/compute_ed

# Erzeuge html-Doku
documentation:
	doxygen doc/levenshtein.doxygen
	mv html doc/

# Lösche alle erzeugten Dateien
clean:
	rm bin/compute_ed
	rm -R doc/html 
