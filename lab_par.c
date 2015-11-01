#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv)
{
        double a[ISIZE][JSIZE];
        int i, j, k, i1, i2, proc_rank, proc_num;
        FILE *ff;

        MPI_Init( &argc, &argv );
        MPI_Comm_size( MPI_COMM_WORLD, &proc_num );
        MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );

        k = ISIZE/proc_num;
        i1 = k * proc_rank;
        i2 = k * (proc_rank + 1);
        if( proc_num == proc_rank - 1 ) i2 = ISIZE;
        
        for (i=i1; i<i2; i++)
        {
                for (j=0; j<JSIZE; j++)
                {
                        a[i][j] = 10*i +j;
                        a[i][j] = sin(0.00001*a[i][j]);
                        ff = fopen("result.par.txt", "w");
                        fprintf(ff, "%f ", a[i][j]);
                        fclose(ff);
                }
        }
        
        MPI_Finalize();
        return 0;
}
        
