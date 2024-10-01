# Usage:
# make           # Compile Monopoly executable along with object files
# make Monopoly  # Compile only Monopoly executable
# make clean     # Removes all binaries and objects
# make valgrind  # Run Valgrind for memory leak checking

.PHONY: all clean Monopoly valgrind
CC := g++
CFLAGS := -Wall -Wextra -pedantic -std=c++11

# Add OpenGL libraries only for Windows, adjust for Linux otherwise
ifeq ($(OS), Windows_NT)
    LDFLAGS := -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio
else
    LDFLAGS := -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
endif

SRCS := $(wildcard ./src/*.cpp)
OBJS := ./obj/definitions.o ./obj/main.o ./obj/Board.o ./obj/maingame.o ./obj/Dice.o ./obj/Player.o ./obj/Location.o ./obj/Card.o ./obj/playerManu.o ./obj/action.o

ifeq ($(OS), Windows_NT)
    RM := del /Q
    RMOFILES := del /Q ./obj/*.o
else
    RM := rm -f
    RMOFILES := rm -f ./obj/*.o
endif

all: OFiles
	${CC} ${CFLAGS} ${OBJS} -o Monopoly ${LDFLAGS}
	@echo Make successful

Monopoly: ${SRCS}
	${CC} ${CFLAGS} ${SRCS} -o Monopoly ${LDFLAGS}
	@echo Compiled Monopoly successfully

OFiles: $(OBJS)
	@echo Files compiled successfully

./obj/definitions.o: ./src/definitions.cpp ./src/definitions.hpp
	${CC} ${CFLAGS} -c ./src/definitions.cpp -o ./obj/definitions.o

./obj/main.o: ./src/main.cpp
	${CC} ${CFLAGS} -c ./src/main.cpp -o ./obj/main.o

./obj/action.o: ./src/action.cpp ./src/action.hpp
	${CC} ${CFLAGS} -c ./src/action.cpp -o ./obj/action.o

./obj/playerManu.o: ./src/playerManu.cpp ./src/playerManu.hpp
	${CC} ${CFLAGS} -c ./src/playerManu.cpp -o ./obj/playerManu.o

./obj/maingame.o: ./src/maingame.cpp ./src/maingame.hpp
	${CC} ${CFLAGS} -c ./src/maingame.cpp -o ./obj/maingame.o

./obj/Location.o: ./src/Location.cpp ./src/Location.hpp
	${CC} ${CFLAGS} -c ./src/Location.cpp -o ./obj/Location.o

./obj/Dice.o: ./src/Dice.cpp ./src/Dice.hpp
	${CC} ${CFLAGS} -c ./src/Dice.cpp -o ./obj/Dice.o

./obj/Player.o: ./src/Player.cpp ./src/Player.hpp
	${CC} ${CFLAGS} -c ./src/Player.cpp -o ./obj/Player.o

./obj/Board.o: ./src/Board.cpp ./src/Board.hpp
	${CC} ${CFLAGS} -c ./src/Board.cpp -o ./obj/Board.o

./obj/Card.o: ./src/Card.cpp ./src/Card.hpp
	${CC} ${CFLAGS} -c ./src/Card.cpp -o ./obj/Card.o

clean:
	$(RM) Monopoly*
	$(RMOFILES)
	@echo Clean successful

# Valgrind command to check memory leaks
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-report.txt ./Monopoly
	@echo Valgrind check completed. See valgrind-report.txt for details.
