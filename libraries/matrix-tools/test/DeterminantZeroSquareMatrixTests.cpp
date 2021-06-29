#include <gmock/gmock-matchers.h>
#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>

using namespace ::testing;

struct DeterminantZeroSquareMatrixTests : public Test {

    Elements elements{
            {2.0, 2.0},
            {2.0, 2.0}};

    Matrix matrix{elements};
};

TEST_F(DeterminantZeroSquareMatrixTests, Inverse_ThrowsException_ForSquareMatrixWithDeterminantOfZero) {

    EXPECT_THROW(matrix.Inverse(), InverseMatrixWithZeroDeterminant);
}