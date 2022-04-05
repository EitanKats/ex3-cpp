//
// Created by Eitan Kats on 04/04/2022.
//
#include "Matrix.hpp"
#include "vector"
#include "doctest.h"

using namespace zich;


TEST_CASE ("Matrix construction tests") {
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};

            SUBCASE("Negative dimensions") {
                CHECK_THROWS(Matrix
                                     a(identity, 3, -3));
                CHECK_THROWS(Matrix
                                     a(identity, -3, 3));
    }
            SUBCASE("not matching dimensions") {
                CHECK_THROWS(Matrix
                                     a(identity, 3, 1));
                CHECK_THROWS(Matrix
                                     a(identity, 1, 3));
    }
            SUBCASE("Good matrix construction") {

                CHECK_NOTHROW(Matrix
                                      m1(identity, 3, 3));
                CHECK_NOTHROW(Matrix
                                      m2(identity, 9, 1));
                CHECK_NOTHROW(Matrix
                                      m3(identity, 1, 9));
    }

}

TEST_CASE ("comparison operators tests") {
    std::vector<double> mat1Vect = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    std::vector<double> mat2Vect = {1, 2, 3, 0, 3, 0, 0, 0, 3};
    std::vector<double> zeroMat = {0, 0, 0};
    std::vector<double> zeroSumMat = {-1, 0, 1};
    std::vector<double> largestSumMat = {14, 8, 1996, 27, 9, 1997, 0, 0, 3};
    Matrix m0{mat1Vect, 3, 3};
    Matrix m1{mat1Vect, 3, 3};
    Matrix m2{mat1Vect, 9, 1};
    Matrix m3{mat2Vect, 3, 3};
    Matrix m4{zeroMat, 3, 1};
    Matrix m5{zeroSumMat, 3, 1};
    Matrix largestSum{largestSumMat, 3, 3};
            SUBCASE("equality") {
                CHECK_THROWS(m1.operator==(m2));
                CHECK_FALSE(m1 == m3);
                CHECK(m4 == (-m4));
                CHECK(m0 == m1);
                CHECK_FALSE(m4 == m5);

    }
            SUBCASE("lte operator") {
                CHECK(m0 == m1);
                CHECK(m1 <= m3);
                CHECK_FALSE(m3 <= m1);
                CHECK_FALSE(m4 <= m5);
                CHECK_THROWS(m1.operator<=(m2));

    }
            SUBCASE("gte operator") {
                CHECK(m0 == m1);
                CHECK(m3 >= m1);
                CHECK_FALSE(m1 >= m3);
                CHECK_THROWS(m1.operator>=(m2));
    }
            SUBCASE("not eq") {
                CHECK_FALSE(m0 != m1);
                CHECK(m4 != m5);
                CHECK_THROWS(m1.operator!=(m2));

    }

            SUBCASE("lt operator") {
                CHECK_FALSE(m4.operator>(m5));
                CHECK(m1.operator<(largestSum));
                CHECK_THROWS(m1.operator<(m2));
    }

            SUBCASE("gt operator") {
                CHECK_FALSE(m4.operator>(m5));
                CHECK(largestSum.operator>(m1));
                CHECK_THROWS(m1.operator>(m2));

    }

}

TEST_CASE ("test multiplication operators") {
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> multipliedIdentity = {3, 0, 0, 0, 3, 0, 0, 0, 3};

    Matrix identityMat{identity, 3, 3};
    Matrix multipliedIdentityMat{multipliedIdentity, 3, 3};

            CHECK((3 * identityMat) == multipliedIdentityMat);
            CHECK((-3 * identityMat) == (-multipliedIdentityMat));
            identityMat *=3;
            CHECK(identityMat == multipliedIdentityMat);
}
