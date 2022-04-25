//
// Created by Eitan Kats on 13/04/2022.
//

#include <iostream>
#include "sources/Matrix.hpp"
#include <string>
#include "vector"

using namespace zich;

const int exitChar = -1;
const int matCreation = 1;
const int matMul = 2;
const int scalarMul = 3;

/*
 * demo matrices
 * [1 2 3], [4 5 6], [7 8 9]
 * [1 0 3], [4 0 6], [7 0 9]
 *
 * result:
 * [30,0,42], [66,0,96], [102,0,150]
 */

void handleMatInput(Matrix &demoMat) {
    std::cout << "input a matrix" << std::endl;
    //cleaning the buffer because I need to get a matrix as input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> demoMat;
}

void matMulDemo(const Matrix &mat1) {
    Matrix demoMat2{{0}, 1, 1};
    handleMatInput(demoMat2);
    std::cout << mat1 * demoMat2 << std::endl;
}

void matScalarMul(const Matrix &mat1) {
    std::cin.clear();
    fflush(stdin);
    double scalar;
    std::cout << "enter the scalar to perform multiplication" << std::endl;
    std::cin >> scalar;
    std::cout << scalar * mat1 << std::endl;
}


void startDemoLoop() {
    std::cout << "press 1 to input two new matrices for the demo or -1 to exit" << std::endl;
    int action;
    Matrix demoMat1{{0}, 1, 1};
    std::cout
            << "create mat by entering the following format each [] represents a row and inside are the numbers separated by spaces";
    handleMatInput(demoMat1);

    while (std::cin) {
        std::cout << "2 - matmul demo\n3 - matmul scalar demo" << std::endl;

        std::cin >> action;
        if (action == exitChar) {
            return;
        }
        if (action == matCreation) {
            std::cout
                    << "create mat by entering the following format each [] represents a row and inside are the numbers separated by spaces";
            handleMatInput(demoMat1);
        }
        if (action == matMul) {
            matMulDemo(demoMat1);
        }
        if (action == scalarMul) {
            matScalarMul(demoMat1);
        }
    }
}

int main() {
    try {
        startDemoLoop();
    } catch (std::exception &ex) {
        std::cout << "ERROR :" << ex.what() << std::endl;
        return 1;
    }

    return 0;
}