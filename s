cmake_minimum_required(VERSION 3.27)
project(CL_Monopoly)

set(CMAKE_CXX_STANDARD 17)

# Find SFML package
set(CMAKE_PREFIX_PATH "C:/SFML")
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
include_directories(headers /usr/include C:/SFML/include)

add_executable(CL_Monopoly
        src/Location.cpp
        src/Location.hpp
        src/Player.cpp
        src/Player.hpp
        src/Dice.cpp
        src/Dice.hpp
        src/maingame.cpp
        src/maingame.hpp
        src/Board.hpp
        src/playerManu.cpp
        src/playerManu.hpp
        src/Board.cpp
        src/Card.cpp
        src/Card.hpp
        src/main.cpp
)
