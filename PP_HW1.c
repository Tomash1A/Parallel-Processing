#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int dart( void );
int dart( void )
{
// write a function that chooses x,y randomaly (uniform distribution)
// between [-1,1], and check x^2+y^2 ? 1
// if x^2+y^2<=1, return 1 (hit), else retuen 0 (miss)
double x, y;
srand((unsigned int)time(NULL));// needed to improve randomness of the code
x = -1 + ((float)rand()/ RAND_MAX)* 2;
y = -1 + ((float)rand()/ RAND_MAX)* 2;
val = x*x + y*y;
if val <=1
    return 1
else return 0
}

int main( int argc, char *argv[]){

    int n = 1; // number of processes used in the program. (1,2,4,6,8)
    int iteration_per_thread = 10000;// number of iterations per thread
    double estimated_pi; // buffer
    double PI25DT = 3.141592653589793238462643; //pi values, represented with 25 digits
    double my_hit_ratio;// my_hit_ratio- hit ratio per thread 
    int hit_per_thread; //hit_per_thread is the accumulator
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stderr,"Process %d on %s\n", myid, processor_name);

    sum = 0.0;
    for (i = myid + 1; i <= n; i += numprocs){
        hit_per_thread += dart();
        }
    
    my_hit_ratio = 4 * (hit_per_thread /(n * iteration_per_thread)) ;
    MPI_Reduce(&my_hit_ratio, &estimated_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


         printf("pi is approximately %.16f, Error is %.16f\n",
               pi, fabs(pi - PI25DT));
	endwtime = MPI_Wtime();
	printf("wall clock time = %f\n", endwtime-startwtime);	       
	}
    MPI_Finalize();

