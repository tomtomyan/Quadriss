CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD
EXEC = quadris
OBJECTS = main.o grid.o cell.o block.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
