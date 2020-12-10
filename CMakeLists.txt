cmake_minimum_required(VERSION 3.17)
project(Base_Calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Base_Calculator Somadora.h Somadora.cpp Conversor.h Conversor.cpp Subtradora.h Subtradora.cpp Auxiliadora.h Auxiliadora.cpp Multiplicadora.h Multiplicadora.cpp Divisora.h Divisora.cpp Validadora.cpp Validadora.h testes.cpp)