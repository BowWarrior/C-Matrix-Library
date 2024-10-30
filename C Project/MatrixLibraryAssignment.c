#include <stdio.h>
#include <stdlib.h>
#include "MatrixLibraryAssignment.h"
#include <unistd.h>
#include <stdbool.h>
Matrix* ReadFile(const char* filename, bool rowMajor){
    FILE *fp = fopen(filename,"r");

    if(fp == NULL){
        printf("file doesn't exist");
        return NULL; //returns null if file doesn't exist
    }

    int M1width = 1, M1height = 0, M2width = 1, M2height = 0;
    int matrixValue = 0;
    bool WidthChecked1 = false;
    bool WidthChecked2 = false;
    int count = 0;
    char CharNow, CharPrev;
    char *charArray = NULL;
    int charArraySize = 0;

    //gets char values of my file and puts them into an array
    while((CharNow = fgetc(fp)) != EOF) {
        //allocates memory for character array
        charArray = realloc(charArray, (charArraySize + 1) * sizeof(char));
        if (charArray == NULL) {
            printf("Memory allocation failed\n");
            fclose(fp);
            return NULL;
        }
        charArray[charArraySize++] = CharNow;

        //switches the matrix from matrix1 to matrix2
        if(CharNow == 10 && CharPrev == 10){
            matrixValue = 1;
        }
        
        //this part puts reads the text file and determines the width and height of the matrices
        //the char values of:   ' ' = 32 and '\n' = 10
        if(CharNow == 32 && matrixValue == 0 && WidthChecked1 == false){
            M1width++;
        }else if(CharNow == 10 && matrixValue == 0){
            M1height++;
            WidthChecked1 = true;
        } 
        if(CharNow == 32 && matrixValue == 1 && WidthChecked2 == false){
            M2width++;
        } else if(CharNow == 10 && matrixValue == 1){
            M2height++;
            count++;
            if(count == 2){
                WidthChecked2 = true;
            }
        } 

        //stores the previous character
        CharPrev = CharNow;
    }
    //this is necessary because the M2height will add one for the 2nd line break when starting the 2nd matrix
    //M2height--;

    Matrix *matrices = (Matrix*)malloc(3 * sizeof(Matrix));

    if (matrices == NULL) {
        printf("Memory allocation failed\n");
        free(charArray);
        return NULL;
    }
    
    matrices[0].height = M1height;
    matrices[0].width = M1width;
    matrices[1].height = M2height;
    matrices[1].width = M2width;
    matrices[2].width = M2width;
    matrices[2].height = M2height;

//takes user's selection for it to be either column major or row major for storage of the matrices
//if rowMajor == true, it stores the matrices into rows first, then columns
    if(rowMajor = true){
        //this one is for row major
        matrices[0].coords = (int **)malloc(matrices[0].height * sizeof(int *));
        for (int i = 0; i < matrices[0].height; i++) {
            matrices[0].coords[i] = (int *)malloc(matrices[0].width * sizeof(int));
        }
        matrices[1].coords = (int **)malloc(matrices[1].height * sizeof(int *));
        for (int i = 0; i < matrices[1].height; i++) {
            matrices[1].coords[i] = (int *)malloc(matrices[1].width * sizeof(int));
        }
        matrices[2].coords = NULL;

        //populates our arrays
        count = 0;
        for(int i = 0; i < matrices[0].height; i++){
            for(int j = 0; j < matrices[0].width; j++){
            matrices[0].coords[i][j] = atoi(&charArray[count]);
            while (charArray[count] != ' ' && charArray[count] != '\n') {
                    count++; 
            }            
                count++;
            }
        }
        
        count++;
        for(int i = 0; i < matrices[1].height; i++){
            for(int j = 0; j < matrices[1].width; j++){
                matrices[1].coords[i][j] = atoi(&charArray[count]);
                while (charArray[count] != ' ' && charArray[count] != '\n') {
                    count++;
                }
                count++;
            }
        }
    } else{
        //this else makes it column major
        matrices[0].coords = (int **)malloc(matrices[0].width * sizeof(int *));
        for (int i = 0; i < matrices[0].width; i++) {
            matrices[0].coords[i] = (int *)malloc(matrices[0].height * sizeof(int));
        }
        matrices[1].coords = (int **)malloc(matrices[1].width * sizeof(int *));
        for (int i = 0; i < matrices[1].width; i++) {
            matrices[1].coords[i] = (int *)malloc(matrices[1].height * sizeof(int));
        }
        matrices[2].coords = NULL;

        //populates our arrays
        count = 0;
        for(int i = 0; i < matrices[0].width; i++){
            for(int j = 0; j < matrices[0].height; j++){
            matrices[0].coords[i][j] = atoi(&charArray[count]);
            while (charArray[count] != ' ' && charArray[count] != '\n') {
                    count++; 
            }            
                count++;
            }
        }
        
        count++;
        for(int i = 0; i < matrices[1].width; i++){
            for(int j = 0; j < matrices[1].height; j++){
                matrices[1].coords[i][j] = atoi(&charArray[count]);
                while (charArray[count] != ' ' && charArray[count] != '\n') {
                    count++;
                }
                count++;
            }
        }
    }


    fclose(fp);
    free(charArray);

    return matrices;
}

void printMatrices(Matrix* matrices, int number) {
    if (matrices[number].coords != NULL && matrices[number].width != 0 && matrices[number].height != 0) {
        printf("Matrix %d is equal to:\n", number+1);
        for (int i = 0; i < matrices[number].height; i++) {
            for (int j = 0; j < matrices[number].width; j++) {
                printf("%d ", matrices[number].coords[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("The result matrix is empty or incompatible!\n");
    }
} 


Matrix* AddMatrices(Matrix* matrices, bool rowMajor){
    //checks if they're the same size, then allocates memory for third matrix:
    if(matrices[0].width != matrices[1].width || matrices[0].height != matrices[1].height) {
        printf("Matrices are not the same dimensions. You can't add them\n");
        return matrices;
    }

    matrices[2].height = matrices[0].height;
    matrices[2].width = matrices[0].width;
    //allocates memory depending on row major vs column major depending on input
    if(rowMajor = true){
        matrices[2].coords = (int **)malloc(matrices[2].height * sizeof(int *));
        if (matrices[2].coords == NULL) {
            printf("Memory allocation failed\n");
            return matrices;
        }
        for (int i = 0; i < matrices[2].height; i++) {
            matrices[2].coords[i] = (int *)malloc(matrices[0].height * sizeof(int));
            if (matrices[2].coords[i] == NULL) {
                printf("Memory allocation failed\n");
                //frees the matrix if we failed ot initialize it
                for (int j = 0; j < i; j++) {
                    free(matrices[2].coords[j]);
                }
                free(matrices[2].coords);
                return matrices;
            }
        }
    } else{
        matrices[2].coords = (int **)malloc(matrices[2].width * sizeof(int *));
        if (matrices[2].coords == NULL) {
            printf("Memory allocation failed\n");
            return matrices;
        }
        for (int i = 0; i < matrices[2].width; i++) {
            matrices[2].coords[i] = (int *)malloc(matrices[0].width * sizeof(int));
            if (matrices[2].coords[i] == NULL) {
                printf("Memory allocation failed\n");
                //frees the matrix if we failed ot initialize it
                for (int j = 0; j < i; j++) {
                    free(matrices[2].coords[j]);
                }
                free(matrices[2].coords);
                return matrices;
            }
        }
    }
    
    //adds them:
    for(int i = 0; i < matrices[2].height; i++){
        for(int j = 0; j < matrices[2].width; j++){
            matrices[2].coords[i][j] = matrices[0].coords[i][j] + matrices[1].coords[i][j];
        }
    }
    printf("3rd Matrix when added is equal to:\n");
    printMatrices(matrices, 2);
    return matrices;
}

Matrix* SubtractMatrices(Matrix* matrices, bool rowMajor){
    //checks if they're the same size, then allocates memory for third matrix:
    if(matrices[0].width != matrices[1].width || matrices[0].height != matrices[1].height) {
        printf("Matrices are not the same dimensions. You can't subtract them.\n");
	return matrices;
    }
    matrices[2].height = matrices[0].height;
    matrices[2].width = matrices[0].width;
    //allocates memory depending on row major vs column major depending on input
    if(rowMajor = true){
        matrices[2].coords = (int **)malloc(matrices[2].height * sizeof(int *));
        if (matrices[2].coords == NULL) {
            printf("Memory allocation failed\n");
            return matrices;
        }

        for (int i = 0; i < matrices[2].height; i++) {
            matrices[2].coords[i] = (int *)malloc(matrices[0].height * sizeof(int));
            if (matrices[2].coords[i] == NULL) {
                printf("Memory allocation failed\n");
                //frees the matrix if we failed ot initialize it:
                for (int j = 0; j < i; j++) {
                    free(matrices[2].coords[j]);
                }
                free(matrices[2].coords);
                return matrices;
            }
        }
    } else{
        matrices[2].coords = (int **)malloc(matrices[2].width * sizeof(int *));
        if (matrices[2].coords == NULL) {
            printf("Memory allocation failed\n");
            return matrices;
        }

        for (int i = 0; i < matrices[2].width; i++) {
            matrices[2].coords[i] = (int *)malloc(matrices[0].width * sizeof(int));
            if (matrices[2].coords[i] == NULL) {
                printf("Memory allocation failed\n");
                //frees the matrix if we failed ot initialize it:
                for (int j = 0; j < i; j++) {
                    free(matrices[2].coords[j]);
                }
                free(matrices[2].coords);
                return matrices;
            }
        }
    }
    //adds them:
    for(int i = 0; i < matrices[2].height; i++){
        for(int j = 0; j < matrices[2].width; j++){
            matrices[2].coords[i][j] = matrices[0].coords[i][j] - matrices[1].coords[i][j];
        }
    }
    printf("3rd Matrix when subtracted is equal to:\n");
    printMatrices(matrices, 2);
    return matrices;
}


char* getColumn(Matrix* matrices, int number, int column) {
    if (column < 0 || column >= matrices[number].width) {
        printf("Invalid column index\n");
        return NULL;
    }

    char* columnValues = (char *)malloc(matrices[number].height * sizeof(char));
    if (columnValues == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    //prints out values in the matrix of choice:
    printf("Column %d values of matrix %d:\n", column+1, number+1);
    for (int i = 0; i < matrices[number].height; i++) {
        columnValues[i] = matrices[number].coords[i][column];
        printf("%d\n", (columnValues[i]));
    }
    return columnValues;
}



char* getRow(Matrix* matrices, int number, int row) {
    if (row < 0 || row >= matrices[number].width) {
        printf("Invalid row index\n");
        return NULL;
    }

    char* rowValues = (char *)malloc(matrices[number].height * sizeof(char));
    if (rowValues == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    //prints out values in the matrix of choice:
    printf("Row %d values of matrix %d:\n", row+1, number+1);
    for (int i = 0; i < matrices[number].height; i++) {
        rowValues[i] = matrices[number].coords[row][i];
        printf("%d\n", (rowValues[i]));
    }

    return rowValues;
}

int getElement(Matrix* matrices, int number, int row, int column){
    if (row >= 0 && row < matrices[number].height && column >= 0 && column < matrices[number].width) {
        int element = matrices[number].coords[row][column];
        //printf("Element value at matrix %d, row %d, column %d is equal to %d\n", number + 1, row+1, column+1, element);
        return element;
    } else {
        printf("Invalid matrix index\n");
        return 0;
    }
}


Matrix* setElement(Matrix* matrices, int number, int row, int column, int input) {
    if (row >= 0 && row < matrices[number].height && column >= 0 && column < matrices[number].width) {
        matrices[number].coords[row][column] = input;
        printf("Your matrix %d at row: %d, and column: %d, was changed to %d\n", number+1, row+1, column+1, input);
        printMatrices(matrices, number);
        return matrices;
    } else {
        printf("Invalid matrix index\n");
        return NULL;
    }
}

Matrix* setRow(Matrix* matrices, int number, int row){
    if (row < 0 || row >= matrices[number].width) {
        printf("Invalid row index\n");
        return NULL;
    }
    
    //prints out values in the matrix of choice:
    printf("Row %d values of matrix %d:\n", row+1, number+1);
    int input = 0;
    for (int i = 0; i < matrices[number].height; i++) {
        printf("What value would you like at matrix: %d, row: %d, index: %d\n", number+1, row+1, i);
        scanf("%d", &input);
        matrices[number].coords[row][i] = input;
    }
    printMatrices(matrices, number);

    return matrices;
}





Matrix* resizeMatrix(Matrix* matrices, int number, int width, int height, bool rowMajor){
    Matrix* resizedMatrix = (Matrix*)malloc(sizeof(Matrix));
    if (resizedMatrix == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    
    //sets new width and height from parameters
    resizedMatrix->height = height;
    resizedMatrix->width = width;
    //allocates memory depending on row major vs column major depending on input
    if(rowMajor = true){
        resizedMatrix->coords = (int **)malloc(height * sizeof(int *));
        if (resizedMatrix->coords == NULL) {
            printf("Memory allocation failed\n");
            free(resizedMatrix);
            return NULL;
        }
        for (int i = 0; i < height; i++) {
            resizedMatrix->coords[i] = (int *)malloc(width * sizeof(int));
            if (resizedMatrix->coords[i] == NULL) {
                printf("Memory allocation failed\n");
                for (int j = 0; j < i; j++) {
                    free(resizedMatrix->coords[j]);
                }
                free(resizedMatrix->coords);
                free(resizedMatrix);
                return NULL;
            }
        }
    } else{
        resizedMatrix->coords = (int **)malloc(width * sizeof(int *));
        if (resizedMatrix->coords == NULL) {
            printf("Memory allocation failed\n");
            free(resizedMatrix);
            return NULL;
        }
        for (int i = 0; i < width; i++) {
            resizedMatrix->coords[i] = (int *)malloc(height * sizeof(int));
            if (resizedMatrix->coords[i] == NULL) {
                printf("Memory allocation failed\n");
                for (int j = 0; j < i; j++) {
                    free(resizedMatrix->coords[j]);
                }
                free(resizedMatrix->coords);
                free(resizedMatrix);
                return NULL;
            }
        }
    }
    //sets the values from the old matrix into the new matrix
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < matrices[number].height && j < matrices[number].width) {
                resizedMatrix->coords[i][j] = matrices[number].coords[i][j];
            } else {
                //fills new elements with 0
                resizedMatrix->coords[i][j] = 0;
            }
        }
    }

    printf("Your resized matrix %d is equal to:\n", number+1);
    for (int i = 0; i < resizedMatrix->height; i++) {
        for (int j = 0; j < resizedMatrix->width; j++) {
            printf("%d ", resizedMatrix->coords[i][j]);
        }
        printf("\n");
    }
    
    return resizedMatrix;
}


Matrix* deepCopy(Matrix* matrices, int number, bool rowMajor) {
    if (matrices == NULL || number < 0) return NULL;

    Matrix* copy = (Matrix*)malloc(sizeof(Matrix));
    if (copy == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    copy->height = matrices[number].height;
    copy->width = matrices[number].width;
    //allocates memory depending on row major vs column major depending on input
    if(rowMajor = true){
        copy->coords = (int**)malloc(copy->height * sizeof(int*));
        if (copy->coords == NULL) {
            free(copy);
            printf("Memory allocation failed for coordinates\n");
            return NULL;
        }

        for (int i = 0; i < copy->height; i++) {
            copy->coords[i] = (int*)malloc(copy->width * sizeof(int));
            if (copy->coords[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(copy->coords[j]);
                }
                free(copy->coords);
                free(copy);
                printf("Memory allocation failed for row %d\n", i);
                return NULL;
            }
            //copies the data
            for (int j = 0; j < copy->width; j++) {
                copy->coords[i][j] = matrices[number].coords[i][j];
            }
        }
    } else{
        copy->coords = (int**)malloc(copy->width * sizeof(int*));
        if (copy->coords == NULL) {
            free(copy);
            printf("Memory allocation failed for coordinates\n");
            return NULL;
        }

        for (int i = 0; i < copy->width; i++) {
            copy->coords[i] = (int*)malloc(copy->height * sizeof(int));
            if (copy->coords[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(copy->coords[j]);
                }
                free(copy->coords);
                free(copy);
                printf("Memory allocation failed for row %d\n", i);
                return NULL;
            }
            //copies the data
            for (int j = 0; j < copy->width; j++) {
                copy->coords[i][j] = matrices[number].coords[i][j];
            }
        }
    }
    
    for (int i = 0; i < copy->height; i++) {
        for (int j = 0; j < copy->width; j++) {
            printf("%d ", copy->coords[i][j]);
        }
        printf("\n");
    }
    return copy;
}



void freeDeepCopy(Matrix* copy){
    if (copy[0].coords != NULL) {
        for (int i = 0; i < copy[0].height; i++) {
            free(copy[0].coords[i]);
        }
        free(copy[0].coords);
    }
    free(copy);
}

bool checkEquivalent(Matrix* matrices, int number1, int number2){
    //this starts a count and checks the matrices' height and width are equal, then adds one to count for each time
    //the two matrices have a value in common, then it checks if the count is equal to width * height, essentially 
    //checking if the entire matrices are equal
    if (matrices == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int count = 0;
    int area = matrices[number1].height * matrices[number1].width;
    if(matrices[number1].height == matrices[number2].height && matrices[number1].width == matrices[number2].width){
        for(int i = 0; i < matrices[number1].height; i++){
            for(int j = 0; j < matrices[number1].width; j++){
                if(matrices[number1].coords[i][j] == matrices[number2].coords[i][j]){
                    count++;
                } else{
                    return false;
                }
            }
        }
        if(area == count){
            return true;
        }
    } else{
        return false;
    }
    return false;
}

void printMatrix(Matrix* matrix) {
    if (matrix == NULL) {
        printf("No matrix to display.\n");
        return;
    }
    printf("Resulting Matrix:\n");
    for (int i = 0; i < matrix->height; i++) {
        for (int j = 0; j < matrix->width; j++) {
            printf("%d ", matrix->coords[i][j]);
        }
        printf("\n");
    }
}

Matrix* multiplyMatrices(Matrix* matrices, int number1, int number2, bool rowMajor) {
    if (matrices[number1].width != matrices[number2].height) {
        printf("The dimensions aren't right to multiply!\n");
        return NULL;
    }

    Matrix* result = (Matrix*)malloc(sizeof(Matrix));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    result->height = matrices[number1].height;
    result->width = matrices[number2].width;
    //allocates memory depending on row major vs column major depending on input
    if(rowMajor = true){
        result->coords = (int**)malloc(result->height * sizeof(int*));
        if (result->coords == NULL) {
            printf("Memory allocation for matrix data failed\n");
            free(result);
            return NULL;
        }

        for (int i = 0; i < result->height; i++) {
            result->coords[i] = (int*)malloc(result->width * sizeof(int));
        }
    } else{
        result->coords = (int**)malloc(result->width * sizeof(int*));
        if (result->coords == NULL) {
            printf("Memory allocation for matrix data failed\n");
            free(result);
            return NULL;
        }

        for (int i = 0; i < result->width; i++) {
            result->coords[i] = (int*)malloc(result->height * sizeof(int));
        }
    }
    for (int i = 0; i < result->height; i++) {
        if (result->coords[i] == NULL) {
            printf("Memory allocation for row data failed\n");
            for (int j = 0; j < i; j++) {
                free(result->coords[j]);
            }
            free(result->coords);
            free(result);
            return NULL;
        }

        for (int j = 0; j < result->width; j++) {
            result->coords[i][j] = 0;
            //iterates though the width of first the multiplied matrix and adds the 
            for (int k = 0; k < matrices[number1].width; k++) {
                result->coords[i][j] += matrices[number1].coords[i][k] * matrices[number2].coords[k][j];
            }
        }
    }
    //printMatrices(result, 0);
    return result;
}


Matrix* rotateMatrix(Matrix* matrices, int number){
    if(matrices[number].width != matrices[number].height){
        printf("your matrix has to be the same tall as wide\n");
        return NULL;
    }
    int size = matrices[number].height;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int temp = matrices[number].coords[i][j];
            matrices[number].coords[i][j] = matrices[number].coords[j][i];
            matrices[number].coords[j][i] = temp;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            int temp = matrices[number].coords[i][j];
            matrices[number].coords[i][j] = matrices[number].coords[i][size - 1 - j];
            matrices[number].coords[i][size - 1 - j] = temp;
        }
    }
    return matrices;
}

Matrix* subsetMatrix(Matrix* matrices, int number, int startrow, int startcolumn, int endrow, int endcolumn, bool rowMajor){
    //checks for out of bounds issues
    if(startrow < 0 || startcolumn < 0 || endrow >= matrices[number].height || endcolumn >= matrices[number].width || startrow > endrow || startcolumn > endcolumn) {
        printf("Invalid subset range\n");
        return NULL;
    }
    //calculates dimensions of the subset
    int subsetHeight = endrow - startrow + 1;
    int subsetWidth = endcolumn - startcolumn + 1;

    Matrix* subset = (Matrix*)malloc(sizeof(Matrix));
    if (subset == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    subset->height = subsetHeight;
    subset->width = subsetWidth;
    //allocates memory depending on row major vs column major depending on input
    if(rowMajor = true){
        subset->coords = (int**)malloc(subsetHeight * sizeof(int*));
        if (subset->coords == NULL) {
            printf("Memory allocation for matrix data failed\n");
            free(subset);
            return NULL;
        }
        for (int i = startrow; i <= endrow; i++) {
            subset->coords[i - startrow] = (int*)malloc(subsetWidth * sizeof(int));
        }
    } else{
        subset->coords = (int**)malloc(subsetWidth * sizeof(int*));
        if (subset->coords == NULL) {
            printf("Memory allocation for matrix data failed\n");
            free(subset);
            return NULL;
        }
        for (int i = startrow; i <= endrow; i++) {
            subset->coords[i - startrow] = (int*)malloc(subsetHeight * sizeof(int));
        }
    }

    //copies values from the original matrix
    for (int i = startrow; i <= endrow; i++) {
        subset->coords[i - startrow] = (int*)malloc(subsetWidth * sizeof(int));
        if (subset->coords[i - startrow] == NULL) {
            printf("Memory allocation for row data failed\n");
            for (int j = 0; j < i - startrow; j++) {
                free(subset->coords[j]);
            }
            free(subset->coords);
            free(subset);
            return NULL;
        }

        for (int j = startcolumn; j <= endcolumn; j++){
            subset->coords[i - startrow][j - startcolumn] = matrices[number].coords[i][j];
        }
    }
    return subset;
}


//how to get the memory address of any element in my matrices: 
//printf("Memory location of a point in matrices[0]: %p\n", (void *)&matrices[0].coords[3][2]);
//(I just wanted to keep this in case i have to come back to this project int the future)




void freeMatrices(Matrix* matrices) { 
    if (matrices != NULL) {
        if (matrices[0].coords != NULL) {
            for (int i = 0; i < matrices[0].height; i++) {
                free(matrices[0].coords[i]);
            }
            free(matrices[0].coords);
        }
        if (matrices[1].coords != NULL) {
            for (int i = 0; i < matrices[1].height; i++) {
                free(matrices[1].coords[i]);
            }
            free(matrices[1].coords);
        }
        if (matrices[2].coords != NULL) {
            for (int i = 0; i < matrices[2].height; i++) {
                free(matrices[2].coords[i]);
            }
            free(matrices[2].coords);
        }
        free(matrices);
    }
}


/*
int main(){

    	Matrix* matrices = ReadFile();

     //prints the matrices if they exist
     if (matrices != NULL) {
        printMatrices(matrices, 0);
        printMatrices(matrices, 1);

        //Prints (and returns) my added/subtracted matrix:
        AddMatrices(matrices);
	    SubtractMatrices(matrices);
    

        //gets first column of a matrix (the 2nd number is which matrix you would like, and the third is the column):
        char* columnValues = getColumn(matrices, 1, 2); 
        if (columnValues != NULL) {
            free(columnValues);
        }

        char* rowValues = getRow(matrices, 1, 2); 
        if (rowValues != NULL) {
            free(rowValues);
        }

        int elementValue = getElement(matrices, 1, 3, 3);
        printf("Element value: %d\n", elementValue);

        //this will allow you to set a value of one of my given matrices at a given column and row
        //Matrix* setValue = setElement(matrices, 2, 2, 1, 99);
        setElement(matrices, 2, 2, 1, 99);

        //this will iterate through a row of the specified matrix and row, setting values that the user would like to input
        //Matrix* setRowValue = setRow(matrices, 0, 0);
        setRow(matrices, 0, 0);

        

        //frees my matrices:
	freeMatrices(matrices);
    } else {
        printf("Error reading file!\n");
    }

    
        
    

    return 0;
}



*/