a.out: main.c matrix.o pivot.o gs_solver.o pivot_gs_solver.o 
	$(CC) $^ 
matrix.o: matrix.c matrix.h
pivot.o: pivot.c matrix.h
piv_gs_solver.o: pivot_gs_solver.c pivot_gs_solver.h matrix.h
gs_solver.o: gs_solver.c
.PHONY: clean

clean:
	-rm *.o a.out
