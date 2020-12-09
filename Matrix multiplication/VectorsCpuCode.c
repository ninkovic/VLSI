#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Maxfiles.h"
#include <MaxSLiCInterface.h>

int check(int vectorSize, uint32_t *outVector, uint32_t *expectedVector)
{
	int status = 0;
	for (int i = 0; i < vectorSize; i++) {
		if (outVector[i] != expectedVector[i]) {
			fprintf(stderr, "Error detected outVector[%d] != %d\n",
				outVector[i], expectedVector[i]);
			status = 1;
		}
	}
	return status;
}

int main()
{
	const int vectorSize = 16;
	const int streamSize = 2;
	size_t sizeBytes = vectorSize * streamSize * sizeof(uint32_t);
	uint32_t *inMatrix1 = malloc(sizeBytes);
	uint32_t *inMatrix2 = malloc(sizeBytes);
	uint32_t *outMatrix = malloc(sizeBytes);
	uint32_t *expectedMatrix = malloc(sizeBytes);

	for (int i = 0; i < vectorSize; i++) {
		inMatrix1[i] = i;
	}
	
	for (int i = 0; i < vectorSize; i++) {
		inMatrix2[i] = i;
	}
	
	for (int i = 0; i < vectorSize; i++) {
		expectedMatrix[i] = 0;
	}

    int size = (int)sqrt(vectorSize);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++){
		    int sum = 0;
		    for (int k = 0; k < size; k++){
		        sum += inMatrix1[i*size + k] * inMatrix2[k*size + j]; 
		    }
		    expectedMatrix[i*size + j] = sum;
		    printf("%d ", sum);
		}
		printf("\n");
	}

	printf("Running DFE.\n");
	Vectors(streamSize, inMatrix1, inMatrix2, outMatrix);
	
	for (int i = 0; i < vectorSize; i++) {
		printf("%u ", outMatrix[i]);
		if (i % size == (size-1) && i != 0){
		    printf("\n");
		}
	}

	int status = check(vectorSize, outMatrix, expectedMatrix);
	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");

	return status;
}
