CC=gcc
CFLAGS=-Wall -std=c99 -lcsfml-graphics -lcsfml-window -lm -lssl -lcrypto -lcgraph -lgvc
CPPFLAGS =-O2
LDLIBS=


SRC = Ui.c Math_Tools/calculator/tinyexpr.c Algo_tools/graph/dfs/Gdfs.c Algo_tools/graph/bfs/Gbfs.c Algo_tools/tree/dfs/Tdfs.c Algo_tools/tree/bfs/Tbfs.c Algo_tools/tree/treeCheck/isTree/IsTree.c Algo_tools/queue/queue.c

OBJ = ${SRC:.c=.o}

release: main
	${CC} ${OBJ} ${CFLAGS} -o Vafa

main: ${OBJ}

debug: CPPFLAGS = -g -fsanitize=address
debug: LDLIBS = -lasan
debug: main
	${CC} ${CPPFLAGS} ${CFLAGS} ${OBJ} -o Vafa

clean:
	rm Vafa
	${RM} ${OBJ}
