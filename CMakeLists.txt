cmake_minimum_required(VERSION 3.27)
project(CL_Monopoly)

set(CMAKE_CXX_STANDARD 17)

# מציאת SFML
set(CMAKE_PREFIX_PATH "C:/SFML")
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories("C:/SFML/include")

# הגדרת האובייקט המבוצע שלך עם כל הקבצים שציינת
add_executable(CL_Monopoly
        src/Location.cpp
        src/Location.hpp
        src/Player.cpp
        src/Player.hpp
        src/Dice.cpp
        src/Dice.hpp
        src/maingame.cpp
        src/maingame.hpp
        src/Board.cpp
        src/Board.hpp
        src/playerManu.cpp
        src/playerManu.hpp
        src/Card.cpp
        src/Card.hpp
        src/main.cpp
        src/definitions.cpp
        src/definitions.hpp
        src/action.cpp
        src/action.hpp
)

# קישור ספריות ה-SFML
target_link_libraries(CL_Monopoly sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
