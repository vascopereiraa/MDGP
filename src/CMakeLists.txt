cmake_minimum_required(VERSION 3.17)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src main.c initDados.c utils.c pesquisaLocal.c funcoes.c evolutivo.c)