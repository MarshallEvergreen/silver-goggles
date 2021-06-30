#include <optional>
#include <ostream>
#include <vector>

using Elements = std::vector<std::vector<double>>;
namespace SilverGoogles::MatrixTools {

    class Matrix {
    public:
        explicit Matrix(Elements elements);

        [[nodiscard]] bool IsSquare() const;
        double Determinant();
        Matrix Inverse();

        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
        const std::vector<double>& operator[](int i);

    private:
        size_t _rows;
        size_t _columns;
        Elements _elements;

        void ReduceRow(Elements& elements, size_t row, size_t column, double factor) const;

        void DeterminantReduceToUpperTriangular(Elements& elements) const;

        void InvertReduceToUpperTriangular(Elements& elements, Elements& adjointElements) const;
        void InvertReduceToLowerTriangular(Elements& elements, Elements& adjointElements) const;
        void InvertReduceToIdentityMatrix(Elements& elements, Elements& adjointElements) const;

        [[nodiscard]] Elements CreateIdentityElements() const;
    };

}// namespace SilverGoogles::MatrixTools
