//
// Created by Eitan Kats on 02/04/2022.
//

#include "Matrix.hpp"

#include <utility>
#include "vector"
#include <cmath>

using std::signbit;
namespace zich {

    Matrix::Matrix(vector<double> &matrix, int rowsNum, int colsNum) :
            _flatMatrix(matrix), _rowsNum(rowsNum), _columnsNum(colsNum) {
        if (rowsNum < 0 || colsNum < 0) {
            throw std::invalid_argument("bad dimensions");
        }
        if (rowsNum * colsNum != _flatMatrix.size()) {
            throw std::invalid_argument("bad dimensions");
        }

    }

    void Matrix::validateOperatorDimensions(const Matrix &m) const {
        if (this->_columnsNum != m._columnsNum || this->_rowsNum != m._rowsNum) {
            throw std::invalid_argument("cannot compare matrices with different dimensions");
        }

    }

    double Matrix::calculateSum() const {
        double sum = 0;
        for (const double &num: this->_flatMatrix) {
            sum += num;
        }
        return sum;
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
            i = i == 0 ? i : i * scalar;
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other_m) const {
        std::vector<double> vect = {1, 2, 3};
        return Matrix(vect, 1, 3);
    }

    Matrix Matrix::operator+(const Matrix &other_m) const {
        this->validateOperatorDimensions(other_m);
        std::vector<double> newVect(this->_flatMatrix);
        for (size_t i = 0; i < this->_flatMatrix.size(); ++i) {
            newVect[i] += _flatMatrix[i];
        }
        return Matrix{newVect, this->_rowsNum, this->_columnsNum};
    }

    Matrix Matrix::operator-(const Matrix &other_m) const {
        std::vector<double> vect = {1, 2, 3};
        return Matrix(vect, 1, 3);
    }

    Matrix operator*(double scalar, const Matrix &m) {
        std::vector<double> newMatVect(m._flatMatrix.size());
        for (size_t i = 0; i < m._flatMatrix.size(); ++i) {
            newMatVect[i] = m._flatMatrix[i] == 0 ? m._flatMatrix[i] : m._flatMatrix[i] * scalar;
        }
        return Matrix{newMatVect, m._rowsNum, m._columnsNum};
    }

    Matrix Matrix::operator-() const {
        vector<double> minusVect(this->_flatMatrix);
        for (size_t i = 0; i < minusVect.size(); ++i) {
            minusVect[i] = minusVect[i] == 0 ? 0 : -minusVect[i];
        }
        Matrix minusMat{minusVect, this->_rowsNum, this->_columnsNum};
        return minusMat;
    }

    bool Matrix::operator!=(const Matrix &m) const {
        this->validateOperatorDimensions(m);
        return !this->operator==(m);
    }

    bool Matrix::operator==(const Matrix &m) const {
        this->validateOperatorDimensions(m);
        for (size_t i = 0; i < m._flatMatrix.size(); ++i) {
            double myNum = this->_flatMatrix[i];
            double otherMatNum = m._flatMatrix[i];
            if ((myNum == 0 || otherMatNum == 0) && ((bool) signbit(myNum) != (bool) signbit(otherMatNum))) {
                return false;
            }
            if (myNum != otherMatNum) {
                return false;
            }
        }

        return true;
    }

    bool Matrix::operator<=(const Matrix &m) const {
        this->validateOperatorDimensions(m);
        return this->operator==(m) || this->operator<(m);
    }

    bool Matrix::operator>=(const Matrix &m) const {
        this->validateOperatorDimensions(m);
        return this->operator==(m) || this->operator>(m);
    }

    bool Matrix::operator>(const Matrix &m) const {
        this->validateOperatorDimensions(m);
        return this->calculateSum() > m.calculateSum();
    }

    bool Matrix::operator<(const Matrix &m) const {
        this->validateOperatorDimensions(m);
        return this->calculateSum() < m.calculateSum();
    }

    Matrix Matrix::operator+() const {
        std::vector<double> tst = {1, 2, 3};
        return Matrix{tst, 0, 0};
    }
}