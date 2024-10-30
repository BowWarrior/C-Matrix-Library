#include <stdbool.h>

#ifndef MatrixLibraryAssignment_h
#define MatrixLibraryAssignment_h

typedef struct {
    int height;
    int width;
    int** coords;
} Matrix;

Matrix* ReadFile(const char* filename, bool rowMajor);

void printMatrices(Matrix* matrices, int number);

Matrix* AddMatrices(Matrix* matrices, bool rowMajor);

Matrix* SubtractMatrices(Matrix* matrices, bool rowMajor);

char* getColumn(Matrix* matrices, int number, int column);

char* getRow(Matrix* matrices, int number, int row);

int getElement(Matrix* matrices, int number, int row, int column);

Matrix* setElement(Matrix* matrices, int number, int row, int column, int input);

Matrix* setRow(Matrix* matrices, int number, int row);

void freeMatrices(Matrix* matrices);

Matrix* resizeMatrix(Matrix* matrices, int number, int width, int height, bool rowMajor);

Matrix* deepCopy(Matrix* matrices, int number, bool rowMajor);

bool checkEquivalent(Matrix* matrices, int number1, int number2);

void freeDeepCopy(Matrix* copy);

Matrix* multiplyMatrices(Matrix* matrices, int number1, int number2, bool rowMajor);

Matrix* rotateMatrix(Matrix* matrices, int number);

Matrix* subsetMatrix(Matrix* matrices, int number, int startrow, int startcolumn, int endrow, int endcolumn, bool rowMajor);

#endif
