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

        void ReduceToUpperTriangular(Elements& elements) const;
        void ReduceToLowerTriangular(Elements& elements) const;
        void ReduceToIdentityMatrix(Elements& elements) const;

        [[nodiscard]] Elements CreateIdentityElements() const;
    };

}// namespace SilverGoogles::MatrixTools
