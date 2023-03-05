#!/bin/sh

gcc \
     ./CommandBattle.c \
\
     -L ./sisters/ -lSisters \
\
     -o ./CommandBattle

echo Completed!
