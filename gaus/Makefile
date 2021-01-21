libge: matrix.o pivot.o gs_solver.o piv_gs_solver.o
	ar rvs libge.a $^ 

matrix.o: matrix.c matrix.h
pivot.o: pivot.c matrix.h
piv_gs_solver.o: piv_gs_solver.c matrix.h
gs_solver.o: gs_solver.h
.PHONY: clean

clean:
	-rm *.o libge.a
