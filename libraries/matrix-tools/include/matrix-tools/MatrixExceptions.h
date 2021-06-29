#include <exception>

struct DeterminantNonSquareMatrix : std::exception {
    const char * what () const noexcept override;
};

struct InverseNonSquareMatrix : std::exception {
    const char * what () const noexcept override;
};

struct InverseMatrixWithZeroDeterminant : std::exception {
    const char * what () const noexcept override;
};
