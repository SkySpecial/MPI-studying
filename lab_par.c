#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv)
{
	double a[ISIZE][JSIZE], result[ISIZE][JSIZE];
	int i, j, k, i1, i2, proc_rank, proc_num;
	FILE *ff;
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &proc_num );
	MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );
	
	k = ISIZE/proc_num;
	i1 = k * proc_rank;
	i2 = k * (proc_rank + 1);
	if( proc_num - 1 == proc_rank ) i2 = ISIZE;

	for (i=i1; i<i2; i++)
	{
		for (j=0; j<JSIZE; j++)
		{
			a[i][j] = 10*i +j;
			a[i][j] = sin(0.00001*a[i][j]); 
		}
	}

	if( 0 != proc_rank)
	{
		MPI_Send( &i1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);// посылаем значение i1
		MPI_Send( &a[i1][0], (i2-i1)*JSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	if( 0 == proc_rank ) // запись в файл одним процессом
	{
		int counter = 1, buf_i1;
		while( proc_num  != counter)
		{
			MPI_Recv( &buf_i1, 1, MPI_INT, counter, 0, MPI_COMM_WORLD, &status);
			if( proc_num - 1 == counter)
			{
				MPI_Recv( &result[buf_i1][0], (ISIZE-buf_i1)*JSIZE, MPI_DOUBLE, counter, 0, MPI_COMM_WORLD, &status );
				counter++;
			}	
			else
			{ 
				MPI_Recv( &result[buf_i1][0], k*JSIZE, MPI_DOUBLE, counter, 0, MPI_COMM_WORLD, &status); 
				counter++;
			}
		}
		
		for( i=0; i<ISIZE; i++)
		{
			for( j=0; j< JSIZE; j++ )
			{
				ff = fopen("result.par.txt", "w");
                        	fprintf(ff, "%f ", result[i][j]);
                        	fclose(ff);
			}
			fprintf(ff, "\n");
		}
		
		fclose(ff);
	}

	MPI_Finalize();
	return 0;
}
