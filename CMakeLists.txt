cmake_minimum_required(VERSION 3.7)
project(GAMagicSquare)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(SOURCE_FILES main.cpp Individual.cpp Individual.h Population.cpp Population.h Comparator.cpp Comparator.h GeneticAlgorithm.cpp GeneticAlgorithm.h timer.h)
add_executable(GAMagicSquare ${SOURCE_FILES} Individual.cpp Individual.h GeneticAlgorithm.cpp GeneticAlgorithm.h)