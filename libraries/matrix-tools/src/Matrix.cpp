#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>
#include <utility>

Matrix::Matrix(Elements elements) {
    _elements = std::move(elements);
    _rows = _elements.size();
    _columns = _elements[0].size();
}

bool Matrix::IsSquare() {
    return _rows == _columns;
}

double Matrix::Determinant() {
    if (!IsSquare()) {
        throw DeterminantNonSquareMatrix{};
    }
    // Take a copy here to not mutate the elements for future use.
    auto elements = _elements;

    ReduceToUpperTriangular(elements);

    double determinant = 1.0;
    for (size_t i = 0; i < _rows; i++) {
        determinant = determinant * elements[i][i];
    }

    return determinant;
}
Matrix Matrix::Inverse() {
    if (!IsSquare()) {
        throw InverseNonSquareMatrix{};
    }

    if (Determinant() == 0.0) {
        throw InverseMatrixWithZeroDeterminant{};
    }

    return Matrix{{}};
}

void Matrix::ReduceToUpperTriangular(Elements &elements) const {

    for (size_t i = 0; i < _rows - 1; i++) {
        if (elements[i + 1][0] != 0.0) {
            const auto &factor = elements[i + 1][0] / elements[0][0];
            for (size_t j = 0; j < _columns; j++) {
                elements[i + 1][j] = elements[i + 1][j] - (factor * elements[0][j]);
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    {
        for (const auto &row : matrix._elements) {
            os << "| ";
            for (const auto &element : row) {
                os << element << " ";
            }
            os << "|\n";
        }
        return os;
    }
}