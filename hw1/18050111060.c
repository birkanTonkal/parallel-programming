#include <hellomake.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	clock_t start_t, end_t;
	int comm_sz; // number of processes
	int my_rank; // process rank
	int firstDimension = atoi(argv[1]);
	int secondDimension = atoi(argv[2]);

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	int partial = firstDimension / (comm_sz - 1);
	double resultArray[partial];
	int resultLength = partial;

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	double **myArray = malloc(firstDimension * sizeof(double *));
	double randomVector[secondDimension];
	
	for (int i = 0; i < firstDimension; i++)
	{
		myArray[i] = malloc(secondDimension * sizeof(double));
	}
	srand(18050111060);
	if (my_rank == 0)
	{

		// FILL MATRIX WITH RANDOM DOUBLE NUMS
		for (int i = 0; i < firstDimension; i++)
		{
			for (int j = 0; j < secondDimension; j++)
			{
				double random = randomDouble();
				myArray[i][j] = random;
			}
		}

		// CREATE RANDOM VECTOR FOR MULTIPLICATION

		for (int i = 0; i < secondDimension; i++)
		{
			randomVector[i] = rand() % 100 + 1;
		}

		start_t = clock();
		for (int i = 1; i < comm_sz; i++)
		{
			MPI_Send(myArray, firstDimension * secondDimension, MPI_DOUBLE, i, 111, MPI_COMM_WORLD);
			MPI_Send(randomVector, secondDimension, MPI_DOUBLE, i, 112, MPI_COMM_WORLD);
			MPI_Recv(resultArray, resultLength, MPI_DOUBLE, i, 999, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			writeToFile(resultArray, argv[3], resultLength);
		}
		end_t = clock();
		printf(" Elapsed time is : %f", (double)(end_t - start_t) / CLOCKS_PER_SEC);
	}
	else
	{
		MPI_Recv(&myArray[0][0], firstDimension * secondDimension, MPI_DOUBLE, 0, 111, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		MPI_Recv(&randomVector[0], secondDimension, MPI_DOUBLE, 0, 112, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		double sum = 0.0;
		int iterationStart = (my_rank - 1) * partial;
		int iterationEnd = partial * my_rank;
		int count = 0;
		for (int i = iterationStart; i < iterationEnd; i++)
		{
			for (int j = 0; j < secondDimension; j++)
			{
				double mult = myArray[i][j] * randomVector[j];
				// printf("%lf", mult);
				sum = sum + mult;
			}

			resultArray[count] = sum;
			count++;
			sum = 0;
		}
		// printf("%lf", sum);
		MPI_Send(resultArray, resultLength, MPI_DOUBLE, 0, 999, MPI_COMM_WORLD);
	}

	/* multVectorMatrix(myArray, randomVector, firstDimension, secondDimension, resultArray);

	writeToFile(resultArray, argv[3], resultLength); */

	MPI_Finalize();
	free(myArray);
	return (0);
}
