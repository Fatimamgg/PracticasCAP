EXECS=pingpong
MPICC=mpicc

all:
	${MPICC} -o ${EXECS} pingpong.c

run:
	mpirun -np 2 ./${EXECS} 40000

clean:
	rm -f ${EXECS}
