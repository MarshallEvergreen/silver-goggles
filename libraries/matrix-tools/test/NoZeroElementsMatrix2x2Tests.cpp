#include <gmock/gmock-matchers.h>
#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>

using namespace ::testing;
using namespace ::SilverGoogles::MatrixTools;

struct NoZeroElementsMatrix2x2Tests : public Test {

    Elements elements{
            {1.0, 7.0},
            {8.0, 9.0}};

    Matrix matrix{elements};
};

TEST_F(NoZeroElementsMatrix2x2Tests, ostream_isFormattedNicely)
{
    auto expectedOutput = "| 1 7 |\n| 8 9 |\n";
    std::ostringstream out;
    out << matrix;
    EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(NoZeroElementsMatrix2x2Tests, IsSquare_ReturnsTrue_WhenMatrixIsSquareMatrix)
{
    EXPECT_THAT(matrix.IsSquare(), Eq(true));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Determinant_CalculatesTheDetermiant_ForSquareMatrix)
{
    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Determinant_CanBeCalledMultipleTimesCorrectly)
{
    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
    EXPECT_THAT(matrix.Determinant(), DoubleEq(-47.0));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Inverse_CalculatesTheInverse_ForSquareMatrix)
{
    const auto& tol = 0.0001;
    auto inverseMatrix = matrix.Inverse();

    const auto& row1 = inverseMatrix[0];
    const auto& row2 = inverseMatrix[1];

    EXPECT_THAT(inverseMatrix[0],
                ElementsAre(
                        DoubleNear(-0.1914893617, tol),
                        DoubleNear(0.14893617021, tol)));

    EXPECT_THAT(inverseMatrix[1],
                ElementsAre(
                        DoubleNear(0.17021276595, tol),
                        DoubleNear(-0.02127659574, tol)));
}

TEST_F(NoZeroElementsMatrix2x2Tests, Inverse_InvertingTheInverse_YieldsOriginalMatrix)
{
    const auto& tol = 0.0001;
    auto original = matrix.Inverse().Inverse();

    const auto& row1 = original[0];
    const auto& row2 = original[1];

    EXPECT_THAT(original[0],
                ElementsAre(
                        DoubleNear(1, tol),
                        DoubleNear(7, tol)));

    EXPECT_THAT(original[1],
                ElementsAre(
                        DoubleNear(8, tol),
                        DoubleNear(9, tol)));
}
