#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

  int firstDimension = atoi(argv[1]);
  int secondDimension = atoi(argv[2]);

  double **myArray = malloc(firstDimension * sizeof(double*));
  
	for(int i = 0; i < firstDimension; i++){
		myArray[i] = malloc(secondDimension * sizeof(double));
	} 
  
  srand(18050111060);
  
  for (int i = 0; i < firstDimension; i++) {
        for (int j = 0; j < secondDimension; j++) {
            double random = randomDouble();
            myArray[i][j] = random;
        }
    }
    
    
	double randomVector[secondDimension];
	for (int i=0; i < secondDimension; i++) {
		randomVector[i] = rand() % 100 + 1;
	}
	
	
	multAndWriteToFile(myArray, randomVector, firstDimension, secondDimension,  argv[3]);
	free(myArray);
  return(0);
}
