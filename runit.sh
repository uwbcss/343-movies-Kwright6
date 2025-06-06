#!/bin/bash

echo "Compiling with ALL Movies and Commands..."

g++ -g \
  main.cpp borrowCmd.cpp classics.cpp comedy.cpp command.cpp \
  customer.cpp drama.cpp historyCmd.cpp inventoryCmd.cpp \
  movie.cpp movieStore.cpp returnCmd.cpp store_test.cpp \
  -o my_program

if [ $? -eq 0 ]; then
  echo "Compilation successful. Running program..."
  ./my_program
else
  echo "Compilation failed."
fi