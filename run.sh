#! /bin/sh

g++ -o ../main main.cpp $(pkg-config --cflags --libs gtk+-3.0)

../main