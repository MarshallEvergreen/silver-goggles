#include <gmock/gmock-matchers.h>
#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>

using namespace ::testing;

struct NoZeroElementsMatrix3x3Tests : public Test {

    Elements elements{
            {5.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}};

    Matrix matrix{elements};
};

TEST_F(NoZeroElementsMatrix3x3Tests, ostream_isFormattedNicely) {

    auto expectedOutput = "| 5 2 3 |\n| 4 5 6 |\n| 7 8 9 |\n";
    std::ostringstream out;
    out << matrix;
    EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(NoZeroElementsMatrix3x3Tests, IsSquare_ReturnsTrue_WhenMatrixIsSquareMatrix) {

    EXPECT_THAT(matrix.IsSquare(), Eq(true));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Determinant_CalculatesTheDetermiant_ForSquareMatrix) {

    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Determinant_CanBeCalledMultipleTimesCorrectly) {

    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Inverse_CanBeCalledMultipleTimesCorrectly) {

    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
}