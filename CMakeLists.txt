cmake_minimum_required(VERSION 3.10)
project(chess)

set(CMAKE_CXX_STANDARD 14)

list(APPEND SOURCES
        include/sources/Game.cpp
        include/sources/Cell.cpp
        src/sources/Figure.cpp
        src/sources/Pawn.cpp
        src/sources/Bishop.cpp
        src/sources/King.cpp
        src/sources/Knight.cpp
        src/sources/Rook.cpp
        src/sources/Queen.cpp)

list(APPEND TESTS test/TestCell.cpp
        test/TestGame.cpp
        test/testMain.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} src/sources/main.cpp)

add_executable(test_chess ${TESTS} ${SOURCES})
