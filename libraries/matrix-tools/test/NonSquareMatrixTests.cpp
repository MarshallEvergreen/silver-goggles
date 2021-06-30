#include <gmock/gmock-matchers.h>
#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>

using namespace ::testing;
using namespace ::SilverGoogles::MatrixTools;

struct NonSquareMatrixTests : public Test {

    Elements elements{
            {1.0, 7.0},
            {8.0, 9.0},
            {6.0, 5.0}};

    Matrix matrix{elements};
};

TEST_F(NonSquareMatrixTests, Determinant_ThrowsException_ForNonSquareMatrix) {

    EXPECT_THROW(matrix.Determinant(), DeterminantNonSquareMatrix);
}

TEST_F(NonSquareMatrixTests, Inverse_ThrowsException_ForNonSquareMatrix) {

    EXPECT_THROW(matrix.Inverse(), InverseNonSquareMatrix);
}
