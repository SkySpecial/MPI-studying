#include <stdio.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
	int proc_num;
	int proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank);
	
        if( 0 == proc_rank)
       		 printf("%d\n", proc_num);

	MPI_Finalize();

	//if( 0 == proc_rank)
	//	printf("%d\n", proc_num);

	return 0;
}	
