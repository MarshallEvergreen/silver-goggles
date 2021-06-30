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

        ReduceToUpperTriangular(elements);

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

        ReduceToUpperTriangular(elements);
        ReduceToLowerTriangular(elements);
        ReduceToIdentityMatrix(elements);

        auto inverseMatrix = Matrix{elements};
        return inverseMatrix;
    }

    void Matrix::ReduceToUpperTriangular(Elements& elements) const
    {
        for (size_t i = 0; i < _columns - 1; i++)
        {
            for (size_t j = i + 1; j < _rows; j++)
            {
                if (elements[j][i] != 0.0)
                {
                    const auto& factor = elements[j][i] / elements[i][i];
                    for (size_t k = 0; k < _columns; k++)
                    {
                        elements[j][k] = elements[j][k] - (factor * elements[i][k]);
                    }
                }
            }
        }
    }

    void Matrix::ReduceToLowerTriangular(Elements& elements) const
    {
        for (size_t i = _columns - 1; _columns > i; i--)
        {
            for (size_t j = i - 1; _rows > j; j--)
            {
                if (elements[j][i] != 0.0)
                {
                    const auto& factor = elements[j][i] / elements[i][i];
                    for (size_t k = 0; k < _columns; k++)
                    {
                        elements[j][k] = elements[j][k] - (factor * elements[i][k]);
                    }
                }
            }
        }
    }

    void Matrix::ReduceToIdentityMatrix(Elements& elements) const
    {
        for (size_t i = 0; i < _rows; i++)
        {
            const auto& factor = 1 / elements[i][i];
            for (size_t k = 0; k < _columns; k++)
            {
                elements[i][k] = (factor * elements[i][k]);
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