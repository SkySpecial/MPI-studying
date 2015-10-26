#include <stdio.h>
#include <mpi.h>

#define MAX_TERMS 10000 

int main(int argc, char ** argv)
{
        int proc_rank, proc_num, num_of_iter, k, i, i1, i2;
        float local_result = 0.0, end_result = 0.0;
        double time1, time2;

        num_of_iter = ( (2==argc) && (atoi( argv[1] )<10000) ) ? atoi( argv[1] ) : MAX_TERMS;

        MPI_Init( &argc, &argv );   // начало
        MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );
        MPI_Comm_size( MPI_COMM_WORLD, &proc_num );

        if ( 0 == proc_rank )
                time1 = MPI_Wtime();

        k = num_of_iter / proc_num; // границы суммирования участков
        i1 = k * proc_rank;
        i2 = k * (proc_rank + 1);

        if ( proc_num - 1 == proc_rank ) // если поделилось не нацело - учитываем оставшийся хвост
                i2 = num_of_iter;

        for ( i = i1+1; i <= i2; i++ ) // суммируем с 1 до num_of_iter включительно!
                local_result += 1.0/i;

        MPI_Reduce( &local_result, &end_result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

        if ( 0 == proc_rank)
        {
                time2 = MPI_Wtime();

                printf( "Result: %f\n", end_result );
                printf( "Time: %f\n", time2-time1 );
                //printf( "%d\n", num_of_iter );
        }

        MPI_Finalize();
        return 0;
}
