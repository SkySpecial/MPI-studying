#include <stdio.h>
#include <mpi.h>

#define MAX_TERMS 10000 

int main(int argc, char ** argv)
{
        int proc_rank, proc_num, num_of_iter, k, i;
        float buf[MAX_TERMS], local_result = 0.0, end_result = 0.0 // можно ведь просто result = 0 ? Из-за MAX_TERMS завожу 
        // заведомо большее буферное пространство, есть ли способ не делать это? Динамический массив?

        MPI_Init( &argc, &argv );   // начало
        MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );
        MPI_Comm_size( MPI_COMM_WORLD, &proc_num );

        if( 0 == proc_rank )   // определяем количество членов ряда
        {
                printf("Enter the number of terms: ");
                scanf("%d", &num_of_iter );  // сделать это через командную строку? num_of_iter = argv[4]; 
                                                // А если через строку определить num_of_iter - то он сразу будет всем
                                                // известен? Именно поэтому так чаще делают?

                for( i = 1; i <= num_of_iter; i++ )
                        buf[i] = 1.0/i;
        }

        MPI_Bcast( buf, num_of_iter, MPI_FLOAT, 0, MPI_COMM_WORLD ); // можно ли передать каждому процессу только порцию членов
        // ряда, а не всё сразу? 
        // похоже , num_of_iter должен быть заранее определён, иначе ост процессы не узнают его?

        k = num_of_iter / proc_num; // границы суммирования участков
        i1 = k * proc_rank;
        i2 = k * (proc_rank + 1);

        if ( proc_num - 1 == proc_rank ) // если поделилось не нацело - учитываем оставшийся хвост
                i2 = num_of_iter;

        for ( i = i1; i < i2; i++ )
                local_result += buf[i];

        MPI_Reduce( &local_result, &end_result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

        if ( 0 == proc_rank)
                printf( "Result: %f\n", end_result );

        MPI_Finalize();
        return 0;
}
