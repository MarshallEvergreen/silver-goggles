#include <gmock/gmock-matchers.h>
#include <matrix-tools/Matrix.h>
#include <matrix-tools/MatrixExceptions.h>

using namespace ::testing;
using namespace ::SilverGoogles::MatrixTools;

struct NoZeroElementsMatrix3x3Tests : public Test {

    Elements elements{
            {5.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}};

    Matrix matrix{elements};
};

TEST_F(NoZeroElementsMatrix3x3Tests, ostream_isFormattedNicely)
{
    auto expectedOutput = "| 5 2 3 |\n| 4 5 6 |\n| 7 8 9 |\n";
    std::ostringstream out;
    out << matrix;
    EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(NoZeroElementsMatrix3x3Tests, IsSquare_ReturnsTrue_WhenMatrixIsSquareMatrix)
{
    EXPECT_THAT(matrix.IsSquare(), Eq(true));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Determinant_CalculatesTheDetermiant_ForSquareMatrix)
{
    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Determinant_CanBeCalledMultipleTimesCorrectly)
{

    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
    EXPECT_THAT(matrix.Determinant(), DoubleNear(-12.0, 0.0001));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Inverse_CalculatesTheInverse_ForSquareMatrix)
{
    const auto& tol = 0.0001;
    auto inverseMatrix = matrix.Inverse();

    const auto& row1 = inverseMatrix[0];
    const auto& row2 = inverseMatrix[1];
    const auto& row3 = inverseMatrix[2];

    EXPECT_THAT(inverseMatrix[0],
                ElementsAre(
                        DoubleNear(0.25, tol),
                        DoubleNear(-0.5, tol),
                        DoubleNear(0.25, tol)));

    EXPECT_THAT(inverseMatrix[1],
                ElementsAre(
                        DoubleNear(-0.5, tol),
                        DoubleNear(-2, tol),
                        DoubleNear(1.5, tol)));

    EXPECT_THAT(inverseMatrix[2],
                ElementsAre(
                        DoubleNear(0.25, tol),
                        DoubleNear(2.16667, tol),
                        DoubleNear(-1.41667, tol)));
}

TEST_F(NoZeroElementsMatrix3x3Tests, Inverse_InvertingTheInverse_YieldsOriginalMatrix)
{

    const auto& tol = 0.0001;
    auto original = matrix.Inverse().Inverse();

    const auto& row1 = original[0];
    const auto& row2 = original[1];
    const auto& row3 = original[2];

    EXPECT_THAT(original[0],
                ElementsAre(
                        DoubleNear(5, tol),
                        DoubleNear(2, tol),
                        DoubleNear(3, tol)));

    EXPECT_THAT(original[1],
                ElementsAre(
                        DoubleNear(4, tol),
                        DoubleNear(5, tol),
                        DoubleNear(6, tol)));

    EXPECT_THAT(original[2],
                ElementsAre(
                        DoubleNear(7, tol),
                        DoubleNear(8, tol),
                        DoubleNear(9, tol)));
}