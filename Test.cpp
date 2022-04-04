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
                CHECK_THROWS(Matrix a(identity, 3, -3));
                CHECK_THROWS(Matrix a(identity, -3, 3));
    }
            SUBCASE("not matching dimensions") {
                CHECK_THROWS(Matrix a(identity, 3, 1));
                CHECK_THROWS(Matrix a(identity, 1, 3));
    }

}
