#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>
#include <utility>

namespace SilverGoogles::MatrixTools {

    Matrix::Matrix(Elements elements)
    {
        _elements = std::move(elements);
        _rows = _elements.size();
        _columns = _elements[0].size();
    }

    bool Matrix::IsSquare() const
    {
        return _rows == _columns;
    }

    double Matrix::Determinant()
    {
        if (!IsSquare())
        {
            throw DeterminantNonSquareMatrix{};
        }

        // Take a copy here to not mutate the elements for future use.
        auto elements = _elements;

        DeterminantReduceToUpperTriangular(elements);

        double determinant = 1.0;
        for (size_t i = 0; i < _rows; i++)
        {
            determinant = determinant * elements[i][i];
        }

        return determinant;
    }
    Matrix Matrix::Inverse()
    {
        if (!IsSquare())
        {
            throw InverseNonSquareMatrix{};
        }

        if (Determinant() == 0.0)
        {
            throw InverseMatrixWithZeroDeterminant{};
        }

        // Take a copy here to not mutate the elements for future use.
        auto elements = _elements;
        auto identity = CreateIdentityElements();

        InvertReduceToUpperTriangular(elements, identity);
        InvertReduceToLowerTriangular(elements, identity);
        InvertReduceToIdentityMatrix(elements, identity);

        auto inverseMatrix = Matrix{identity};
        return inverseMatrix;
    }

    void Matrix::ReduceRow(Elements& elements, size_t row, size_t column, double factor) const
    {
        for (size_t k = 0; k < _columns; k++)
        {
            elements[row][k] = elements[row][k] - (factor * elements[column][k]);
        }
    }

    void Matrix::DeterminantReduceToUpperTriangular(Elements& elements) const
    {
        for (size_t column = 0; column < _columns - 1; column++)
        {
            for (size_t row = column + 1; row < _rows; row++)
            {
                if (elements[row][column] != 0.0)
                {
                    const auto& factor = elements[row][column] / elements[column][column];
                    ReduceRow(elements, row, column, factor);
                }
            }
        }
    }

    void Matrix::InvertReduceToUpperTriangular(Elements& elements, Elements& adjointElements) const
    {
        for (size_t column = 0; column < _columns - 1; column++)
        {
            for (size_t row = column + 1; row < _rows; row++)
            {
                if (elements[row][column] != 0.0)
                {
                    const auto& factor = elements[row][column] / elements[column][column];
                    ReduceRow(elements, row, column, factor);
                    ReduceRow(adjointElements, row, column, factor);
                }
            }
        }
    }

    void Matrix::InvertReduceToLowerTriangular(Elements& elements, Elements& adjointElements) const
    {
        for (size_t column = _columns - 1; _columns > column; column--)
        {
            for (size_t row = column - 1; _rows > row; row--)
            {
                const auto& factor = elements[row][column] / elements[column][column];
                ReduceRow(elements, row, column, factor);
                ReduceRow(adjointElements, row, column, factor);
            }
        }
    }

    void Matrix::InvertReduceToIdentityMatrix(Elements& elements, Elements& adjointElements) const
    {
        for (size_t i = 0; i < _rows; i++)
        {
            const auto& factor = 1 / elements[i][i];
            for (size_t k = 0; k < _columns; k++)
            {
                elements[i][k] = (factor * elements[i][k]);
                adjointElements[i][k] = (factor * adjointElements[i][k]);
            }
        }
    }

    Elements Matrix::CreateIdentityElements() const
    {
        Elements identity;
        for (size_t i = 0; i < _rows; i++)
        {
            identity.push_back({});
            for (size_t k = 0; k < _columns; k++)
            {
                if (i == k)
                {
                    identity[i].push_back(1.0);
                }
                else
                {
                    identity[i].push_back(0.0);
                }
            }
        }
        return identity;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
    {
        for (const auto& row : matrix._elements)
        {
            os << "| ";
            for (const auto& element : row)
            {
                os << element << " ";
            }
            os << "|\n";
        }
        return os;
    }

    const std::vector<double>& Matrix::operator[](int i)
    {
        return _elements[i];
    }

}// namespace SilverGoogles::MatrixTools