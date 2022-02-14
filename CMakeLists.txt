cmake_minimum_required(VERSION 3.19)
project(AVR_Project_Main C)

set(CMAKE_C_STANDARD 99)

add_executable(AVR_Project_Main Hex2Char.c Count2Binary.c Count2Binary.h Hex2Char.h Timer2Count.h Bin2Hex+Len.c Bin2Hex+Len.h main.c main.h)