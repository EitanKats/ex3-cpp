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

TEST_CASE ("equality operator tests") {
    std::vector<double> mat1Vect = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    std::vector<double> mat2Vect = {1, 2, 3, 0, 3, 0, 0, 0, 3};
    std::vector<double> zeroMat = {0, 0, 0};
    Matrix m0{mat1Vect, 3, 3};
    Matrix m1{mat1Vect, 3, 3};
    Matrix m2{mat1Vect, 9, 1};
    Matrix m3{mat2Vect, 3, 3};
    Matrix m4{zeroMat, 3, 1};
            SUBCASE("bad dimensions for matrices") {
                CHECK_THROWS(m1.operator==(m2));
                CHECK_FALSE(m1 == m3);
                CHECK(m4 == (-m4));
                CHECK(m0 == m1);

    }
}
