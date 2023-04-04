#include <stdio.h>
#include <hellomake.h>
#include <time.h>
#include <stdlib.h>

double randomDouble()
{
	double lowerRange = 1.0;
	double upperRange = 101.0;
	return ((double)rand() * (upperRange - lowerRange)) / (double)RAND_MAX + lowerRange;
}

void multVectorMatrix(double **matrix, double vector[], int row, int column, double resultArray[])
{

	double sum = 0.0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			double mult = matrix[i][j] * vector[j];
			sum = sum + mult;
		}
		resultArray[i] = sum;
		sum = 0;
	}
}

void writeToFile(double resultArray[],char fileName[], int length)
{
	FILE *fp = fopen(fileName, "a");

	for (int i = 0; i < length; i++) {     
        fprintf(fp, "%lf \n", resultArray[i]);    
    }    
		
}
