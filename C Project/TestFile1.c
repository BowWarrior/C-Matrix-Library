#include <stdio.h>
#include <stdlib.h>
#include "MatrixLibraryAssignment.h"

int main() {
    const char* filename = "MatrixLibraryAssignment.txt"; // Change this to your input file

    Matrix* matrices = ReadFile(filename, false);

    if (matrices != NULL) {
        
        printMatrices(matrices, 0);
        printMatrices(matrices, 1);

        
        printf("Adding matrices:\n");
        AddMatrices(matrices, true);

        
        printf("Subtracting matrices:\n");
        SubtractMatrices(matrices, true);

        
        printf("Getting column and row:\n");
        char* columnValues = getColumn(matrices, 1, 2); 
        if (columnValues != NULL) {
            free(columnValues);
        }

        char* rowValues = getRow(matrices, 1, 2); 
        if (rowValues != NULL) {
            free(rowValues);
        }


        printf("Getting element:\n");
        int elementValue = getElement(matrices, 1, 3, 3);
        printf("Element value: %d\n", elementValue);


        printf("\nSetting element:\n");
        setElement(matrices, 2, 2, 1, 99);

        printf("\nSetting row:\n");
        setRow(matrices, 0, 0);
        
        
        printf("\nResizing matrix:\n");
        Matrix* resizedMatrix = resizeMatrix(matrices, 0, 2, 6, true);
        
        printf("\nDeep Copy:\n");
        Matrix* copy = deepCopy(matrices, 0, true);
        freeDeepCopy(copy);

        printf("\n");
        if(checkEquivalent(matrices, 1, 1)){
            printf("checkEquivalent(matrices, %d, %d) returned true\n\n", 1, 1);
        } else{
            printf("checkEquivalent(matrices, %d, %d) returned false\n\n", 1, 1);
        }
        
        Matrix* multiplied = multiplyMatrices(matrices, 0, 1, false);
        printMatrices(multiplied, 0);

        rotateMatrix(matrices, 0);
        printMatrices(matrices, 0);

        Matrix* subset = subsetMatrix(matrices, 0, 1, 1, 3, 3, false);
        printMatrices(subset, 0);

        freeMatrices(matrices);
    } else {
        printf("Error reading file!\n");
    }


    return 0;
}