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

    void Matrix::validateDimensionsNaively(const Matrix &m) const {
        if (this->_columnsNum != m._columnsNum || this->_rowsNum != m._rowsNum) {
            throw std::invalid_argument("cannot compare matrices with different dimensions");
        }

    }

    void Matrix::validateDimensionsForMultiplication(const Matrix &m) const {
        if (this->_columnsNum != m._rowsNum) {
            throw std::invalid_argument("cannot multiply matrices with those dimensions");
        };
    }

    double Matrix::calculateSum() const {
        double sum = 0;
        for (const double &num: this->_flatMatrix) {
            sum += num;
        }
        return sum;
    }

    ostream &operator<<(ostream &output, const Matrix &m) {

        for (int row = 0; row < m._rowsNum; ++row) {
            output << '[';
            for (int col = row * m._columnsNum; col < (row + 1) * m._columnsNum; ++col) {
                if (col % m._columnsNum == 0) {
                    output << m._flatMatrix[(unsigned int) col];
                } else {
                    output << ' ' << m._flatMatrix[(unsigned int) col];
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
        this->validateDimensionsForMultiplication(other_m);
        unsigned int newMatSize = (unsigned int) this->_rowsNum * (unsigned int) other_m._columnsNum;
        std::vector<double> newVect(newMatSize, 0);
        unsigned int rowCtr = 0;
        unsigned int currRow = 0;

        for (size_t i = 0; i < newMatSize; ++i) {

            if (rowCtr == other_m._columnsNum) {
                currRow += (unsigned int) this->_columnsNum;
                rowCtr = 0;
            }
            for (int j = 0; j < other_m._rowsNum; ++j) {
                unsigned int nextMatIdx =
                        ((unsigned int) j * (unsigned int) other_m._columnsNum) +
                        (i % (unsigned int) other_m._columnsNum);
                unsigned int currMatIdx = currRow + (unsigned int) j;
                double fromOther = other_m._flatMatrix[nextMatIdx];
                double fromCurrent = this->_flatMatrix[currMatIdx];
                newVect[i] += fromCurrent * fromOther;
            }
            rowCtr++;
        }
        return Matrix{newVect, this->_rowsNum, other_m._columnsNum};
    }

    Matrix Matrix::operator+(const Matrix &other_m) const {
        this->validateDimensionsNaively(other_m);
        std::vector<double> newVect(this->_flatMatrix);
        for (size_t i = 0; i < this->_flatMatrix.size(); ++i) {
            newVect[i] += other_m._flatMatrix[i];
        }
        return Matrix{newVect, this->_rowsNum, this->_columnsNum};
    }

    Matrix &Matrix::operator+=(const Matrix &other_m) {
        this->validateDimensionsNaively(other_m);
        for (size_t i = 0; i < other_m._flatMatrix.size(); ++i) {
            this->_flatMatrix[i] = this->_flatMatrix[i] + other_m._flatMatrix[i];
        }
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &other_m) {
        this->validateDimensionsNaively(other_m);
        for (size_t i = 0; i < other_m._flatMatrix.size(); ++i) {
            this->_flatMatrix[i] = this->_flatMatrix[i] - other_m._flatMatrix[i];
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other_m) const {
        this->validateDimensionsNaively(other_m);
        std::vector<double> newVect(this->_flatMatrix);
        for (size_t i = 0; i < this->_flatMatrix.size(); ++i) {
            newVect[i] -= other_m._flatMatrix[i];
        }
        return Matrix{newVect, this->_rowsNum, this->_columnsNum};
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

    //region equality operators
    bool Matrix::operator!=(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return !this->operator==(m);
    }

    bool Matrix::operator==(const Matrix &m) const {
        this->validateDimensionsNaively(m);
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
        this->validateDimensionsNaively(m);
        return this->operator==(m) || this->operator<(m);
    }

    bool Matrix::operator>=(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->operator==(m) || this->operator>(m);
    }

    bool Matrix::operator>(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->calculateSum() > m.calculateSum();
    }

    bool Matrix::operator<(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->calculateSum() < m.calculateSum();
    }
    //endregion

    Matrix Matrix::operator+() const {
        std::vector<double> tst = {1, 2, 3};
        return Matrix{tst, 0, 0};
    }
}