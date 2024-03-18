cmake_minimum_required(VERSION 3.10)
project(MfcProject002)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включаем заголовочные файлы
include_directories(include)

# Добавляем дополнительные cpp файлы
add_executable(MfcProject002 
    main.cpp
    CMyWindow.cpp
)
