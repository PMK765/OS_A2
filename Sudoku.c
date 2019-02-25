#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>


typedef struct {
	int row;
	int column;
} parameters;
/*
parameters *data = (parameters *) malloc(sizeof(parameters));
data->row = 1;
data->column = 1;

 Now create the thread passing it data as a parameter */

void printSudokuArray();
bool checkRowValidity(int rowIndex);
bool checkColumnValidity(int columnIndex);
bool check3x3SubmatrixValidity(int rowIndex, int columnIndex);
void swap(int*, int*);
int sudokuArray[9][9] = {{6,2,4,5,3,9,1,8,7}, //Global array that will be checked for validity
					    {5,1,9,7,2,8,6,3,4}, 
						{8,3,7,6,1,4,2,9,5}, 
						{1,4,3,8,6,5,7,2,9},
						{9,5,8,2,4,7,3,6,1},
						{7,6,2,3,9,1,4,5,8},
						{3,7,1,9,5,6,8,4,2},
						{4,9,6,1,8,2,5,7,3},
						{2,8,5,4,7,3,9,1,6},
						};

int main() {
	
	printSudokuArray();	
	
	int z;
	for(z = 0; z < 9; z++) {
		if(checkRowValidity(z)) {
			printf("Row %d is valid!\n",z);
		}
		else {
			printf("Row %d is invalid!\n",z);
		}
	}
	
	for(z = 0; z < 9; z++) {
		if(checkColumnValidity(z)) {
			printf("Column %d is valid!\n",z);
		}
		else {
			printf("Column %d is invalid!\n",z);
		}	
	}
	
	int rowIndex = 0, columnIndex = 0;
	int rowExtent = rowIndex + 9;
	int columnExtent = columnIndex + 9;
	for (rowIndex; rowIndex < rowExtent; rowIndex += 3) {
		for (columnIndex; columnIndex < columnExtent; columnIndex += 3) {
			if(check3x3SubmatrixValidity(rowIndex, columnIndex)) {
				printf("SubArray [%d][%d] is valid!\n", rowIndex, columnIndex);
			}
			else {
				printf("SubArray [%d][%d] is invalid!\n", rowIndex, columnIndex);
			}
		}
		columnIndex = 0;
	} 
	
	

	return 0;
}

bool checkRowValidity(int rowIndex) {
	int i, j, k, l;
	int unsortedArray[9];
	int checkArray[9] = {1,2,3,4,5,6,7,8,9};
	
	for (i = 0; i < 9; i++) { // Copy a row of the sudokuArray
		unsortedArray[i] = sudokuArray[rowIndex][i];
		//printf("%d  ",unsortedArray[i]);
	}
	for(j = 0; j < 8; j++) {
		for(k = 0; k < 8; k++) {
			if(unsortedArray[k] > unsortedArray[k+1]) {
				swap(&unsortedArray[k], &unsortedArray[k+1]);
			}
		} 
	} // The unsortedArray should now be sorted
	
	for(l = 0; l < 9; l++) {
		if(checkArray[l] != unsortedArray[l]) {
			return false;
		}
	}
	return true; // default
}

bool checkColumnValidity(int columnIndex) {
	int i, j, k, l;
	int unsortedArray[9];
	int checkArray[9] = {1,2,3,4,5,6,7,8,9};
	for (i = 0; i < 9; i++) { // Copy a row of the sudokuArray
		unsortedArray[i] = sudokuArray[i][columnIndex];
		//printf("%d  ",unsortedArray[i]);
	}
	for(j = 0; j < 8; j++) {
		for(k = 0; k < 8; k++) {
			if(unsortedArray[k] > unsortedArray[k+1]) {
				swap(&unsortedArray[k], &unsortedArray[k+1]);
			}
		}
	} // The unsortedArray should now be sorted
	
	for(l = 0; l < 9; l++) {
		if(checkArray[l] != unsortedArray[l]) {
			return false;
		}
	}
	return true; // default
}

bool check3x3SubmatrixValidity(int rowIndex, int columnIndex) {
	if ((rowIndex % 3 != 0) || (columnIndex % 3 != 0)) {
		printf("rowIndex and columnIndex must be multiples of 3!\n");
		return false;
	}
	if (rowIndex > 6 || columnIndex > 6) {
		printf("Out of bounds of the array!\n");
		return false;
	}
	int rowExtent, columnExtent, i, j, k;
	rowExtent = rowIndex + 3;
	columnExtent = columnIndex + 3;
	int columnIndexHolder = columnIndex;
	int unsortedArray[9];
	int checkArray[9] = {1,2,3,4,5,6,7,8,9};
	int counter = 0;
	for (rowIndex; rowIndex < rowExtent; rowIndex++) {
		for (columnIndex; columnIndex < columnExtent; columnIndex++) {
			unsortedArray[counter] = sudokuArray[rowIndex][columnIndex];
			counter++;
			//printf("%d  ",unsortedArray[i]);
		}
		columnIndex = columnIndexHolder;
	} 

	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(unsortedArray[j] > unsortedArray[j+1]) {
				swap(&unsortedArray[j], &unsortedArray[j+1]);
			}
		}
	} // The unsortedArray should now be sorted
	
	for(k = 0; k < 9; k++) {
		if(checkArray[k] != unsortedArray[k]) {
			return false;
		}
	}
	return true; // default
}

void swap(int *a, int *b) {
    int tmp  = *b;
    *b = *a;
    *a = tmp;
}

void printSudokuArray() {
	int i, j, outerSize, innerSize;
	outerSize = sizeof(sudokuArray) / sizeof(sudokuArray[0]);
	innerSize = outerSize; //IN THIS CASE
	for(i = 0; i < outerSize; i++) {
		for (j = 0; j < innerSize; j++) {
			printf("%d  ", sudokuArray[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



