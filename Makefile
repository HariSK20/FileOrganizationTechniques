CC = gcc

FLAGS = -o

DEBUG_FLAG = -g

all: single two_level hierarchical

single: single.c common.c
	@echo "Compiling files..."
	${CC} ${DEBUG_FLAG} single.c common.c ${FLAGS} single.out

two_level: two_level.c common.c
	@echo "Compiling files..."
	${CC} ${DEBUG_FLAG} two_level.c common.c ${FLAGS} two_level.out

hierarchical: hierarchical.c common.c
	@echo "Compiling files..."
	${CC} ${DEBUG_FLAG} hierarchical.c common.c ${FLAGS} hierarchical.out

# generate: Triangle.cpp Application.cpp
# 	@echo "Compiling files..."
# 	g++ Application.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o Application.out
# 	g++ Triangle.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o Triangle.out
clean:
	@echo "Cleaning up..."
	rm *.out