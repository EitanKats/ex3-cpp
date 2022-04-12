//
// Created by Eitan Kats on 04/04/2022.
//
#include "sources/Matrix.hpp"
#include "vector"
#include "doctest.h"
#include <sstream>
#include "iostream"
#include "string"

using namespace zich;
std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
std::vector<double> multipliedIdentity = {3, 0, 0, 0, 3, 0, 0, 0, 3};

TEST_CASE ("Matrix construction tests") {


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

TEST_CASE ("test scalar multiplication operators") {


    Matrix identityMat{identity, 3, 3};
    Matrix multipliedIdentityMat{multipliedIdentity, 3, 3};

            CHECK((3 * identityMat) == multipliedIdentityMat);
            CHECK((-3 * identityMat) == (-multipliedIdentityMat));
    identityMat *= 3;
            CHECK(identityMat == multipliedIdentityMat);
}

TEST_CASE ("test matrix basic arithmetic operators (plus minus)") {
    Matrix identityMatSquare{identity, 3, 3};
    Matrix identityMatFlat{identity, 1, 9};

            SUBCASE("plus tests") {
        Matrix identityMatSquareChanges{identity, 3, 3};
                CHECK_THROWS(identityMatSquare.operator+(identityMatFlat));
                CHECK((identityMatSquare + identityMatSquare) == 2 * identityMatSquare);
                CHECK((identityMatSquareChanges += identityMatSquare) == 2 * identityMatSquare);

    }
            SUBCASE("minus tests") {
        Matrix identityMatSquareThree{multipliedIdentity, 3, 3};

                CHECK_THROWS(identityMatSquare.operator-(identityMatFlat));
                CHECK((2 * identityMatSquare) - identityMatSquare == identityMatSquare);
                CHECK((identityMatSquareThree -= identityMatSquare) == 2 * identityMatSquare);
    }
}

TEST_CASE ("stream tests") {
    Matrix identityMatSquare{identity, 3, 3};
    std::string indentityMatString = "[1 0 0]\n[0 1 0]\n[0 0 1]";
    std::stringstream buffer;
    buffer << identityMatSquare;
            CHECK(buffer.str() == indentityMatString);
}

TEST_CASE ("matrix multiplication test") {
    std::vector<double> randomVect = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> randomVect2 = {1, 0, 3, -4, 0, 6, -7, 0, 9};
    std::vector<double> result1 = {-28, 0, 42, -58, 0, 96, -88, 0, 150};
    std::vector<double> randomVect2by3 = {1, 2, 3, 4, 5, 6};
    std::vector<double> resultVect2by3 = {30, 36, 42, 66, 81, 96};


    Matrix randomMat{randomVect, 3, 3};
    Matrix randomMat1{randomVect2, 3, 3};
    Matrix resultMat1{result1, 3, 3};
    Matrix flatMat{randomVect, 9, 1};
    Matrix squareIdentity{identity, 3, 3};
    Matrix Mat2by3{randomVect2by3, 2, 3};
    Matrix ResultMat2by3{resultVect2by3, 2, 3};

            CHECK_THROWS(randomMat.operator*(flatMat));
            CHECK_NOTHROW(randomMat.operator*(randomMat));
            CHECK(resultMat1 == randomMat * randomMat1);
            CHECK(resultMat1 == resultMat1 * squareIdentity);
            CHECK(ResultMat2by3 == Mat2by3 * randomMat);

}