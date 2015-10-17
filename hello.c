#include <stdio.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
	int proc_num;

	MPI_Init(&argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &proc_num);

	MPI_Finalize();

	printf("%d\n", proc_num);
	return 0;
}	
