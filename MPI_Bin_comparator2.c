#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_NUM 1000 // запускать на 10 процессах

int *dec_to_bin( int );

int main(int argc, char **argv)
{
	int num1, num2, proc_num, proc_rank, comp_result, i;
	int buf1[10], buf2[10], buf_result[10]; 
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &proc_num );
	MPI_Comm_rank( MPI_COMM_WORLD, &proc_rank );

	if( 10 != proc_num ) // проверка на 10 процессов
	{
		if( 0 == proc_rank ) printf("Wrong number of processes!\n");
                MPI_Finalize();
		return 0;
        }

	
	if( 0 == proc_rank ) // считываем десятичные числа в 0 процессе, они известны только ему
	{
		scanf("%d%d", &num1, &num2 );

        	if( num1>1000 ) // ограничения 
                	num1 = MAX_NUM;

        	if( num2>1000 )
                	num2 = MAX_NUM;

		MPI_Send( &num1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD ); // сделать другой коммуникатор - разослать только им?
		MPI_Send( &num2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD ); // посылаем числа процессу 1 и 2
	}
	
	if( 1 == proc_rank ) // перевод в бинарный вид в этих процессах
	{
		MPI_Recv( &num1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );
		for( i=0;i<10;i++)
			buf1[i] = *( dec_to_bin( num1 ) + i );

		printf("The first number is: ");
		
		for( i=0;i<10;i++)
			printf("%d ", buf1[i]);
		
		printf("\n");
	}
	
	if( 2 == proc_rank)
	{
		MPI_Recv( &num2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );
		for(i=0;i<10;i++)
			buf2[i] = *( dec_to_bin( num2 ) + 1 );

		printf("The second number is: ");

		for(i=0;i<10;i++)
			printf("%d ", buf2[i] );
	
		printf("\n");
	}

	MPI_Bcast( buf1, 10, MPI_INT, 1, MPI_COMM_WORLD ); // теперь бинарный вид у всех
	MPI_Bcast( buf2, 10, MPI_INT, 2, MPI_COMM_WORLD );

	comp_result = ( buf1[proc_rank] == buf2[proc_rank] ) ? 0 : 1; 	// каждый процесс пар-но сравнивает разряд

	MPI_Barrier( MPI_COMM_WORLD );
	
	MPI_Gather( &comp_result, 1, MPI_INT, buf_result, 1, MPI_INT, 0, MPI_COMM_WORLD );	// рез-т сравнения на 0 процессе
	
	if ( 0 == proc_rank )
	{
		for(i=0;i<10;i++)
			printf("%d ", buf_result[i] ); 
		i = 0;
		int flag = 1;

		while( 0 == buf_result[i] ) // По порядку анализируем разряды чисел - равны или не равны
		{
			i++;
			
			if( 10 == i)
			{
				printf("Numbers are equal!\n");
				flag = 0;
			}
		} 
		
		if(flag)
		{
			if( buf1[i] > buf2[i] )
				printf("\nFirst number is bigger!\n");
			else printf("\nSecond number is bigger!\n");
		}
	}

	MPI_Finalize();
	return 0;
}

int* dec_to_bin( int num)
{
	int i = 0, buf[10];

        while( num != 1 )
        { 
        	buf[i] = num%2;
                num /= 2;
                i++;
        }

        buf[i] = 1;
        i++;

       	while( i <= 9)
        {
        	buf[i] = 0;
                i++;
        }

        for( i=0; i<10; i++ )
       		buf[i] = buf[9-i];

	return buf;
}	
