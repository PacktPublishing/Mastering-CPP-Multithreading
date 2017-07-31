EXECS=code1
MPICC?=mpicc

all: ${EXECS}

mpi_hello_world: code1.c
	${MPICC} -o code1 code1.c

clean:
	rm ${EXECS}
