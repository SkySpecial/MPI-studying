#include <stdio.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
	int proc_rank, proc_num, buf;
	MPI_Status status;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );
	MPI_Comm_size( MPI_COMM_WORLD, &proc_num );

	if ( 0 != proc_rank )
	{
		MPI_Recv( &buf, 1, MPI_INT, proc_rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
		printf("Process №%d has received %d from process №%d\n", proc_rank, proc_rank - 1, proc_rank - 1);
	}
  
	if ( proc_rank < proc_num - 1 )
		MPI_Send( &buf, 1, MPI_INT, proc_rank + 1 , 0 , MPI_COMM_WORLD );
	
	if ( 0 == proc_rank )
	{
		MPI_Recv( &buf, 1, MPI_INT, proc_num - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("Process №%d has received %d from process №%d\n",/* proc_rank*/0, proc_num - 1, proc_num - 1);
	}
	 
	if ( proc_rank == proc_num - 1 )
		MPI_Send( &buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}
