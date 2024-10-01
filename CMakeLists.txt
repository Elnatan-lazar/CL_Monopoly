cmake_minimum_required(VERSION 3.27)
project(CL_Monopoly)

set(CMAKE_CXX_STANDARD 17)

# מציאת SFML
set(CMAKE_PREFIX_PATH "C:/SFML")
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories("C:/SFML/include")

# הגדרת האובייקט המבוצע שלך עבור המשחק
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

# קישור ספריות ה-SFML למשחק
target_link_libraries(CL_Monopoly sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# הגדרת האובייקט המבוצע שלך עבור הבדיקות
add_executable(CL_Monopoly_tests
        src/Location.cpp
        src/Player.cpp
        src/Dice.cpp
        src/maingame.cpp
        src/Board.cpp
        src/playerManu.cpp
        src/Card.cpp
        src/definitions.cpp
        src/action.cpp
        src/doctest.h
        src/test.cpp
)

# קישור ספריות ה-SFML לבדיקות
target_link_libraries(CL_Monopoly_tests sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# הכללת doctest ביעד הבדיקות
target_include_directories(CL_Monopoly_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
