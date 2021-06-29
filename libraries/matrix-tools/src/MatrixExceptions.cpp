#include "matrix-tools/MatrixExceptions.h"

const char *DeterminantNonSquareMatrix::what() const noexcept {
    return "Can not compute the determinant of a non square matrix";
}
const char *InverseNonSquareMatrix::what() const noexcept {
    return "Can not compute the inverse of a non square matrix";
}
const char *InverseMatrixWithZeroDeterminant::what() const noexcept {
    return "Can not compute the inverse of a square matrix with a determinant of 0";
}
