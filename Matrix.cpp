//
// Created by Eitan Kats on 02/04/2022.
//

#include "Matrix.hpp"

#include <utility>
#include "vector"

namespace zich {

    Matrix::Matrix(vector<double> &matrix, int rowsNum, int colsNum) :
            _flatMatrix(matrix), _rowsNum(rowsNum), _columnsNum(colsNum) {
//        if (rowsNum < 0 || colsNum < 0) {
//            throw std::invalid_argument("bad dimensions");
//        }
    }

    ostream &operator<<(ostream &output, const Matrix &m) {

        for (int i = 0; i < m._rowsNum; ++i) {
            output << '[';
            for (int j = i * m._columnsNum; j < (i + 1) * m._columnsNum; ++j) {
                if (j % m._columnsNum == 0) {
                    output << m._flatMatrix[(unsigned int) j];
                } else {
                    output << ' ' << m._flatMatrix[(unsigned int) j];
                }
            }
            output << "]\n";
        }
        return output;
    }

    Matrix &Matrix::operator*=(const double scalar) {
        for (double &i: this->_flatMatrix) {
            i = scalar * i;
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other_m) const {
        std::vector<double> vect = {1, 2, 3};
        return Matrix(vect, 1, 3);
    }

    Matrix Matrix::operator+(const Matrix &other_m) const {
        std::vector<double> vect = {1, 2, 3};
        return Matrix(vect, 1, 3);
    }

    Matrix Matrix::operator-(const Matrix &other_m) const {
        std::vector<double> vect = {1, 2, 3};
        return Matrix(vect, 1, 3);
    }

    Matrix operator*(double scalar, const Matrix &m) {
        std::vector<double> vect = {1, 2, 3};
        return Matrix(vect, 1, 3);
    }


}