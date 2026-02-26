#!/bin/bash

g++ src/main.cpp -o out `pkg-config --cflags --libs sdl2` && ./out ; rm ./out