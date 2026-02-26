#!/bin/bash

rm -rf dist && mkdir dist && g++ src/main.cpp -o dist/out `pkg-config --cflags --libs sdl2`