#include <ostream>
#include <vector>
using Elements = std::vector<std::vector<double>>;

class Matrix {
public:
    explicit Matrix(Elements elements);

    bool IsSquare() const;
    double Determinant();
    Matrix Inverse();

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);


private:
    size_t _rows;
    size_t _columns;
    Elements _elements;

    void ReduceToUpperTriangular(Elements &elements) const;
};
