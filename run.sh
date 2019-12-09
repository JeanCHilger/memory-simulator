#!/bin/bash

g++ -c utils.cpp -lm
g++ -c objects.cpp -lm
g++ -o run utils.o objects.o
./run

rm -rf *.o
rm -rf run

