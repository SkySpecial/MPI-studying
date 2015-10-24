#include <stdio.h>
#include <mpi.h>

int main(int argc, char ** argv)
{
	int proc_rank;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );
	double t1 = MPI_Wtime();

	int a = 6;

	double t2 = MPI_Wtime();
	if( 0 == proc_rank )
		printf("%.12f\n", t2 - t1); // почему результат = 0 ?
	//if( 0 == proc_rank ) 
	//	printf( "%.12f\n", MPI_Wtick() );
	
	MPI_Finalize();
	return 0;
}
