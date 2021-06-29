#include <gmock/gmock-matchers.h>
#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>

using namespace ::testing;

struct NoZeroElementsMatrix2x2Tests : public Test {

    Elements elements{
            {1.0, 7.0},
            {8.0, 9.0}};

    Matrix matrix{elements};
};

TEST_F(NoZeroElementsMatrix2x2Tests, ostream_isFormattedNicely) {

    auto expectedOutput ="| 1 7 |\n| 8 9 |\n";
    std::ostringstream out;
    out << matrix;
    EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(NoZeroElementsMatrix2x2Tests, IsSquare_ReturnsTrue_WhenMatrixIsSquareMatrix) {

    EXPECT_THAT(matrix.IsSquare(), Eq(true));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Determinant_CalculatesTheDetermiant_ForSquareMatrix) {

    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Determinant_CanBeCalledMultipleTimesCorrectly) {

    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Inverse_CanBeCalledMultipleTimesCorrectly) {

    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
}